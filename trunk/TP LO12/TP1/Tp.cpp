/*

Universite de Technologie de Compiegne

UV: LO12

FICHIER: tp1.c

COMMENTAIRE:
Fichier principal projet LO12
Interface OpenGL (GLUT, GLU, GL)
Auteurs : Guyard Romain, Louison Céphise
*/
#include "const.h"
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
#include "Texte.h"
#include "Interface.h"
#include "InterfaceVitesse.h"
#include "ShaderPhong.h"

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


	_scene->createWindows(HAUTEUR_FENETRE , LARGEUR_FENETRE);

	AbstractObjet* root = new AbstractObjet();

	{
		Vector3d<GLdouble> ambiante(0.8, 0.8, 0.8);
		Vector3d<GLdouble> couleur(0.3, 0.3, 0.3);
		Matrice<GLdouble> *m = new Matrice<GLdouble>();
		m->translate(0.3, 0, 0);
		m->rotate(90, 0, 1, 0);
		//m->getVector16().at(0) = -1;
		Lumiere* l = GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 2.0, 25.0, m);
		l->setAfficheSphere(true);
		camera->attache(l);
	}

	{
		Vector3d<GLdouble> ambiante(0.2, 0.2, 0.2);
		Vector3d<GLdouble> couleur(0.8, 0.1, 0.1);
		Matrice<GLdouble> *m = new Matrice<GLdouble>();
		m->translate(0.3, 0, 0);
		//m->rotate(90, 0, 1, 0);
		//m->getVector16().at(0) = -1;
		Lumiere* l = GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 2.0, 25.0, m);
		l->setAfficheSphere(true);
		root->attache(l);
	}

	{
		Vector3d<GLdouble> ambiante(0.2, 0.2, 0.2);
		Vector3d<GLdouble> couleur(0.1, 0.8, 0.1);
		Matrice<GLdouble> *m = new Matrice<GLdouble>();
		m->translate(0.3, 0, 0);
		m->rotate(180, 0, 1, 0);
		//m->getVector16().at(0) = -1;
		Lumiere* l = GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 2.0, 25.0, m);
		l->setAfficheSphere(true);
		root->attache(l);
	}
		{
		Vector3d<GLdouble> ambiante(0.2, 0.2, 0.2);
		Vector3d<GLdouble> couleur(0.1, 0.1, 0.8);
		Matrice<GLdouble> *m = new Matrice<GLdouble>();
		m->translate(0.3, 0, 0);
		m->rotate(270, 0, 1, 0);
		//m->getVector16().at(0) = -1;
		Lumiere* l = GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 2.0, 25.0, m);
		l->setAfficheSphere(true);
		root->attache(l);
	}


	Import imp;
	//permet d'avoir la taille du fichier
	std::cout << "Taille fichier" << imp.sizeOfFile("models/robien/RobienSimpleLOD.obj") << std::endl;
	root->attache(imp.importer("models/robien/RobienSimpleLOD.obj")); // manque un delete ... le faire dans attache ?
	//root->attache(imp.importer("models/robien/RobienSimple.obj"));
	AbstractObjet* vaisseau = imp.importer("models/explorerShip/vaisseau3.obj")->at(0);
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
	std::vector<AbstractObjet* >* vect = imp.importer("models/motherShip/motherShip.obj");
	vect->at(1)->addFils(vect->at(0));
	vect->at(1)->getMatrice()->rotate(90,1,0,0);
	vect->at(1)->matrice().scale(10, 10, 10);
	root->attache(vect->at(1));
	//vect = imp.importer("models/asteroides/LotAsteroids.obj");
	//unsigned int l = 5;//pow((float) vect->size(), (float) (1.0/3.0));
	//unsigned int m = 0;
	//for (unsigned int i = 0; i < l; ++i)
	//{
	//	for (unsigned int j = 0; j < l; ++j)
	//	{
	//		for (unsigned int k = 0; k < l; ++k)
	//		{
	//			std::cout << Outil::get()->random<unsigned int>(0, vect->size() - 1)  << " - " << vect->size() - 1 << std::endl;
	//			m = Outil::get()->random<unsigned int>(0, vect->size() - 1) ;
	//			AbstractObjet* ab = new AbstractObjet();
	//			//ab->matrice().rotate(Outil::get()->random<unsigned int>(0, 360), 0, 0, 1);
	//			//ab->matrice().rotate(Outil::get()->random<unsigned int>(0, 360), 0, 1, 0);
	//			//ab->matrice().rotate(Outil::get()->random<unsigned int>(0, 360), 1, 0, 0);
	//			ab->matrice().translate(200*i + 1000 + Outil::get()->random<unsigned int>(0, 190), 200*j + Outil::get()->random<unsigned int>(0, 190), 200*k + Outil::get()->random<unsigned int>(0, 190));
	//			ab->matrice().scale(20+Outil::get()->random<unsigned int>(0, 20), 20+Outil::get()->random<unsigned int>(0, 20), 20+Outil::get()->random<unsigned int>(0, 20));
	//			ab->attache(vect->at(m));
	//			root->attache(ab);
	//		}
	//	}
	//}
	//root->attache(vect);
	//	SystemeParticules* sp = new SystemeParticules(true, 1000);
	//	sp->matrice().translate(0,0,-2);
	//	sp->start();
	//	root->attache(sp);


	_scene->setRoot(root);

	//{
	//	Vector3d<GLdouble> ambiante(0.0,0.0, 0.0);
	//	Vector3d<GLdouble> couleur(0.1, 0.1, 0.1);
	//	Matrice<GLdouble> *m = new Matrice<GLdouble>();
	//	m->translate(0, 0, 2);
	//	//m->getVector16().at(10) = -1;
	//	vaisseau->attache(GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 5.0, 5.0, m));
	//}


	//Brouillard bou;
	_scene->add(new Texte("Mission : Recuperer les robiens", 0.25, 0.1));
	_scene->add(new Interface(0.45,0.45,0.1,0.1, "textures/center.png"));
	_scene->add(new InterfaceVitesse(0.15,0.01,0.08,0.08, "textures/power_Front.png", "textures/power_Back.png"));
	


	_scene->run();




}


