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

#include "Interactions.h"

class Skybox;

class keyEvent : public CB_Interraction
{
	virtual void eventsKey(unsigned char key, int x, int y)
	{
		std::cout << "ceci est un test" << std::endl;
	}
};

Scene::~Scene()
{
}
Scene::Scene(Camera* mainCamera) : _mainCamera(mainCamera)
{
	_skybox = new Skybox();
	objetSelectionne = 0;
	_root = new AbstractObjet();
	if (_mainCamera == NULL)
	{
		_mainCamera = new Camera();
	}
	Interactions::get()->addEventCallBack(new keyEvent());

}
Scene::Scene(AbstractObjet* root, Camera* mainCamera) : _root(root), _mainCamera(mainCamera)
{
	_skybox = new Skybox();
	objetSelectionne = 0;
	if (_mainCamera == NULL)
	{
		_mainCamera = new Camera();
	}
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
void Scene::toggleFilted()
{
	_root->toggleFilted();
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
//	_mainCamera->affiche();
	if (_root != NULL)
	{
		_root->affiche();
	}

	/*
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		dessine_skybox(Interactions::get()->_ob->getPosition());

        dessine_repere();

        
		_eclairage->defAllSources(); //definition des sources de lumiere
		
		
		_scene->affiche();

		
        glutSwapBuffers();
		glutPostRedisplay();


		*/

}
AbstractObjet* Scene::getRoot()
{
	return _root;
}