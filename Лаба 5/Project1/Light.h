#pragma once
#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/freeglut.h"
// КЛАСС ДЛЯ РАБОТЫ С ИСТОЧНИКОМ СВЕТА
class Light
{
public:
	// конструкторы
	Light();
	//Light(float x, float y, float z);
	Light(float x, float y, float z);
	// задание различных параметров источника света
	void setPosition(int x, int y, int z);
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	// установка всех параметров источника света с заданным номером
	// данная функция должна вызываться после установки камеры,
	// т.к. здесь устанавливается позиция источника света
	void apply();
private:
	// позиция источника света
	GLfloat position[3];
	// фоновая составляющая источника света
	GLfloat ambient[4];
	// диффузная составляющая
	GLfloat diffuse[4];
	// зеркальная составляющая
	GLfloat specular[4];
};