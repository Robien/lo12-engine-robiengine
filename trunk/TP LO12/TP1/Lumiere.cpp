#include "Lumiere.h"


AllureFaisceau::AllureFaisceau(GLdouble k, GLdouble theta)
{
	_k=k;
	_theta=theta;
}

AllureFaisceau::~AllureFaisceau()
{
}

Lumiere::Lumiere() : _allure_faisceau()
{
	_sphere = gluNewQuadric();
}


Lumiere::~Lumiere()
{
	gluDeleteQuadric(_sphere);
}

void Lumiere::affiche()
{
	glDisable(GL_LIGHTING);
	glColor3d(_couleur.getX(), _couleur.getY(), _couleur.getZ());				
	glPushMatrix();
	glTranslatef(_position.getX(), _position.getY(), _position.getZ());
	gluSphere(_sphere, 0.1, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
