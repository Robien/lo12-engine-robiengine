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
	_fils.remove(fils);
}

std::list<AbstractObjet*> AbstractObjet::getFils()
{
	return _fils;
}

Matrice<GLdouble>* AbstractObjet::getMatrice()
{
	return _matrice;
}

void AbstractObjet::setMatrice(Matrice<GLdouble>* matrice)
{
	_matrice = matrice;
}