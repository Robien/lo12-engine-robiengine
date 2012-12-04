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
#include "GestionnaireLumiere.h"

class Skybox;

class DefautInteraction : public CB_Interraction
{
public:
	DefautInteraction(Scene* scene):_scene(scene)
	{}
	~DefautInteraction(){}
private:
	Scene* _scene;
public:
	virtual void eventsSpecialKey(int key, int x, int y)
	{
		float mult = 0.1;
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
		{
			mult *= -1;
		}


		switch(key)
		{
		case GLUT_KEY_F1:	_scene->translateObjetSelectionne(1*mult,0,0);	break;
		case GLUT_KEY_F2:	_scene->translateObjetSelectionne(0,1*mult,0);	break;
		case GLUT_KEY_F3:	_scene->translateObjetSelectionne(0,0,1*mult);	break;
		case GLUT_KEY_F4:	_scene->rotateObjetSelectionne(1,0,0,90*mult);	break;
		case GLUT_KEY_F5:	_scene->rotateObjetSelectionne(0,1,0,90*mult);	break;
		case GLUT_KEY_F6:	_scene->rotateObjetSelectionne(0,0,1,90*mult);	break;
		case GLUT_KEY_F7:	_scene->toggleFilted();	break;

		}
	}
	virtual void eventsKey(unsigned char key, int x, int y)
	{
		switch(key)
		{
		case 27:	exit(0);	break;
		case 32 :	_scene->changerObjetSelectionne();	break;
		case 105 :  _scene->resetObjet();	break;

		}
	}
	virtual void eventsMouse(int boutton, int etat, int x, int y){}
	virtual void eventsMotionMouse(int x, int y){}
	virtual void idle()
	{
		_scene->affiche();
	}
	virtual void reshape(int largeur, int hauteur)
	{
	}
	virtual void dessine_scene()
	{
		_scene->affiche();
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
	Interactions::get()->addEventCallBack(new DefautInteraction(this));

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
	_root->getFils()->at(objetSelectionne)->matrice().reset();
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	_skybox->dessine_box();

	dessine_repere();

	GestionnaireLumiere::get()->defAllSources();

	if (_root != NULL)
	{
		_root->affiche();
	}



	glutSwapBuffers();
	glutPostRedisplay();

}
AbstractObjet* Scene::getRoot()
{
	return _root;
}



void Scene::dessine_repere()
{
	glDisable(GL_LIGHTING);

	glBegin(GL_LINES);
	glColor3f(1.0,0.0,0.0);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(10.0,0,0);

	glColor3f(0.0,1.0,0);
	glVertex3d(0.0,0,0);
	glVertex3d(0.0,10,0);

	glColor3f(0.0,0,1);
	glVertex3d(0.0,0,0);
	glVertex3d(0.0,0,10);

	glColor3f(1,1,1);
	glEnd();

}