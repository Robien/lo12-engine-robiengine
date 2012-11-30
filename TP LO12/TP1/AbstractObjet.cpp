#include "AbstractObjet.h"



AbstractObjet::AbstractObjet()
{
	//la matrice par défaut = matrice identitée
	_matrice = new Matrice<GLdouble>();
}

AbstractObjet::AbstractObjet(Matrice<GLdouble>* matrice)
{
	_matrice = matrice;
}


AbstractObjet::~AbstractObjet()
{
}


void AbstractObjet::addFils(AbstractObjet* fils)
{
	_fils.push_back(fils);
}

void AbstractObjet::removeFils(AbstractObjet* fils)
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

std::vector<AbstractObjet*>* AbstractObjet::getFils()
{
	return &_fils;
}

Matrice<GLdouble>* AbstractObjet::getMatrice()
{
	return _matrice;
}

void AbstractObjet::setMatrice(Matrice<GLdouble>* matrice)
{
	_matrice = matrice;
}


void AbstractObjet::affiche()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();
	glMultMatrixd(getMatrice()->getMat());

	 

	//on affiche les objets fils

	 for (unsigned int i = 0; i < getFils()->size(); ++i)
	 {
		 getFils()->at(i)->affiche();
	 }


//	for(std::list<AbstractObjet*>::const_iterator lit = getFils().begin();lit != getFils().end();++lit) 
//	{
//		std::cout << lit._Ptr << std::endl;
//		(*lit)->affiche();
//	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}