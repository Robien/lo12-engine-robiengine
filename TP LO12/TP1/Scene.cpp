/*
 
        Universite de Technologie de Compiegne
        
        UV: LO12
        
        FICHIER: scene.c
 
        COMMENTAIRE:
                variables globales

*/

#include "Scene.h"

#include <stdio.h>
#include <stdlib.h>
#include "Texture.h"
#include "Skybox.h"


Scene::~Scene()
{
}
Scene::Scene()
{
	_skybox = new Skybox();
	objetSelectionne = 0;
	_root = new AbstractObjet();
}
Scene::Scene(AbstractObjet* root) : _root(root)
{
	_skybox = new Skybox();
	objetSelectionne = 0;
}
void Scene::resetObjet()
{
	glPushMatrix();
	glLoadIdentity();
	//glGetDoublev(GL_MODELVIEW_MATRIX,tabobj[objetSelectionne].transfo);
	_root->getFils()->at(objetSelectionne)->matrice().reset();
	glPopMatrix();
}

void Scene::changerObjetSelectionne()
{
	objetSelectionne = (objetSelectionne+1)%_root->getFils()->size(); 
}


void Scene::translateObjetSelectionne(GLdouble x,GLdouble y,GLdouble z)
{

	_root->getFils()->at(objetSelectionne)->matrice().translate(x, y, z);

	/*
	glPushMatrix();
	glLoadIdentity();
	glTranslated(x,y,z);
	glMultMatrixd(tabobj[objetSelectionne].transfo);
	glGetDoublev(GL_MODELVIEW_MATRIX,tabobj[objetSelectionne].transfo);
	glPopMatrix();
	*/
}


void Scene::rotateObjetSelectionne(GLdouble x,GLdouble y,GLdouble z, GLdouble angle)
{
	_root->getFils()->at(objetSelectionne)->matrice().rotate(angle, x, y, z);
	/*
	glPushMatrix();
	glLoadIdentity();
	glMultMatrixd(tabobj[objetSelectionne].transfo);
	glRotated(angle,x,y,z);
	glGetDoublev(GL_MODELVIEW_MATRIX,tabobj[objetSelectionne].transfo);
	glPopMatrix();
	*/
}


void Scene::setRoot(AbstractObjet* root)
{
	_root = root;
}

void Scene::affiche()
{
	if (_root != NULL)
	{
		_root->affiche();
	}
}