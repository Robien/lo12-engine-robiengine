/*

Universite de Technologie de Compiegne

UV: LO12

FICHIER: tp1.c

COMMENTAIRE:
Fichier principal
Interface OpenGL (GLUT, GLU, GL)


*/

#include "Import.h"
#include "Tp.h"
#include "AbstractObjet.h"
#include "SystemeParticules.h"
#include "Objet.h"
#include <vector>
#include "GestionnaireLumiere.h"
#include "CameraVaisseau.h"
#include "CameraLookAt.h"
#include "Brouillard.h"



Tp::Tp()
{
}

Tp::~Tp()
{
}




/* ========================================================================= */
void Tp::run()
{
	Camera* camera = new CameraVaisseau();

	_scene = new Scene(camera);

	_scene->createWindows(1024/1.2, 768/1.2);

	AbstractObjet* root = new AbstractObjet();

	Import imp;

	root->attache(imp.importer("models/robien/RobienSimpleLOD.obj")); // manque un delete ... le faire dans attache ?
	root->attache(imp.importer("models/robien/RobienSimple.obj"));
	AbstractObjet* vaisseau = imp.importer("models/explorerShip/vaisseau.obj")->at(0);
	vaisseau->matrice().scale(1, 1, 0.5);
	
	vaisseau->matrice().rotate(180, 0, 1, 0);
	//vaisseau->matrice().rotate(180, 0, 0, 0);
	vaisseau->matrice().rotate(5, 1, 0, 0);
	//vaisseau->matrice().rotate(180, 1, 0, 1);

	vaisseau->matrice().translate(0, -5, 0);
	vaisseau->matrice().translate(0, 0, 6);

//	vaisseau->matrice().rotate(180, 0, 1, 0);
//	vaisseau->matrice().translate(0, -4.2, 0);
//	vaisseau->matrice().translate(0, 0, 10.9);
	camera->attache(vaisseau);
	std::vector<AbstractObjet* >* vect= imp.importer("models/motherShip/motherShip.obj");
	vect->at(0)->getMatrice()->rotate(90,1,0,0);
	vect->at(0)->matrice().scale(10, 10, 10);
	root->attache(vect);

	//	SystemeParticules* sp = new SystemeParticules(true, 1000);
	//	sp->matrice().translate(0,0,-2);
	//	sp->start();
	//	root->attache(sp);

		
	_scene->setRoot(root);
	
	{
		Vector3d<GLdouble> ambiante(0.4,0.1, 0.1);
		Vector3d<GLdouble> couleur(0.1, 0.1, 0.1);
		Matrice<GLdouble> *m = new Matrice<GLdouble>();
		m->translate(0, 0, 2);
		m->getVector16().at(10) = -1;
		root->attache(GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 5.0, 5.0, m));
	}

	{
		Vector3d<GLdouble> ambiante(0.2, 0.2, 0.2);
		Vector3d<GLdouble> couleur(0.5, 0.5, 0.5);
		Matrice<GLdouble> *m = new Matrice<GLdouble>();
		m->translate(25, 0, 0);
		m->getVector16().at(0) = -1;
		root->attache(GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 2.0, 180.0, m));
	}

	//Brouillard bou;
	

	_scene->run();

		


}


