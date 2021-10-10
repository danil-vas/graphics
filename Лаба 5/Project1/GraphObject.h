#pragma once
#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/freeglut.h"
#include "Material.h"
#include <memory>
using namespace std;
class GraphicObject
{
private:
	GLfloat angle;
	// Цвет модели
	GLfloat color[3];
	// Используемый материал
	std::shared_ptr<PhongMaterial> material;

public:
	// Позиция и угол поворота для объекта
	GLfloat position[3];
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
	// Установка используемого материала
	void setMaterial(shared_ptr<PhongMaterial> material2);

};