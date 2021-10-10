#include "Light.h"
// Конструктор
Light::Light(void)
{
}

void Light::setPosition(int x, int y, int z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}


void Light::setAmbient(float r, float g, float b, float a)
{
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}
void Light::setDiffuse(float r, float g, float b, float a)
{
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}
void Light::setSpecular(float r, float g, float b, float a)
{
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}
void Light::apply()
{
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}
