/*
 
        Universite de Technologie de Compiegne
        
        UV: LO12
        
        FICHIER: eclairage.cpp
 
        COMMENTAIRE:
                Routines d'eclairage
 
*/

#include <math.h>
#include <stdio.h>

#include <iostream>

#include "eclairage.h"
#include "const.h"


//extern SCENE* scene;




/*******************************************************************************/
/*                         Mise en place de l'eclairage                        */
/*******************************************************************************/

/* -----------------------------------------------
Cette fonction realise la norme euclidienne d'un
vecteur v.
On ne prend pas en compte la quatrieme composante.
----------------------------------------------- */



Eclairage::Eclairage(Scene* scene) : _scene(scene)
{
	
}

Eclairage::~Eclairage()
{
}



GLdouble Eclairage::norme(Scene::MCOORD v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z* v.z + v.w * v.w);
}



/* -----------------------------------------------
Cette fonction realise le produit vectoriel de deux
vecteurs
  w = u ^ v
----------------------------------------------- */

void Eclairage::prod_vectoriel(Scene::MCOORD u, Scene::MCOORD v, Scene::MCOORD *w)
{
	w->x = u.y * v.z - u.z * v.y;
	w->y = u.z * v.x - v.z * u.x;
	w->z = u.x * v.y - v.x * u.y;

}


/*****************************************************************************/
void Eclairage::calcule_normales()
{
	
	for (int iface = 0; iface < _scene->nbface; ++iface)
	{
		Scene::MCOORD x, y;

		x.x = _scene->tabpt[_scene->tabface[iface].tabpt[1]].x - _scene->tabpt[_scene->tabface[iface].tabpt[0]].x;
		x.y = _scene->tabpt[_scene->tabface[iface].tabpt[1]].y - _scene->tabpt[_scene->tabface[iface].tabpt[0]].y;
		x.z = _scene->tabpt[_scene->tabface[iface].tabpt[1]].z - _scene->tabpt[_scene->tabface[iface].tabpt[0]].z;

		y.x = _scene->tabpt[_scene->tabface[iface].tabpt[2]].x - _scene->tabpt[_scene->tabface[iface].tabpt[0]].x;
		y.y = _scene->tabpt[_scene->tabface[iface].tabpt[2]].y - _scene->tabpt[_scene->tabface[iface].tabpt[0]].y;
		y.z = _scene->tabpt[_scene->tabface[iface].tabpt[2]].z - _scene->tabpt[_scene->tabface[iface].tabpt[0]].z;


		prod_vectoriel(x, y, &_scene->tabface[iface].n);

		GLdouble valNorme = norme(_scene->tabface[iface].n);

		_scene->tabface[iface].n.x /= valNorme;
		_scene->tabface[iface].n.y /= valNorme;
		_scene->tabface[iface].n.z /= valNorme;
	}
}


/**********************************************************************/
GLenum Eclairage::lumiere_i(int i)
{
        GLenum source;
        switch (i) {
        case 0:
                source=GL_LIGHT0;
                break;
        case 1:
                source=GL_LIGHT1;
                break;
        case 2:
                source=GL_LIGHT2;
                break;
        case 3:
                source=GL_LIGHT3;
                break;
        case 4:
                source=GL_LIGHT4;
                break;
        case 5:
                source=GL_LIGHT5;
                break;
        case 6:
                source=GL_LIGHT6;
                break;
        case 7:
                source=GL_LIGHT7;
                break;
        }

        if (i<=7)
                return(source);
        else {
                printf("Attention: nombre de sources lumineuses depasse\n");
                return ((GLenum)GL_LIGHT7);
        }
}


void Eclairage::rgb2rgbaf(Scene::RGB *rgb,GLfloat alpha,Scene::RGBAF *rgbaf)
{
        rgbaf->r = rgb->r;
        rgbaf->g = rgb->g;
        rgbaf->b = rgb->b;
        rgbaf->a = alpha;
}

void Eclairage::mcoord2mcoordf(Scene::MCOORD *mcoord,Scene::MCOORDF *mcoordf)
{
        mcoordf->x = mcoord->x;
        mcoordf->y = mcoord->y;
        mcoordf->z = mcoord->z;
        mcoordf->w = mcoord->w;
}

/*****************************************************************************/
void Eclairage::def_sources(GLint i)
{             /* indice source */
        Scene::RGBAF propc;    /* tableau des proprietes de la source */
        Scene::MCOORDF propp;
        GLenum source;

        if( i < _scene->nbsource)   /* boucle sur les sources */
        {
                source=lumiere_i(i);

                if(_scene->tabsource[i].allume)
                {
					rgb2rgbaf( &_scene->tabsource[i].ambiante ,1,&propc);
					glLightfv(source,GL_AMBIENT,propc.rgba);

					rgb2rgbaf(&_scene->tabsource[i].couleur ,1,&propc);
					glLightfv(source,GL_DIFFUSE,propc.rgba);
					glLightfv(source,GL_SPECULAR,propc.rgba);

					mcoord2mcoordf(&_scene->tabsource[i].position,&propp);
					glLightfv(source,GL_POSITION,propp.vect);

					mcoord2mcoordf(&_scene->tabsource[i].direction,&propp);
					glLightfv(source,GL_SPOT_DIRECTION,propp.vect);

					glLightf(source,GL_SPOT_CUTOFF,_scene->tabsource[i].allure_faisceau.theta);
					glLightf(source,GL_SPOT_EXPONENT,_scene->tabsource[i].allure_faisceau.k);

					glEnable(source);
					
					afficherSphereSpot(i);

                }
				else
                {
					
					 glDisable(source);
				}
        }
}

void Eclairage::afficherSphereSpot(GLint i)
{
	GLUquadricObj *quadObj = gluNewQuadric();
	glDisable(GL_LIGHTING);
	glColor3d(_scene->tabsource[i].couleur.r, _scene->tabsource[i].couleur.g, _scene->tabsource[i].couleur.b);				
	glPushMatrix();
	glTranslatef(_scene->tabsource[i].position.x, _scene->tabsource[i].position.y, _scene->tabsource[i].position.z);
	gluSphere(quadObj, 0.1, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	gluDeleteQuadric(quadObj);

}

/*****************************************************************************/
void Eclairage::def_modele()
{
        Scene::RGBAF propc;

        propc.r = 0.8;
        propc.g = 0.8;
        propc.b = 0.8;
        propc.a = 1.0;
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,propc.rgba);

        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

}



/*****************************************************************************/
void Eclairage::def_matiere(int i)
{
        Scene::RGBAF propc;


		rgb2rgbaf(&_scene->tabmat[i].ambiante,1,&propc);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, propc.rgba);

        rgb2rgbaf(&_scene->tabmat[i].diffuse,1,&propc);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, propc.rgba);

        rgb2rgbaf(&_scene->tabmat[i].speculaire,1,&propc);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, propc.rgba);

        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _scene->tabmat[i].brillance);

        rgb2rgbaf(&_scene->tabmat[i].emission,1,&propc);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, propc.rgba);

}

void Eclairage::defAllSources()
{
	for (int i = 0; i < _scene->nbsource; ++i)
	{
		def_sources(i);
	}
}