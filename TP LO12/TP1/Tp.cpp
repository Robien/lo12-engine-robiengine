/*

Universite de Technologie de Compiegne

UV: LO12

FICHIER: tp1.c

COMMENTAIRE:
Fichier principal
Interface OpenGL (GLUT, GLU, GL)


*/

//******************//
//Fichiers inclus : //
//******************//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Import.h"

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Tp.h"
#include "Interactions.h"
#include "AbstractObjet.h"
#include "SystemeParticules.h"
#include "Objet.h"
#include <vector>
#include "GestionnaireLumiere.h"
#include "GestionnaireTexture.h"
#include "CameraLookAt.h"




Tp::Tp()
{
	_scene = new Scene(new CameraLookAt());

}

Tp::~Tp()
{
}




/* ========================================================================= */
void Tp::run()
{

	_scene->createWindows();

	AbstractObjet* root = new AbstractObjet();

	Import imp;
	root->attache(imp.importer("models/testExport/RobienSimpleLOP.obj")); // manque un delete ... le faire dans attache ?
	root->attache(imp.importer("models/testExport/RobienFinal.obj"));

		SystemeParticules* sp = new SystemeParticules(true);
		sp->matrice().translate(0,0,-2);
		sp->start();
		root->attache(sp);

		
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


	_scene->run();

		


}


