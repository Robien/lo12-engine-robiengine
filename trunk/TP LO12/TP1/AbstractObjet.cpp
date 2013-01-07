#include "AbstractObjet.h"



AbstractObjet::AbstractObjet(std::string str): _listPointsCollision()
{
	_pere = NULL;
	_isFilted = false;
	_nom = str;
	//la matrice par défaut = matrice identitée
	_matrice = new Matrice<GLdouble>();
	_matriceAbsolue = new Matrice<GLdouble>();
	_collider = new Collider();
}

AbstractObjet::AbstractObjet(Matrice<GLdouble>* matrice, std::string str): _listPointsCollision()
{
	_pere = NULL;
	_isFilted = false;
	_nom = str;
	_matrice = matrice;
	_matriceAbsolue = new Matrice<GLdouble>();
	_collider = new Collider();
}


AbstractObjet::~AbstractObjet()
{
	for (unsigned int i = 0; i < _fils.size(); ++i)
	{
		delete (_fils.at(i));
	}
	for (unsigned int i = 0; i < _listPointsCollision.size(); ++i)
	{
		delete (_listPointsCollision.at(i));
	}

	_fils.clear();
}


void AbstractObjet::addFils(AbstractObjet* fils)
{
	_fils.push_back(fils);
	fils->_pere = this;
	_collider->addCollider(*fils->_collider);
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
	fils->_pere = NULL;

}

void AbstractObjet::addFils(std::vector<AbstractObjet*>* fils)
{
	for (unsigned int i = 0; i < fils->size(); ++i)
	{
		addFils(fils->at(i));
	}

}
void AbstractObjet::removeFils(std::vector<AbstractObjet*>* fils)
{
	for (unsigned int i = 0; i < fils->size(); ++i)
	{
		removeFils(fils->at(i));
	}

}

void AbstractObjet::addPointCollsion(Vector3d<GLdouble>* pt)
{
	_listPointsCollision.push_back(pt);
}

void AbstractObjet::addAxe(AxeAnimation* axe)
{
	_listAxes.push_back(axe);
}

void AbstractObjet::majCollider()
{
	_collider->reset();
	for (unsigned int i = 0; i < getFils()->size(); ++i)
	{
		_collider->addCollider(*getFils()->at(i)->_collider);

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


unsigned int AbstractObjet::affiche()
{
	unsigned int nbPointAffiche = 0;

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glPushMatrix();
	glMultMatrixd(getMatrice()->getMat());



	//on affiche les objets fils

	for (unsigned int i = 0; i < getFils()->size(); ++i)
	{
		nbPointAffiche += getFils()->at(i)->affiche();
	}


	//	for(std::list<AbstractObjet*>::const_iterator lit = getFils().begin();lit != getFils().end();++lit) 
	//	{
	//		std::cout << lit._Ptr << std::endl;
	//		(*lit)->affiche();
	//	}

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	return nbPointAffiche;
}

void AbstractObjet::toggleFilted()
{
	_isFilted = !_isFilted;
	for (unsigned int i = 0; i < getFils()->size(); ++i)
	{
		getFils()->at(i)->toggleFilted();
	}
}

void AbstractObjet::toggleVBO()
{
	_isVboActive = !_isVboActive;
	for (unsigned int i = 0; i < getFils()->size(); ++i)
	{
		getFils()->at(i)->toggleVBO();
	}
}

AbstractObjet* AbstractObjet::getPere()
{
	return _pere;
}
std::string AbstractObjet::getNom()
{
	return _nom;
}
void AbstractObjet::majPos()
{
	glPushMatrix();
	glMultMatrixd(getMatrice()->getMat());

	GLdouble* mat = (GLdouble*) malloc(16*sizeof(GLdouble));
	glGetDoublev(GL_MODELVIEW_MATRIX, mat);

	_matriceAbsolue->getVector16().clear();
	_matriceAbsolue->getVector16().assign(mat, mat + 16);
	Vector3d<GLdouble>* vect = getScale();
	if (vect->getX() != vect->getY())
	{
		//vect->println();
	}
	_matriceAbsolue->setSaveScale(*vect);
	delete vect;
	delete mat;
	//on maj les objets fils
	for (unsigned int i = 0; i < getFils()->size(); ++i)
	{
		getFils()->at(i)->majPos();
	}

	glPopMatrix();
}

bool AbstractObjet::isInCollisionWith(AbstractObjet* objet)
{
	if (_collider->getDistanceMax() != 0)
	{
		Vector3d<GLdouble> distance(objet->matriceAbsolue().getPosition().getX() - matriceAbsolue().getPosition().getX(), 
			objet->matriceAbsolue().getPosition().getY() - matriceAbsolue().getPosition().getY(),
			objet->matriceAbsolue().getPosition().getZ() - matriceAbsolue().getPosition().getZ() );
		if (distance.length() <= abs(_collider->getDistanceMax() + objet->getCollider()->getDistanceMax()) && isInCollisionWithFace(objet))
		{
			//std::cout << "cas 1 : " << distance.length() << " - " << _collider->getDistanceMax() << " - " << objet->getCollider()->getDistanceMax() << std::endl;
			//objet->matriceAbsolue().print();

			return true;
		}
		else
		{
			for (unsigned int i = 0; i < getFils()->size(); ++i)
			{
				if (getFils()->at(i)->isInCollisionWith(objet))
				{
					return true;
				}
			}
		}
		return false;
	}
	for (unsigned int i = 0; i < getFils()->size(); ++i)
		{
			if (getFils()->at(i)->isInCollisionWith(objet))
			{
				return true;
			}
		}
		
	return false;
}

Collider* AbstractObjet::getCollider()
{
	return _collider;
}

Vector3d<GLdouble>* AbstractObjet::getScale()
{
	Vector3d<GLdouble>* vec = new Vector3d<GLdouble>(matrice().getScale());
	if (getPere() != NULL)
	{
		Vector3d<GLdouble>* vecPere = getPere()->getScale();
		vec->setX(vecPere->getX() * vec->getX());
		vec->setY(vecPere->getY() * vec->getY());
		vec->setZ(vecPere->getZ() * vec->getZ());
		delete vecPere;
	}
	return vec;
}

bool AbstractObjet::isInCollisionWithFace(AbstractObjet* objet)
{
	return false;
}

std::vector<Vector3d<GLdouble>* >& AbstractObjet::getListePointsCollision()
{
	return _listPointsCollision;
}