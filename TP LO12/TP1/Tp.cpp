/*

Universite de Technologie de Compiegne

UV: LO12

FICHIER: tp1.c

COMMENTAIRE:
Fichier principal projet LO12
Interface OpenGL (GLUT, GLU, GL)
Auteurs : Guyard Romain, Louison C�phise
*/
#include <string>
#include <vector>
#include "const.h"

#include "Tp.h"
#include "Import.h"

#include "AbstractObjet.h"
#include "Objet.h"

#include "SystemeParticules.h"
#include "Brouillard.h"
#include "Texte.h"
#include "Interface.h"
#include "InterfaceVitesse.h"

#include "GestionnaireLumiere.h"
#include "ShaderPhong.h"

#include "CameraVaisseau.h"
#include "CameraLookAt.h"
#include "CameraPilotView.h"
#include "CameraPolarView.h"


#include "AnimationRotation.h"
#include "AnimationTranslation.h"
#include "AnimationPesanteur.h"
#include "AnimationPorte.h"
#include "AnimationSurchauffe.h"
#include "AnimationSuivre.h"
#include "AnimationTracter.h"

Tp::Tp()
{
}

Tp::~Tp()
{
}




/* ========================================================================= */
void Tp::run()
{	
	Import imp;
	{//ajout des tailles de tous les fichiers � importer
		std::cout << "Importation des fichiers des modeles 3D..." << std::endl;
		imp.addSizeOfFile("models/robien/RobienSimpleLOD.obj");
		imp.addSizeOfFile("models/explorerShip/vaisseau3.obj");
		imp.addSizeOfFile("models/motherShip/motherShip.obj");
		imp.addSizeOfFile("models/asteroides/LotAsteroids.obj");
	}


	CameraVaisseau* camera = new CameraVaisseau();
	_scene = new Scene(camera);
	_scene->addCam(new CameraLookAt());
	_scene->addCam(new CameraPilotView());
	_scene->addCam(new CameraPolarView());

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
		l->setAfficheSphere(false);
		camera->attache(l);
	}

	AbstractObjet* gyro = new AbstractObjet();
	//gyro->getMatrice()->translate(-420,50,100);
		//gyrophare
	{
		Vector3d<GLdouble> ambiante(0.2, 0.2, 0.2);
		Vector3d<GLdouble> couleur(0.8, 0.1, 0.1);
		Matrice<GLdouble> *m = new Matrice<GLdouble>();
		
		//m->rotate(90, 0, 1, 0);
		//m->getVector16().at(0) = -1;
		Lumiere* l = GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 2.0, 25.0, m);
		l->setAfficheSphere(true);
		gyro->attache(l);
	}
	{
		Vector3d<GLdouble> ambiante(0.2, 0.2, 0.2);
		Vector3d<GLdouble> couleur(0.1, 0.1, 0.8);
		Matrice<GLdouble> *m = new Matrice<GLdouble>();
		//m->translate(-420,50,100);
		m->rotate(180, 0, 1, 0);
		//m->getVector16().at(0) = -1;
		Lumiere* l = GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 2.0, 25.0, m);
		l->setAfficheSphere(true);
		gyro->attache(l);
	}
	
	root->attache(gyro);
	{
		Vector3d<GLdouble> ambiante(0.2, 0.2, 0.2);
		Vector3d<GLdouble> couleur(0.8, 0.8, 0.8);
		Matrice<GLdouble> *m = new Matrice<GLdouble>();
		m->translate(0.3, 0, 0);
		m->rotate(180, 0, 1, 0);
		//m->getVector16().at(0) = -1;
		Lumiere* l = GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 2.0, 0.0, m);
		l->setAfficheSphere(true);
		root->attache(l);
	}

	//Robien
	//permet d'avoir la taille du fichier
	std::vector<AbstractObjet* >* vect2 = imp.importer("models/robien/RobienSimpleLOD.obj");
	vect2->at(0)->getMatrice()->scale(2,2,2);
	new AnimationPesanteur(vect2->at(0));
	AbstractObjet* objvid1 = new AbstractObjet();
	objvid1->attache(vect2->at(0));


	//root->attache(imp.importer("models/robien/RobienSimple.obj"));
	{
		Vector3d<GLdouble> ambiante(0.2, 0.2, 0.2);
		Vector3d<GLdouble> couleur(0.1, 0.1, 0.8);
		Matrice<GLdouble> *m = new Matrice<GLdouble>();
		m->translate(0.3, 0, 0);
		//m->rotate(270, 0, 1, 0);
		//m->getVector16().at(0) = -1;
		Lumiere* l = GestionnaireLumiere::get()->newLumiere(ambiante,couleur, 2.0, 25.0, m);
		l->setAfficheSphere(true);
		vect2->at(0)->attache(l); 
	}


	

	
	
	//Vaisseau
	AbstractObjet* vaisseau = imp.importer("models/explorerShip/vaisseau3.obj")->at(0);
	//new AnimationTracter(objvid1,vaisseau); 
	root->attache(objvid1); 
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


	//vaisseau mere
	std::vector<AbstractObjet* >* vect = imp.importer("models/motherShip/motherShip.obj");
	//Gyrophare
	vect->at(0)->getMatrice()->translate(-40.58082,14.11398,-5.30275);
	vect->at(3)->addFils(vect->at(0));
	vect->at(0)->attache(gyro);
	//Porte
	vect->at(2)->getMatrice()->translate(-38.66924,3.40688,-5.26819);
	new AnimationPorte(vect->at(2), new AnimationRotation(vect->at(0), new Vector3d<int>(0, 1, 0), 8, false));
	vect->at(3)->addFils(vect->at(2));
	//vaisseauMere
	vect->at(3)->getMatrice()->rotate(90,1,0,0);
	vect->at(3)->matrice().scale(10, 10, 10);
	root->attache(vect->at(3));



	//Asteroides
	vect = imp.importer("models/asteroides/LotAsteroids.obj");
	unsigned int l = 5;//pow((float) vect->size(), (float) (1.0/3.0));
	unsigned int m = 0;
	for (unsigned int i = 0; i < l; ++i)
	{
		for (unsigned int j = 0; j < l; ++j)
		{
			for (unsigned int k = 0; k < l; ++k)
			{
				//std::cout << Outil::get()->random<unsigned int>(0, vect->size() - 1)  << " - " << vect->size() - 1 << std::endl;
				m = Outil::get()->random<unsigned int>(0, vect->size() - 1) ;
				AbstractObjet* ab = new AbstractObjet();
				//ab->matrice().rotate(Outil::get()->random<unsigned int>(0, 360), 0, 0, 1);
				//ab->matrice().rotate(Outil::get()->random<unsigned int>(0, 360), 0, 1, 0);
				//ab->matrice().rotate(Outil::get()->random<unsigned int>(0, 360), 1, 0, 0);
				ab->matrice().translate(200*i + 1000 + Outil::get()->random<unsigned int>(0, 190), 200*j + Outil::get()->random<unsigned int>(0, 190), 200*k + Outil::get()->random<unsigned int>(0, 190));
				ab->matrice().scale(20+Outil::get()->random<unsigned int>(0, 20), 20+Outil::get()->random<unsigned int>(0, 20), 20+Outil::get()->random<unsigned int>(0, 20));
				AbstractObjet* ab2 = new AbstractObjet();
				ab2->attache(vect->at(m));
				new AnimationPesanteur(ab2);
				ab->attache(ab2);
				root->attache(ab);
			}
		}
	}
	//root->attache(vect);
	//vect->at(0)->getMatrice()->translate(10,0,0);
/*	SystemeParticules* sp2 = new SystemeParticules(true, 4000);
	sp2->start();
	sp2->matrice().translate(0,4,0);
	root->attache(sp2);*/ 

	SystemeParticules* sp = new SystemeParticules(true, 2000);
	sp->matrice().translate(0,3,0);
	sp->matrice().rotate(-90,1,0,0);
	sp->start();

	vaisseau->attache(sp); 

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
	Interface* inter = new Interface(0.31,0.1,0.38,0.05);
	inter->setCouleur(1.0,1.0,0,0.5);
	Texte* texte  = new Texte(" !!! Surchauffe des moteurs !!!", 0.31, 0.1);
	texte->setCouleur(1.0,0,0);
	AnimationSurchauffe* anim = new AnimationSurchauffe(sp,texte,inter);
	_scene->add(inter);
	_scene->add(texte);
	_scene->add(new Interface(0.45,0.45,0.1,0.1, "textures/center.png"));
	InterfaceVitesse* interfaceVitesse = new InterfaceVitesse(0.15,0.01,0.08,0.08, "textures/power_Front.png",anim);
	camera->setInterfaceVitesse(interfaceVitesse);
	_scene->add(interfaceVitesse);


	imp.endImport();
	_scene->run();




}


