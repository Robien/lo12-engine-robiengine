#ifndef _MATERIAL_H	
#define _MATERIAL_H

#include "Vector3d.h"
#include "Outil.h"

class Material
{
public:
	Material();
	Material(Material const& c);
	virtual ~Material();

	bool isTextured();
	GLdouble getAlpha();
	Vector3d<GLdouble>*    getAmbiante();
	Vector3d<GLdouble>*    getDiffuse();
	Vector3d<GLdouble>*    getEmission();
	Vector3d<GLdouble>*    getSpeculaire();
	GLdouble getBrillance();      
	GLint getIndiceTex(); 

	void setTextured(bool ist);
	void getAlpha(GLdouble al);
	void getAmbiante(Vector3d<GLdouble>* am);
	void getAmbiante(GLdouble r, GLdouble g, GLdouble b);
	void getDiffuse(Vector3d<GLdouble>* di);
	void getDiffuse(GLdouble r, GLdouble g, GLdouble b);
	void getEmission(Vector3d<GLdouble>* em);
	void getEmission(GLdouble r, GLdouble g, GLdouble b);
	void getSpeculaire(Vector3d<GLdouble>* sp);
	void getSpeculaire(GLdouble r, GLdouble g, GLdouble b);
	void getBrillance(GLdouble br);      
	void getIndiceTex(GLint num); 


private:
	bool _textured;
	GLdouble _alpha;							/* coeff. de transparence */
	Vector3d<GLdouble>*    _ambiante;		/* couleur de la reflectance ambiante */
	Vector3d<GLdouble>*    _diffuse;			/* couleur de la reflectance diffuse */
	Vector3d<GLdouble>*    _emission;		/* couleur de la reflectance emise */
	Vector3d<GLdouble>*    _speculaire;		/* couleur de la reflectance speculaire */
	GLdouble _brillance;						/* coeff. de brillance */
	GLint _indiceTex;						/* indice de la texture */
};

#endif