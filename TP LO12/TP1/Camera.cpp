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


void Camera::maj()
{
//	glutPostRedisplay();
}

Matrice<GLdouble>* Camera::getMatrice()
{
	return &_matrice;
}
Matrice<GLdouble>& Camera::matrice()
{
	return _matrice;
}