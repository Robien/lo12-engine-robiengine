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
	GLfloat getAlpha();
	Vector3d<GLfloat>*    getAmbiante();
	Vector3d<GLfloat>*    getDiffuse();
	Vector3d<GLfloat>*    getEmission();
	Vector3d<GLfloat>*    getSpeculaire();
	GLfloat getBrillance();      
	GLint getIndiceTex(); 

	void setTextured(bool ist);
	void getAlpha(GLfloat al);
	void getAmbiante(Vector3d<GLfloat>* am);
	void getAmbiante(GLfloat r, GLfloat g, GLfloat b);
	void getDiffuse(Vector3d<GLfloat>* di);
	void getDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void getEmission(Vector3d<GLfloat>* em);
	void getEmission(GLfloat r, GLfloat g, GLfloat b);
	void getSpeculaire(Vector3d<GLfloat>* sp);
	void getSpeculaire(GLfloat r, GLfloat g, GLfloat b);
	void getBrillance(GLfloat br);      
	void getIndiceTex(GLint num); 

	void appliqueTexture();
	void appliqueMatiere();
	

private:
	bool _textured;
	GLfloat _alpha;							/* coeff. de transparence */
	Vector3d<GLfloat>*    _ambiante;		/* couleur de la reflectance ambiante */
	Vector3d<GLfloat>*    _diffuse;			/* couleur de la reflectance diffuse */
	Vector3d<GLfloat>*    _emission;		/* couleur de la reflectance emise */
	Vector3d<GLfloat>*    _speculaire;		/* couleur de la reflectance speculaire */
	GLfloat _brillance;						/* coeff. de brillance */
	GLint _indiceTex;						/* indice de la texture */
};

#endif