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


}
unsigned int Camera::afficheFils()
{
	unsigned int nbPointAffiche = 0;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	for (unsigned int i = 0; i < getFils()->size(); ++i)
	{
		nbPointAffiche += getFils()->at(i)->affiche();
	}
	glPopMatrix();

	return nbPointAffiche;
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





void Camera::addFils(AbstractObjet* fils)
{
	_fils.push_back(fils);

}

void Camera::removeFils(AbstractObjet* fils)
{
	for (unsigned int i = 0; i < getFils()->size(); ++i)
	{
		if (getFils()->at(i) == fils)
		{
			getFils()->at(i) = getFils()->at(getFils()->size() - 1); 
			getFils()->pop_back();
		}
	}

}

void Camera::addFils(std::vector<AbstractObjet*>* fils)
{
	for (unsigned int i = 0; i < fils->size(); ++i)
	{
		addFils(fils->at(i));
	}

}
void Camera::removeFils(std::vector<AbstractObjet*>* fils)
{
	for (unsigned int i = 0; i < fils->size(); ++i)
	{
		removeFils(fils->at(i));
	}

}

std::vector<AbstractObjet*>* Camera::getFils()
{
	return &_fils;
}
