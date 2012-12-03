#include "Face.h"


Face::Face(Material* material)
{
	_material = material;
	_normale = NULL;
	_isFilted = false;
}


Face::~Face()
{
	for (unsigned int i = 0; i < _listePoints.size(); ++i)
	{
		delete (_listePoints.at(i));
	}

	for (unsigned int i = 0; i < _listeCoordonneesTextures.size(); ++i)
	{
		if (_listeCoordonneesTextures.at(i) != NULL)
		{
			delete (_listeCoordonneesTextures.at(i));
		}
	}
	if (_normale != NULL)
	{
		delete _normale;
	}
	delete _material;

}

void Face::affiche()
{

	if (_listeCoordonneesTextures.at(0) != NULL)
	{
		_material->appliqueTexture();
	}

	if (_isFilted)
	{
		glBegin(GL_LINE_LOOP); // affichage fils de fer
	}
	else
	{
		glBegin(GL_POLYGON);
	}
	//_eclairage->def_matiere(_scene->tabface[iface].imat);
	_material->appliqueMatiere();
	if (_normale != NULL)
	{
		glNormal3d(_normale->getX(), _normale->getY(),_normale->getZ());
	}
	else
	{
		std::cout << "Les normales n ont pas ete calculees ! Il faut utiliser la methode calculnormales !" << std::endl;
		calculeNormales();
	}

	float coordTex[4][2] = {{1,1},{0,1},{0,0},{1,0}} ;

	//glColor3f(scene->tabmat[scene->tabface[iface].imat].ambiante.r,scene->tabmat[scene->tabface[iface].imat].ambiante.g,scene->tabmat[scene->tabface[iface].imat].ambiante.b); 
	for (unsigned i = 0 ; i < _listePoints.size(); i++)/* boucle sur les points */
	{
		//glColor3f(0.0,(i+1.0)/scene->tabface[iface].nbpt,(scene->tabface[iface].nbpt-i+0.0)/scene->tabface[iface].nbpt); 
		if (_listeCoordonneesTextures.at(i) != NULL)
		{
			glTexCoord2d(_listeCoordonneesTextures.at(i)->getX(), _listeCoordonneesTextures.at(i)->getY());
		}	
		glVertex3d(_listePoints.at(i)->getX(), _listePoints.at(i)->getY(), _listePoints.at(i)->getZ());


	}
	glEnd();

}

void Face::calculeNormales()
{
	if (_listePoints.size() >= 3)
	{
		_normale = Outil::get()->produitVectoriel<GLdouble>(*_listePoints.at(1) - *_listePoints.at(0), *_listePoints.at(2) - *_listePoints.at(0));
		*_normale = (*_normale)/Outil::get()->norme(*_normale);
	}
}

void Face::addPoint(Vector3d<GLdouble>* coordonnees, Vector2d<GLdouble>* coordonnneesTexture)
{
	_listePoints.push_back(coordonnees);
	_listeCoordonneesTextures.push_back(coordonnneesTexture);
}

void Face::setTexture(GLuint texture)
{
	_material->setTextured(true);
	_material->setIndiceTex(texture);
}

void Face::toggleFilted()
{
	_isFilted = !_isFilted;
}