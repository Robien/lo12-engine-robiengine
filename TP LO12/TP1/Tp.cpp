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
	_scene = new Scene(new CameraVaisseau());
}

Tp::~Tp()
{
}




/* ========================================================================= */
void Tp::run()
{

	_scene->createWindows(1024/1.2, 768/1.2);

	AbstractObjet* root = new AbstractObjet();

	Import imp;
	//root->attache(imp.importer("models/testExport/RobienSimpleLOP.obj")); // manque un delete ... le faire dans attache ?
	//root->attache(imp.importer("models/testExport/RobienFinal.obj"));
	std::vector<AbstractObjet* >* vect= imp.importer("models/motherShip/motherShip.obj");
	vect->at(0)->getMatrice()->rotate(90,1,0,0);
	root->attache(vect);

	//	SystemeParticules* sp = new SystemeParticules(true);
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


