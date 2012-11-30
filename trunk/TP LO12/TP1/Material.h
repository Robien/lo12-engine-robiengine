#ifndef _MATERIAL_H	
#define _MATERIAL_H

#include "Vector3d.h"
#include "Outil.h"
#include <iostream>

class Material
{
public:
	Material();
	Material(std::string nom);
	Material(Material const& c);
	virtual ~Material();

	bool isTextured();
	std::string getNom();
	GLfloat getAlpha();
	Vector3d<GLfloat>*    getAmbiante();
	Vector3d<GLfloat>*    getDiffuse();
	Vector3d<GLfloat>*    getEmission();
	Vector3d<GLfloat>*    getSpeculaire();
	GLfloat getBrillance();      
	GLuint getIndiceTex(); 

	void setTextured(bool ist);
	void setNom(std::string n);
	void setAlpha(GLfloat al);
	void setAmbiante(Vector3d<GLfloat>* am);
	void setAmbiante(GLfloat r, GLfloat g, GLfloat b);
	void setDiffuse(Vector3d<GLfloat>* di);
	void setDiffuse(GLfloat r, GLfloat g, GLfloat b);
	void setEmission(Vector3d<GLfloat>* em);
	void setEmission(GLfloat r, GLfloat g, GLfloat b);
	void setSpeculaire(Vector3d<GLfloat>* sp);
	void setSpeculaire(GLfloat r, GLfloat g, GLfloat b);
	void setBrillance(GLfloat br);      
	void setIndiceTex(GLuint num); 

	void appliqueTexture();
	void appliqueMatiere();
	
	void afficheString();

private:
	bool _textured;
	std::string _nom;
	GLfloat _alpha;							/* coeff. de transparence */
	Vector3d<GLfloat>*    _ambiante;		/* couleur de la reflectance ambiante */
	Vector3d<GLfloat>*    _diffuse;			/* couleur de la reflectance diffuse */
	Vector3d<GLfloat>*    _emission;		/* couleur de la reflectance emise */
	Vector3d<GLfloat>*    _speculaire;		/* couleur de la reflectance speculaire */
	GLfloat _brillance;						/* coeff. de brillance */
	GLuint _indiceTex;						/* indice de la texture */
};

#endif