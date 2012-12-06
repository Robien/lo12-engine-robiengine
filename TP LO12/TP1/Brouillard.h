#ifndef _BROUILLARD_H	
#define _BROUILLARD_H

#include "Vector3d.h"
#include "const.h"

class Brouillard
{

public:
	Brouillard();
	virtual ~Brouillard();

	void setActive(bool ac);
	void setDensite(float de);
private :
	void maj();

private: 

	bool   _active;                      
	//GLuint _filtre;                      
	//GLuint _mode[]= { GL_EXP, GL_EXP2, GL_LINEAR };  
	GLfloat _densite;
	GLfloat _debut;
	GLfloat _fin;
	Vector3d<GLfloat> _couleur;      
};

#endif