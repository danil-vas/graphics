#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

unsigned int KeyCode;
unsigned int timer = 0;
short int counter = 0;
float color[3] = { 1.0, 0.0, 0.0 };
float KitColor[4][3] = { {0.0, 0.0, 0.0}, {1.0, 1.0, 1.0}, {0.0, 0.0, 1.0}, {1.0,0.0,0.0} };

// функция вызывается каждые 20 мс
void Simulation(int value)
{
	// если нажата клавиша "Enter" (код 13), то с периодичностью в 1 секунду
	// меняем цвет чайника
	if (KeyCode == 13) {
		++timer;
		if (timer == 50) {
			timer = 0;
			// меняем цвет чайника
			color[0] = KitColor[counter][0];
			color[1] = KitColor[counter][1];
			color[2] = KitColor[counter][2];
			++counter;
		}
		if (counter == 4) counter = 0;
	}
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, Simulation, 0);
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
	glClearColor(0.22, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);
	// выводим объект ‐ значение берем из массива
	glColor3f(color[0],color[1],color[2]);
	glutWireTeapot(1.0);
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// Функция обработки нажатия клавиш
void KeyboardFunc(unsigned char key, int x, int y)
{
	//printf("Key code is %i\n", (unsigned int)key);
	// присваиваем значение клавиши глобальной переменной
	KeyCode = (unsigned int)key;
};


int main(int argc, char* argv[]) {
	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	// создание окна:
// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(600, 600);
	// 3. создаем окно
	glutCreateWindow("laba1");
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(Display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(Reshape);
	// устанавливаем функцию которая будет вызвана через 20 мс
	glutTimerFunc(20, Simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);
	glutMainLoop();
}
