#include "Objet.h"
#include "AbstractObjet.h"
#include "VBOMangaer.h"
#include <string>

Objet::Objet(std::string str) : AbstractObjet(str)
{
	_oldMaterial = NULL;
	_mat = (GLdouble*) (malloc(sizeof(GLdouble)*16));
}
Objet::Objet(Matrice<GLdouble>* matrice) : AbstractObjet(matrice)
{
	_oldMaterial = NULL;
	_mat = (GLdouble*) (malloc(sizeof(GLdouble)*16));
}


Objet::~Objet()
{
}

unsigned int Objet::affiche()
{

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();
	glMultMatrixd(getMatrice()->getMat());

	//delete _mat;
	//_mat = (GLdouble*) (malloc(sizeof(GLdouble)*16));
	//malloc(0);
	glGetDoublev(GL_MODELVIEW_MATRIX, _mat);
	//std::cout << mat[14] / mat[15] << std::endl;
	_collider->majMatrice(getMatrice()); // il ne faudrait pas utiliser _mat plutot ?
	//std::cout << _collider->getDistanceMax() << " - " << (mat[14]/mat[15]) << std::endl;
	unsigned int nbPointAffiche = 0;

	if (!(_mat[14]/_mat[15] > _collider->getDistanceMax())) // en dehors du champs de vision ?
	{

		if (_isVboActive)
		{
			for (unsigned int i = 0; i < _vbo.size(); ++i)
			{
				nbPointAffiche += _vbo.at(i)->affiche();
			}
		}
		else
		{

			//on affiche les faces
			for (unsigned int i = 0; i < _listeFace.size(); ++i)
			{
				nbPointAffiche += _listeFace.at(i)->affiche();
			}
		}
	}
	//	glMatrixMode(GL_MODELVIEW);

	Collider* col = new Collider();

	col->addColliderWithMatrice(*_collider, new Matrice<GLdouble>(_mat));
	std::cout << col->getMin().getX() << std::endl;
	col->affiche();

	//delete col;

	//std::cout << matriceAbsolue().getPosition().getX()  << std::endl;
	//_collider->affiche();
	//GLdouble* newData = (GLdouble*) malloc(16*sizeof(GLdouble));
	//glGetDoublev(GL_MODELVIEW_MATRIX, newData);
	//std::cout << (new Matrice<GLdouble>(newData))->getVector16().size() << std::endl;
		//_collider->afficheWithMat(new Matrice<GLdouble>(_mat), getMatrice());
	//delete newData;

	//on affiche les objets fils
	for (unsigned int i = 0; i < getFils()->size(); ++i)
	{
		nbPointAffiche += getFils()->at(i)->affiche();
	}


	//	for(std::list<AbstractObjet*>::const_iterator lit = getFils().begin();lit != getFils().end();++lit) 
	//{
	//	(*lit)->affiche();
	//	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);


	return nbPointAffiche;
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