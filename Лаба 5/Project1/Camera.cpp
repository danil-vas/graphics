#include "Camera.h"

using namespace std;

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
	
	if (left) {
		alpha += 90 * time;
	}
	if (right) {
		alpha += -90 * time;
	}
	if (up) {
		beta = min<float>(beta + 90 * time, 90);
	}
	if (down) {
		if (beta > 0) {
			beta += -90 * time;
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
	float alphaRad = alpha * 0.017;
	float betaRad = beta * 0.017;
	x = radius * cos(alphaRad) * cos(betaRad);
	z = radius * sin(alphaRad) * cos(betaRad);
	y = radius * sin(betaRad);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
}
