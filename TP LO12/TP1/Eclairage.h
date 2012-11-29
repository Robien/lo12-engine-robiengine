#ifndef ECLAIRAGE_H
#define ECLAIRAGE_H

#include "Scene.h"


class Eclairage
{

public :
	Eclairage(Scene* scene);
	virtual ~Eclairage();
	void calcule_normales();
	void def_sources(int i);
	void def_modele();
	void def_matiere(int i);
	void defAllSources();


private :
	GLdouble norme(Scene::MCOORD v);
	void prod_vectoriel(Scene::MCOORD u, Scene::MCOORD v, Scene::MCOORD *w);
	GLenum lumiere_i(int i);
	void rgb2rgbaf(Scene::RGB *rgb,GLfloat alpha,Scene::RGBAF *rgbaf);
	void mcoord2mcoordf(Scene::MCOORD *mcoord,Scene::MCOORDF *mcoordf);
	void afficherSphereSpot(GLint i);
private :
	Scene* _scene;

};
#endif

