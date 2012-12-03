#include "Camera.h"
#include "Outil.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}


void Camera::affiche()
{
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glLoadMatrixd(_matrice.getMat());
	glutPostRedisplay();
	
}

