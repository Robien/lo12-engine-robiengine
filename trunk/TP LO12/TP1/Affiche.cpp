/*
 
        Universite de Technologie de Compiegne
        
        UV: LO12
        
        FICHIER: affiche.c
 
        COMMENTAIRE:
                Routines d'affichage
 

*/

#include <iostream>
#include "const.h"

#include "Affiche.h"
#include "Skybox.h"
#include "Interactions.h"
#include "Observateur.h"
#include "Face.h"
#include "Material.h"
#include "Vector2d.h"
#include "Vector3d.h"


/*******************************************************************************/
/*            Fonctions pour afficher le contenu de la structure scene			*/
/*******************************************************************************/

Affiche::Affiche(Scene* scene, Eclairage* eclairage) : _scene(scene), _eclairage(eclairage)
{
}

Affiche::~Affiche()
{
}


void Affiche::dessine_face(Scene::INDICE_FACE iface)
{
	std::cout << "IL NE FAUT PAS UTILISER CETTE METHODE !!!" << std::endl;
		Face face(new Material());
		face.setTexture( _scene->_tabTexture[0]);
        int i;  /* compteur de point */
        int j;  /* indice  de point */
		
	//	glBindTexture(GL_TEXTURE_2D, _scene->_tabTexture[0]);
		
		//glBegin(GL_LINE_LOOP); // affichage fils de fer


	//	glBegin(GL_POLYGON);
	//	_eclairage->def_matiere(_scene->tabface[iface].imat);
		
	//	glNormal3d(_scene->tabface[iface].n.x, _scene->tabface[iface].n.y,  _scene->tabface[iface].n.z);
		
		float coordTex[4][2] = {{1,1},{0,1},{0,0},{1,0}} ;

		//glColor3f(scene->tabmat[scene->tabface[iface].imat].ambiante.r,scene->tabmat[scene->tabface[iface].imat].ambiante.g,scene->tabmat[scene->tabface[iface].imat].ambiante.b); 
        for (i = 0 ; i < _scene->tabface[iface].nbpt ; i++)/* boucle sur les points */
        {
				//glColor3f(0.0,(i+1.0)/scene->tabface[iface].nbpt,(scene->tabface[iface].nbpt-i+0.0)/scene->tabface[iface].nbpt); 
			j = _scene->tabface[iface].tabpt[i];
			face.addPoint(new Vector3d<GLdouble>(_scene->tabpt[j].x, _scene->tabpt[j].y, _scene->tabpt[j].z), new Vector2d<GLdouble>(coordTex[i][0], coordTex[i][1]));
		//	glTexCoord2d(coordTex[i][0], coordTex[i][1]);
		//	glVertex3d(_scene->tabpt[j].x, _scene->tabpt[j].y, _scene->tabpt[j].z);

				
        }
    //    glEnd();

		face.calculeNormales();
		face.affiche();

}


void Affiche::dessine_repere()
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

/*****************************************************************************/
void Affiche::dessine_objet(Scene::OBJET objet)
{
		std::cout << "IL NE FAUT PAS UTILISER CETTE METHODE !!!" << std::endl;
        int  i;      /* compteur de faces */
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for (i = 0 ; i < objet.nbface ; i++) 
		{
			dessine_face(objet.tabface[i]);
        }

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
}


/****************************************************************************/

void Affiche::dessine_skybox(Scene::MCOORD pos)
{
	_scene->_skybox->dessine_box(pos);
}


void Affiche::dessine_scene()
{
      //  int i;  /* indice d'objet */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  /*efface l'ecran */
		
		dessine_skybox(Interactions::get()->_ob->getPosition());

        dessine_repere();

        //glIndexi(2);		 /* couleur de la scene en mode index */
		//  glColor3f(1, .5,.5);   /* couleur de la scene en mode RGB   */
		
		_eclairage->defAllSources(); //definition des sources de lumiere
		
		
		_scene->affiche();

   //     for (i = 0 ; i < _scene->nbobj ; i++)     	/* boucle sur les objets */
     //   {
			//std::cout << scene->tabobj[i].transfo[0] << " - " << scene->tabobj[i].transfo[3] << " - " <<scene->tabobj[i].transfo[15] << std::endl;
		//	if(i==_scene->objetSelectionne)
		//	{
	//			glColor3f(1,1,1); //couleur des objets selectionnés
	//		}
	//		else
	//		{
	//			glColor3f(0.5,(i+1.0)/_scene->nbobj,0.0);
	//		}
	//		glPushMatrix();
	//		glMultMatrixd(_scene->tabobj[i].transfo);
     //       dessine_objet(_scene->tabobj[i]);
	//		glPopMatrix();
     //   }
		
        glutSwapBuffers();
		glutPostRedisplay();
}

/****************************************************************************/


