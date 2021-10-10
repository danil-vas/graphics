#include "Material.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
using namespace std;



// Конструктор
PhongMaterial::PhongMaterial(void)
{
}

void PhongMaterial::setAmbient(float r, float g, float b, float a)
{
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}
void PhongMaterial::setDiffuse(float r, float g, float b, float a)
{
	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}
void PhongMaterial::setSpecular(float r, float g, float b, float a)
{
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}
void PhongMaterial::setEmission(float r, float g, float b, float a)
{
	emission[0] = r;
	emission[1] = g;
	emission[2] = b;
	emission[3] = a;
}
void PhongMaterial::setShininess(float p)
{
	shininess = p;
}

void PhongMaterial::apply()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_POSITION, emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
ostream& operator<<(ostream& lhv, const vector<float>& rhv) {
	std::copy(rhv.begin(), rhv.end(), ostream_iterator<float>(cout, " "));
	return lhv;
}
void PhongMaterial::load(const char* path)
{
	ofstream fout;
	
	ifstream fin;
	fin.open(path);


	if (!fin.is_open()) {
		cout << "Error(((((((((" << endl;
	}
	else {
		while (!fin.eof()) {
			for (int i = 0; i < 5; i++) {
				if (i == 0) {
					string str;
					getline(fin, str);
					
					istringstream(str) >> diffuse[0] >> diffuse[1] >> diffuse[2] >> diffuse[3];
				}
				else if (i == 1) {
					string str;
					getline(fin, str);
					
					istringstream(str) >> ambient[0] >> ambient[1] >> ambient[2] >> ambient[3];
				}
				else if (i == 2) {
					string str;
					getline(fin, str);
					
					istringstream(str) >> specular[0] >> specular[1] >> specular[2] >> specular[3];
				}
				else if (i == 3) {
					string str;
					getline(fin, str);
					
					istringstream(str) >> emission[0] >> emission[1] >> emission[2] >> emission[3];
				}
				else if (i == 4) {
					string str;
					getline(fin, str);

					istringstream(str) >> shininess;
				}
				
			}
	
		}
	}



	fin.close();
}