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
#include "SceneUtils.h"
#include "Interactions.h"
#include "Pngloader.h"
#include "AbstractObjet.h"
#include "Objet.h"
#include <vector>
#include "GestionnaireLumiere.h"




Tp::Tp()
{
	

	_scene = new Scene();
	_ob = new Observateur();
	Outil::get()->initManager(_scene);

}

Tp::~Tp()
{
}



/*******************************************************************************/
/*                      Initialisations pour GL et Glut                        */
/*******************************************************************************/

void Tp::init()
{
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90,1.0,0.1,100) ;

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

        /* mode RGB : choix de la couleur de fond */
        glClearColor(0.4,0.4,0.4,1);

        /* applique la couleur de fond */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		
		glShadeModel(GL_SMOOTH);
		//glShadeModel(GL_FLAT);
		//_eclairage->def_modele();
		Interactions::get()->initInteraction(_ob, _scene);

		for (int i = 0; i < _scene->nbsource; ++i)
		{
			_scene->tabsource[i].allume = true;
		}

		Outil::get()->addTexture("textures\\bois.png");
		_scene->_skybox->charger();
		

//		_scene->_skybox->dessine_box(_ob->getPosition());
		
}





/* ========================================================================= */
void Tp::run(char* filename, int verbose)
{



		if(SceneUtils().read_scene_file(_scene,filename)) {
                printf("Il y a un probleme: je ne peux pas lire le fichier: %s\n",filename);
				system("PAUSE");
                exit(-1);
        }

        if(verbose) {
                SceneUtils().print_scene_data(_scene);
        }
		
		//_eclairage->calcule_normales();

        glutInitWindowSize(800, 600);   /* taille de la fenetre ecran */
		glutInitWindowPosition(100, 100);
		glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);     /* mode rgb et zbuffer*/
		/*glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE);     /* mode rgb */
		 /* glutInitDisplayMode(GLUT_INDEX | GLUT_SINGLE);  /* mode index*/

		
		//glDepthFunc(GL_LESS);
       
		
		
		glutCreateWindow("TP1:cube");
		init();


		AbstractObjet* root = new AbstractObjet();

		//std::vector<AbstractObjet*>* listeObjets = new std::vector<AbstractObjet*>();


		
		/*for (int i = 0 ; i < _scene->nbobj ; i++)     	//boucle sur les objets 
		{
			Objet* tmp = new Objet(new Matrice<GLdouble>(_scene->tabobj[i].transfo));

			for (int j = 0 ; j < _scene->tabobj[i].nbface ; j++) 
			{

				Material* material = new Material();
				Face* face = new Face(material);
				face->setTexture(Outil::get()->addTexture("textures\\bois.png"));
				float coordTex[4][2] = {{1,1},{0,1},{0,0},{1,0}} ;
				for (int k = 0 ; k < _scene->tabface[_scene->tabobj[i].tabface[j]].nbpt ; k++) // boucle sur les points 
				{

					int l = _scene->tabface[_scene->tabobj[i].tabface[j]].tabpt[k];
					face->addPoint(new Vector3d<GLdouble>(_scene->tabpt[l].x, _scene->tabpt[l].y, _scene->tabpt[l].z), new Vector2d<GLdouble>(coordTex[k][0], coordTex[k][1]));

				}

				face->calculeNormales();
				tmp->addFace(face);
			}

			root->attache(tmp);
			
		}*/
		Import imp;
		std::vector<Objet* >* listobj = imp.importer("models/testExport/RobienSimpleLOP.obj");
		
		for(unsigned int i =0; i < listobj->size(); i++)
		{
			//listobj->at(i)->matrice().rotate(90, 0, 0, 1);
			//listobj->at(i)->afficheString();
			//listobj->at(i)->
			root->attache(listobj->at(i));
		}
		
		listobj = imp.importer("models/testExport/RobienFinal.obj");
		
		for(unsigned int i =0; i < listobj->size(); i++)
		{
			//listobj->at(i)->matrice().rotate(0, 0, 90, 1);
			//listobj->at(i)->afficheString();
			//listobj->at(i)->
			root->attache(listobj->at(i));
		}
		
		_scene->setRoot(root);


		for (int i = 0; i < _scene->nbsource; ++i)
		{
			Vector3d<GLdouble> ambiante(_scene->tabsource[i].ambiante.r, _scene->tabsource[i].ambiante.g, _scene->tabsource[i].ambiante.b);
			Vector3d<GLdouble> couleur(_scene->tabsource[i].couleur.r, _scene->tabsource[i].couleur.g, _scene->tabsource[i].couleur.b);
			Matrice<GLdouble> *m = new Matrice<GLdouble>();
			m->translate(_scene->tabsource[i].position.x, _scene->tabsource[i].position.y, _scene->tabsource[i].position.z);
			
			root->attache(GestionnaireLumiere::get()->newLumiere(ambiante,couleur, _scene->tabsource[i].allure_faisceau.k, _scene->tabsource[i].allure_faisceau.theta, m));

		}

		GestionnaireLumiere::get()->def_modele();
		glutMainLoop();

}


