#include "Objet.h"
#include "AbstractObjet.h"


Objet::Objet()
{
}


Objet::~Objet()
{
}

void Objet::affiche()
{

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	//on affiche les faces
	for (unsigned int i = 0; i < _listeFace.size(); ++i)
	{
		_listeFace.at(i)->affiche();
	}

	//on affiche les objets fils
	for(std::list<AbstractObjet*>::const_iterator lit = getFils().begin();lit != getFils().end();++lit) 
	{
		(*lit)->affiche();
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

}

void Objet::addFace(Face* face)
{
	_listeFace.push_back(face);
}