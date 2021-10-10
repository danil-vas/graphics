#pragma once
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/freeglut.h"
// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterial
{
public:
	// конструктор по умолчанию
	PhongMaterial();
	// задание параметров материала
	void setAmbient(float r, float g, float b, float a);
	void setDiffuse(float r, float g, float b, float a);
	void setSpecular(float r, float g, float b, float a);
	void setEmission(float r, float g, float b, float a);
	void setShininess(float p);
	// загрузка параметров материала из внешнего текстового файла
	//void load(std::string filename);
	// установка всех параметров материала
	void apply();
	void load(const char* path);
private:
	// фоновая составляющая 
	GLfloat ambient[4];
	// диффузная составляющая
	GLfloat diffuse[4];
	// зеркальная составляющая
	GLfloat specular[4];
	// самосвечение
	GLfloat emission[4];
	// степень отполированности
	GLfloat  shininess;
};
