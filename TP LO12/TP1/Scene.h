/*
 
        Universite de Technologie de Compiegne
        
        UV: LO12
        
        FICHIER: scene.h
 
        COMMENTAIRE:
                Definition de la stucture de la scene
 
    
*/

#ifndef SCENE_H
#define SCENE_H

#include "const.h"
#include <vector>
#include "AbstractObjet.h"
#include "Camera.h"
#include "Interactions.h"
#include "Skybox.h"


class AbstractObjet;


class Scene
{

public:
	Scene(Camera* mainCamera = NULL);
	Scene(AbstractObjet* root, Camera* mainCamera = NULL);
	virtual ~Scene();

	void setRoot(AbstractObjet* root);
	void affiche();

	void toggleFilted();

public:

	void resetObjet();
	void changerObjetSelectionne();

	void translateObjetSelectionne(GLdouble x,GLdouble y,GLdouble z);
	void rotateObjetSelectionne(GLdouble x,GLdouble y,GLdouble z, GLdouble angle);
	AbstractObjet* getRoot();
	void dessine_repere();
	
public:
	void run();
	void createWindows();

private:

	int objetSelectionne;
	std::vector<GLuint> _tabTexture;
	Skybox* _skybox;
	

	AbstractObjet* _root;
	Camera* _mainCamera;




};




#endif

















