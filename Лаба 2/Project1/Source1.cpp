#include "Header.h"

const int graphicObjectCount = 4;
GraphicObject graphicObjects[graphicObjectCount];

int matrix1[16] = { -1,0,0,0, 0,1,0,0, 0,0,-1,0, 4,0,0,1 };
int matrix2[16] = { 1,0,0,0, 0,1,0,0, 0,0, 1,0, -4,0,0,1 };
int matrix3[16] = { 0,0,1,0, 0,1,0,0, -1,0,0,0, 0,0,-4,1 };
int matrix4[16] = { 0,0,-1,0, 0,1,0,0, 1,0,0,0, 0,0,4,1 };

// функция вызывается каждые 20 мс
void Simulation(int value)
{
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
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(15, 15, 7.5, 0, 0, 0, 0, 1, 0);
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
	glutTimerFunc(20, Simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(KeyboardFunc);
	glutMainLoop();
}
