#include "Objet.h"
#include "AbstractObjet.h"
#include "VBOMangaer.h"
#include <string>

Objet::Objet(std::string str) : AbstractObjet(str)
{
	_oldMaterial = NULL;
}
Objet::Objet(Matrice<GLdouble>* matrice) : AbstractObjet(matrice)
{
	_oldMaterial = NULL;
}


Objet::~Objet()
{
}

void Objet::affiche()
{
	//if (matrice().getPosition().getZ() < 0)
	//{
	//	std::cout << "BOOM : " << AbstractObjet::_nom << std::endl;
	//	return;
	//}
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();
	glMultMatrixd(getMatrice()->getMat());


	if (_isVboActive)
	{
		for (unsigned int i = 0; i < _vbo.size(); ++i)
		{
			_vbo.at(i)->affiche();
		}
	}
	else
	{

		//on affiche les faces
		for (unsigned int i = 0; i < _listeFace.size(); ++i)
		{
			_listeFace.at(i)->affiche();
		}
	}
	//	glMatrixMode(GL_MODELVIEW);

	//std::cout << matriceAbsolue().getPosition().getX()  << std::endl;
	//_collider->affiche();
	//GLdouble* newData = (GLdouble*) malloc(16*sizeof(GLdouble));
	//glGetDoublev(GL_MODELVIEW_MATRIX, newData);
	//std::cout << (new Matrice<GLdouble>(newData))->getVector16().size() << std::endl;
	//	_collider->afficheWithMat(new Matrice<GLdouble>(newData), getMatrice());
	//delete newData;

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

	//std::cout << face->getMaterial() << " - " << _oldMaterial << std::endl;
	if (face->getMaterial() != _oldMaterial)
	{
		_vbo.push_back(VBOMangaer::get()->makeVBO());
		_oldMaterial = face->getMaterial();
	}

	VBO* vbo = _vbo.at(_vbo.size() - 1);

	std::vector<Vector3d<GLdouble>* > points = face->getListePoints();
	std::vector<Vector2d<GLdouble>* > textures = face->getListeCoordonneesTextures();
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		vbo->addPoint(points.at(i), textures.at(i), face->getNormale());
	}
	vbo->setMaterial(_oldMaterial);
}

void Objet::toggleFilted()
{
	_isFilted = !_isFilted;
	for (unsigned int i = 0; i < _listeFace.size(); ++i)
	{
		_listeFace.at(i)->toggleFilted();
	}
}

void Objet::toggleVBO()
{
	_isVboActive = !_isVboActive;

}