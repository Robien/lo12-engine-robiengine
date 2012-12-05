#include "Objet.h"
#include "AbstractObjet.h"


Objet::Objet(std::string str) : AbstractObjet(str)
{
}
Objet::Objet(Matrice<GLdouble>* matrice) : AbstractObjet(matrice)
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

	glPushMatrix();
	glMultMatrixd(getMatrice()->getMat());
   

	

	//on affiche les faces
	for (unsigned int i = 0; i < _listeFace.size(); ++i)
	{
		_listeFace.at(i)->affiche();
	}

	//on affiche les objets fils
	for (unsigned int i = 0; i < getFils()->size(); ++i)
	{
		getFils()->at(i)->affiche();
	}


//	for(std::list<AbstractObjet*>::const_iterator lit = getFils().begin();lit != getFils().end();++lit) 
	//{
	//	(*lit)->affiche();
//	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

}

void Objet::addFace(Face* face)
{
	_collider->addCollider(face->getCollider());
	_listeFace.push_back(face);
}

void Objet::toggleFilted()
{
	_isFilted = !_isFilted;
	for (unsigned int i = 0; i < _listeFace.size(); ++i)
	 {
		 _listeFace.at(i)->toggleFilted();
	 }
}