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
#include "VBOMangaer.h"

#include "GestionnaireLumiere.h"
#include <sstream>  

#include "ShaderPhong.h"


class DefautInteraction : public CB_Interraction
{
public:
	DefautInteraction(Scene* scene):_scene(scene)
	{
		_isOnPause = false;
		_isVBOactive = true;
		_lastUpdateWindowsTitle = 1000; // pour afficher le titre dès le début
	}
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
		case GLUT_KEY_F7:	/*_scene->toggleFilted();*/	_scene->toggleVBO(); _isVBOactive=!_isVBOactive; break;

		}
	}
	virtual void eventsKey(unsigned char key, int x, int y)
	{
		switch(key)
		{
		case 27:	exit(0);	break;
		case 32 :	_scene->changerObjetSelectionne();	break;
		case 105 :  _scene->resetObjet();	break;
		case 'p' : if (_isOnPause) { _scene->unpause();}else{_scene->pause();} _isOnPause = !_isOnPause;

		}
	}
	virtual void eventsMouse(int boutton, int etat, int x, int y){}
	virtual void eventsMotionMouse(int x, int y){}
	virtual void idle()
	{
	
		if ((_lastUpdateWindowsTitle += Interactions::get()->getDeltaTime()) > 1000) //1000ms = 1s
		{
			_lastUpdateWindowsTitle = 0;
			std::ostringstream oss;

			oss << "FPS : "  << nbFrame;
			if (_isVBOactive)
			{
				oss << " VBO activé";
			}
			else
			{
				oss << " VBO désactivé";
			}
			oss << " Faces affiché : " << (_scene->getNombrePointAffiche()/3);
			glutSetWindowTitle( oss.str().c_str());
			_scene->affiche();
			nbFrame = 0;
		}
	}
	virtual void reshape(int largeur, int hauteur)
	{
	}
	virtual void dessine_scene()
	{
		nbFrame++;
		_scene->affiche();
	}

private:
	unsigned int _lastUpdateWindowsTitle;
	unsigned int nbFrame;
	
	bool _isVBOactive;
	bool _isOnPause;

};







Scene::~Scene()
{
	for(unsigned int i = 0; i< _listTexte.size(); ++i)
	{
		delete(_listTexte.at(i));
	}
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
	Interactions::get()->addEventCallBack(new DefautInteraction(this));

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
void Scene::toggleVBO()
{
	_root->toggleVBO();
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

	_shader->setIdTexture(0);

	_nbPointAffiche = 0;
	//_mainCamera->affiche(); // il ne faut pas afficher la caméra pour bien avoir les valeurs des matrices en absolu
	glLoadIdentity();
	_mainCamera->majPos();
	_root->majPos();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,1.0,0.01,1000000) ;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_shader->desactive();
	_mainCamera->affiche();
	_skybox->dessine_box();
		_shader->active();
	GestionnaireLumiere::get()->defAllSources();

	_nbPointAffiche += _mainCamera->afficheFils();


	dessine_repere();

	

	if (_root != NULL)
	{
		_nbPointAffiche += _root->affiche();
	}

	_shader->desactive();

	for(unsigned int k = 0; k< _listInterface.size(); ++k)
	{
		_listInterface.at(k)->affiche();
	}

	_shader->active();

	for(unsigned int i = 0; i< _listTexte.size(); ++i)
	{
		_listTexte.at(i)->affiche();
	}
	glutSwapBuffers();
	glutPostRedisplay();

}
AbstractObjet* Scene::getRoot()
{
	return _root;
}


void Scene::add(Texte* txt)
{
	_listTexte.push_back(txt);
}
void Scene::add(Interface* inter)
{
	_listInterface.push_back(inter);
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

Vector2d<int>* Scene::getDimensions()
{
	std::cout << "Attention ne prend pas en compte le resize !" << std::endl;
	return _windowsSize;
}

void Scene::createWindows(int hauteur, int largeur)
{
	_windowsSize = new Vector2d<int>(hauteur, largeur);
	glutInitWindowSize(largeur,hauteur);   /* taille de la fenetre ecran */
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);     /* mode rgb et zbuffer*/
	/*glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE);     /* mode rgb */
	/* glutInitDisplayMode(GLUT_INDEX | GLUT_SINGLE);  /* mode index*/


	//glDepthFunc(GL_LESS);



	glutCreateWindow("TP1:cube");

	VBOMangaer::get()->init();

	Interactions::get()->initInteraction();
	_mainCamera->affiche();

}

/*******************************************************************************/
/*                      Initialisations pour GL et Glut                        */
/*******************************************************************************/

void Scene::run()
{


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,1.0,0.01,1000000) ;

	//Observateur().pilotView(2, 2, 2, -45,0, 15);
	//ob->polarView(5, 45, 45, 0);

	/*
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5,3,3,0,0,0,0,0,1);

	initialise la table des couleurs : mode index
	glutSetColor(1,0.0, 0.0, 0.0);
	glutSetColor(2,1.0, 0.3, 0.3);
	choix de la couleur de fond 
	glClearIndex(1.0);*/

	//glShadeModel(GL_SMOOTH);

	//glShadeModel(GL_FLAT);

	/* mode RGB : choix de la couleur de fond */
	glClearColor(0.4,0.4,0.4,1);

	/* applique la couleur de fond */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	///*Permet d'ameliorer le rendu
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	// */




	_skybox->charger();
	_shader = new Shader("phong");
	_shader->init();

	GestionnaireLumiere::get()->def_modele();





	glutMainLoop();
}



unsigned int Scene::getNombrePointAffiche()
{
	return _nbPointAffiche;
}

void Scene::pause()
{
	_mainCamera->pause();
}
void Scene::unpause()
{
	_mainCamera->unpause();
}