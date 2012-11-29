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
#include "affiche.h"
#include "Interactions.h"
#include "Pngloader.h"





Tp::Tp()
{
	

	_scene = new Scene();
	_eclairage = new Eclairage(_scene);
	_affiche = new Affiche(_scene, _eclairage);
	_ob = new Observateur(_eclairage);
	Texture::get()->initManager(_scene);

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
		_eclairage->def_modele();
		Interactions::get()->initInteraction(_ob, _scene, _affiche);

		for (int i = 0; i < _scene->nbsource; ++i)
		{
			_scene->tabsource[i].allume = true;
		}

		Texture::get()->addTexture("textures\\bois.png");
		_scene->_skybox->charger();
		

		_scene->_skybox->dessine_box(_ob->getPosition());
		
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
		
		_eclairage->calcule_normales();

        glutInitWindowSize(800, 600);   /* taille de la fenetre ecran */
		glutInitWindowPosition(100, 100);
		glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);     /* mode rgb et zbuffer*/
		/*glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE);     /* mode rgb */
		 /* glutInitDisplayMode(GLUT_INDEX | GLUT_SINGLE);  /* mode index*/

		
		//glDepthFunc(GL_LESS);
       
		
		
        glutCreateWindow("TP1:cube");
	     init();
		
        glutMainLoop();

}


