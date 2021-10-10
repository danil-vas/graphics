#include "GraphObject.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include <iostream>
#include <memory>
#include <vector>

using namespace std;
const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount];
LARGE_INTEGER OldSimTik, NewSimTik, frequency;

int matrix1[16] = { -1,0,0,0, 0,1,0,0, 0,0,-1,0, 0,0,0,1 };
int matrix2[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
int matrix3[16] = { 0,0,1,0, 0,1,0,0, -1,0,0,0, 0,0,0,1 };
int matrix4[16] = { 0,0,-1,0, 0,1,0,0, 1,0,0,0, 0,0,0,1 };


Camera camera;
Light light;
// задание всех параметров одного материала
PhongMaterial material1, material2, material3, material4;

float GetSimulationTime() {
	OldSimTik = NewSimTik;
	QueryPerformanceCounter(&NewSimTik);
	return (float(NewSimTik.QuadPart - OldSimTik.QuadPart)) / frequency.QuadPart;
}

// функция вызывается каждые 20 мс
void Simulation()
{
	// ОПРЕДЕЛЕНИЕ ВРЕМЕНИ ПРОШЕДШЕГО С МОМЕНТА ПОСЛЕДНЕЙ СИМУЛЯЦИИ В СЕКУНДАХ
	float deltaTime = GetSimulationTime();
	// ПЕРЕМЕЩЕНИЕ КАМЕРЫ
	bool CameraLeft = GetAsyncKeyState(VK_LEFT);
	bool CameraRight = GetAsyncKeyState(VK_RIGHT);
	bool CameraUp = GetAsyncKeyState(VK_UP);
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
	// устанавливаем общую фоновую освещенность
	GLfloat globalAmbientColor[] = { 0.8, 0.8, 0.8, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);

	// включаем режим расчета освещения
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// устанавливаем камеру
	camera.apply();
	
	light.setPosition(10, 10, 10);
	light.setDiffuse(0.8, 0.8, 0.8, 1.0);
	light.setAmbient(0.2, 0.2, 0.2, 1.0);
	light.setSpecular(0.0, 0.0, 0.0, 1.0);
	light.apply();
	/*material.setDiffuse(1.0, 0.0, 0.0, 1.0);
	material.setAmbient(0.4, 0.0, 0.0, 1.0);
	material.setSpecular(1.0, 1.0, 1.0, 1.0);
	material.setEmission(0.0, 0.0, 0.0, 1.0);
	material.setShininess(64.0);*/
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


int main(int argc, char* argv[]) {
	vector<shared_ptr<PhongMaterial>> materials;
	materials.emplace_back(new PhongMaterial);
	materials.emplace_back(new PhongMaterial);
	materials.emplace_back(new PhongMaterial);
	materials.emplace_back(new PhongMaterial);
	/*shared_ptr<PhongMaterial> material1(new PhongMaterial);
	shared_ptr<PhongMaterial> material2(new PhongMaterial);
	shared_ptr<PhongMaterial> material3(new PhongMaterial);
	shared_ptr<PhongMaterial> material4(new PhongMaterial);*/
	materials.at(0)->load("data//materials//material_1.txt");
	materials.at(1)->load("data//materials//material_2.txt");
	materials.at(2)->load("data//materials//material_3.txt");
	materials.at(3)->load("data//materials//material_4.txt");
	graphicObjects[0].setСolor(1.0, 0.0, 0.0);
	graphicObjects[0].setPosition(4, 0, 0);
	for (int i = 0; i < 3; ++i) {
		matrix1[12 + i] = graphicObjects[0].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[0].modelMatrix[i] = matrix1[i];
	}
	graphicObjects[0].setMaterial(materials.at(0));
	
	//shared_ptr<PhongMaterial> material;
	//graphicObjects[0].setMaterial(material);


	graphicObjects[1].setСolor(0.0, 0.0, 1.0);
	graphicObjects[1].setPosition(-4, 0, 0);
	for (int i = 0; i < 3; ++i) {
		matrix2[12 + i] = graphicObjects[1].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[1].modelMatrix[i] = matrix2[i];
	}
	graphicObjects[1].setMaterial(materials.at(1));

	graphicObjects[2].setСolor(0.0, 1.0, 0.0);
	graphicObjects[2].setPosition(0, 0, -4);
	for (int i = 0; i < 3; ++i) {
		matrix3[12 + i] = graphicObjects[2].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[2].modelMatrix[i] = matrix3[i];
	}
	graphicObjects[2].setMaterial(materials.at(2));


	graphicObjects[3].setСolor(1.0, 1.0, 1.0);
	graphicObjects[3].setPosition(0, 0, 4);
	for (int i = 0; i < 3; ++i) {
		matrix4[12 + i] = graphicObjects[3].position[i];
	}
	for (int i = 0; i < 16; ++i) {
		graphicObjects[3].modelMatrix[i] = matrix4[i];
	}
	graphicObjects[3].setMaterial(materials.at(3));
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
