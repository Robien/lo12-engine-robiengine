#ifndef _LUMIERE_H	
#define _LUMIERE_H

#include "AbstractObjet.h"
#include "Vector3d.h"

class AllureFaisceau
{
public:
	AllureFaisceau(GLdouble k=2, GLdouble theta=180);
	virtual ~AllureFaisceau();
private:
	GLdouble _k;
    GLdouble _theta;
};

class Lumiere : public	AbstractObjet
{
public:
	Lumiere();
	virtual ~Lumiere();
	
	void def_sources(int i);
	void def_modele();
	void def_matiere(int i);
	void defAllSources();
	void affiche();
private :
	//GLenum lumiere_i(int i);
	//void rgb2rgbaf(Scene::RGB *rgb,GLfloat alpha,Scene::RGBAF *rgbaf);
	//void mcoord2mcoordf(Scene::MCOORD *mcoord,Scene::MCOORDF *mcoordf);

	

private :
	bool active;
	Vector3d<GLdouble> _ambiante;         /* couleur "ambiente" */
    Vector3d<GLdouble> _couleur;          /* couleur de la source */
    Vector3d<GLdouble> _position;         /* position de la source */
    AllureFaisceau _allure_faisceau;  /* allure du faisceau lumineux */
    Vector3d<GLdouble> _direction;        /* direction du faisceau lumineux */

	bool afficheSphere;
	GLUquadricObj* _sphere; //sphere
    //bool		allume;

};

#endif