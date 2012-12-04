#ifndef _LUMIERE_H	
#define _LUMIERE_H

#include "AbstractObjet.h"
#include "Vector3d.h"
#include "Matrice.h"

class AllureFaisceau
{
public:
	AllureFaisceau(GLdouble k=2, GLdouble theta=180);
	virtual ~AllureFaisceau();

	GLdouble getCoefK();
	GLdouble getAngle();
private:
	GLdouble _k;
    GLdouble _theta;
};

class Lumiere : public	AbstractObjet
{
public:
	Lumiere(std::string name = "lumiere_defaut");
	Lumiere(Matrice<GLdouble>* mat, Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, AllureFaisceau alf, std::string name = "lumiere_defaut");
	Lumiere(Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, AllureFaisceau alf, std::string name = "lumiere_defaut");
	virtual ~Lumiere();
	
	void def_sources(GLenum source);
	virtual void affiche();

	void setAfficheSphere(bool aff);
	void  toggle();

private:

	//void rgb2rgbaf(Scene::RGB *rgb,GLfloat alpha,Scene::RGBAF *rgbaf);
	//void mcoord2mcoordf(Scene::MCOORD *mcoord,Scene::MCOORDF *mcoordf);

	

private :
	bool _active;
	Vector3d<GLdouble> _ambiante;         /* couleur "ambiente" */
    Vector3d<GLdouble> _couleur;          /* couleur de la source */
   // Vector3d<GLdouble> _position;         /* position de la source */
    AllureFaisceau _allure_faisceau;  /* allure du faisceau lumineux */
   // Vector3d<GLdouble> _direction;        /* direction du faisceau lumineux */

	bool _afficheSphere;
	GLUquadricObj* _sphere; //sphere
    //bool		allume;

};

#endif