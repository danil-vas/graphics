#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/freeglut.h"
#include <cmath>
#include <algorithm>
using namespace std;
LARGE_INTEGER OldSimTik, NewSimTik, frequency;

class Camera
{
private:
	// необходимые свойства
	float radius;
	bool left, right, up, down, forward, backward;
	float time, x , y , z, fi = 45, om = 45;
public:
	// конструктор по умолчанию
	Camera();
	// деструктор ‐ сохранение новых параметров камеры
	~Camera();
	// установка признаков нажатых клавиш
	void setKey(bool left, bool right, bool up, bool down, bool forward, bool backward);
	// движение камеры в ранее выбранном направлении
	// параметр ‐ количество секунд прошедших с момента последнего вызова
	void simulate(float sec);
	// функция для установки матрицы камеры
	void apply();
};

Camera::Camera() {
	radius = sqrt(499);
}
Camera::~Camera() {
}
void Camera::simulate(float sec) {
	time = sec;
}

void Camera::setKey(bool left, bool right, bool up, bool down, bool forward, bool backward) {
	Camera::left = left;
	Camera::right = right;
	Camera::up = up;
	Camera::down = down;
	Camera::forward = forward;
	Camera::backward = backward;
	cout << om << endl;
	if (left) { 
		fi += 90 * time;
	}
	if (right) {
		fi += -90 * time;
	}
	if (up) {
		om = min<float>(om + 90 * time, 90);
		/*if (om < 90) {
			om += 90 * time;
		}*/
	}
	if (down) {
		if (om > 0) {
			om += -90 * time;
		}
	}
	if (forward) {
		if (radius > 8) {
			radius += -30 * time;
		}
	}
	if (backward) {
		if (radius < 30) {
			radius += 30 * time;
		}
	}
}


void Camera::apply() {
	float fiRad = fi * 0.017;
	float omRad = om * 0.017;
	x = radius * cos(fiRad) * cos(omRad);
	z = radius * sin(fiRad) * cos(omRad);
	y = radius * sin(omRad);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
}

float GetSimulationTime() {
	OldSimTik = NewSimTik;
	QueryPerformanceCounter(&NewSimTik);
	return (float(NewSimTik.QuadPart - OldSimTik.QuadPart)) / frequency.QuadPart;
}

class GraphicObject
{
private:
	// Позиция и угол поворота для объекта
	GLfloat position[3];
	GLfloat angle;
	// Цвет модели
	GLfloat color[3];
public:
	// Конструктор
	GraphicObject(void);
	// Задать позицию объекта
	void setPosition(float x, float y, float z);
	// Задать угол поворота в градусах относительно оси OY
	void setAngle(float a);
	// Задать цвет модели
	void setСolor(float r, float g, float b);
	// Вывести объект
	void draw(void);
	// Матрица модели (расположение объекта) ‐ чтоб не вычислять каждый раз
	GLfloat modelMatrix[16];
};

// Конструктор
GraphicObject::GraphicObject(void)
{
}
// задать позицию объекта
void GraphicObject::setPosition(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}
// задать угол поворота в градусах относительно оси OY
void GraphicObject::setAngle(float a)
{
	angle = a;
}
// Задать цвет модели
void GraphicObject::setСolor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}
// вывести объект
void GraphicObject::draw(void)
{
	//glTranslatef(position[0], position[1], position[2]);
	//glRotatef(angle, 0.0, 1.0, 0.0);
	glPushMatrix();
	glMultMatrixf(modelMatrix);
	glColor3f(color[0],color[1],color[2]);
	glutWireTeapot(1.0);
	glPopMatrix();
}

const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount];
Camera camera;

// функция вызывается каждые 20 мс
void Simulation()
{
	// ОПРЕДЕЛЕНИЕ ВРЕМЕНИ ПРОШЕДШЕГО С МОМЕНТА ПОСЛЕДНЕЙ СИМУЛЯЦИИ В СЕКУНДАХ
	float deltaTime = GetSimulationTime();
		// ПЕРЕМЕЩЕНИЕ КАМЕРЫ
	bool CameraLeft = GetAsyncKeyState(VK_LEFT);
	bool CameraRight = GetAsyncKeyState(VK_RIGHT);
	bool CameraUp = GetAsyncKeyState(VK_UP)	;
	bool CameraDown = GetAsyncKeyState(VK_DOWN);
	bool CameraForward = GetAsyncKeyState(VK_ADD);
	bool CameraBackward = GetAsyncKeyState(VK_SUBTRACT);
	camera.setKey(CameraLeft, CameraRight,
		CameraUp, CameraDown,
		CameraForward, CameraBackward);
	camera.simulate(deltaTime);
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
};

// функция, вызываемая при изменении размеров окна
void Reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void Display(void)
{
	// отчищаем буфер цвета
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	camera.apply();
	// выводим объекты
	for (int i = 0; i < graphicObjectCount; i++) {
		graphicObjects[i].draw();
	};
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	printf("Key code is %i\n", (unsigned int)key);
};

int matrix1[16] = { -1,0,0,0, 0,1,0,0, 0,0,-1,0, 4,0,0,1 };
int matrix2[16] = { 1,0,0,0, 0,1,0,0, 0,0, 1,0, -4,0,0,1 };
int matrix3[16] = { 0,0,1,0, 0,1,0,0, -1,0,0,0, 0,0,-4,1 };
int matrix4[16] = { 0,0,-1,0, 0,1,0,0, 1,0,0,0, 0,0,4,1 };
int main(int argc, char* argv[]) {
	graphicObjects[0].setСolor(1.0, 0.0, 0.0);
	//graphicObjects[0].setPosition(4.0, 0.0, 0.0);
	//graphicObjects[0].setAngle(0);
	for (int i = 0; i < 16; ++i) {
		graphicObjects[0].modelMatrix[i] = matrix1[i];
	}
	graphicObjects[1].setСolor(0.0, 0.0, 1.0);
	//graphicObjects[1].setPosition(-4.0, 0.0, 0.0);
	//graphicObjects[1].setAngle(180);
	for (int i = 0; i < 16; ++i) {
		graphicObjects[1].modelMatrix[i] = matrix2[i];
	}
	graphicObjects[2].setСolor(0.0, 1.0, 0.0);
	//graphicObjects[2].setPosition(0.0, 0.0, 4.0);
	//graphicObjects[2].setAngle(90)
	for (int i = 0; i < 16; ++i) {
		graphicObjects[2].modelMatrix[i] = matrix3[i];
	}
	graphicObjects[3].setСolor(1.0, 1.0, 1.0);
	for (int i = 0; i < 16; ++i) {
		graphicObjects[3].modelMatrix[i] = matrix4[i];
	}
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	// создание окна:
// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("laba1");
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutIdleFunc(Simulation);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);
	QueryPerformanceCounter(&NewSimTik);
	QueryPerformanceFrequency(&frequency);
	glutMainLoop();
}
