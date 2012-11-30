#include "AbstractObjet.h"


AbstractObjet::AbstractObjet()
{
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