#include "Camera.h"
#include "Outil.h"
#include "Matrice.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}


void Camera::affiche()
{
	std::cout << "VIVE LES POMMES" << std::endl;
glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
//	glRotatef(0, 0, 0, 1);
//	glRotatef(0, 1, 0, 0);
//	glRotatef(0, 0, 1, 0);
//	glTranslated(i++, 0, 0);
	glutPostRedisplay();
	
}

