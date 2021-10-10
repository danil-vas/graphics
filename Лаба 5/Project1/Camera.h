#pragma once
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/freeglut.h"
#include <cmath>
#include <algorithm>

class Camera
{
private:
	// необходимые свойства

	float radius;
	bool left, right, up, down, forward, backward, w, s;
	float time, x, y, z, alpha = 45, beta = 45;
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

