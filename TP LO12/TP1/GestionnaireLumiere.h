#ifndef _GESTION_ECLAIRAGE_H
#define _GESTION_ECLAIRAGE_H

#include <iostream>
#include <vector>
#include "const.h"
#include "Singleton.h"
#include "Lumiere.h"


class GestionnaireLumiere : public Singleton<GestionnaireLumiere>
{
public:
	GestionnaireLumiere();

	Lumiere* newLumiere(Vector3d<GLdouble> amb, Vector3d<GLdouble> cou, GLdouble coefk, GLdouble angle, Matrice<GLdouble>* mat = NULL, std::string name = "lumiere_defaut");
	void setLumiereAmbiante(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha = 1);
	void def_modele();
	void defAllSources();
private:
	GLenum lumiere_i(unsigned int i);
private:
	std::vector<Lumiere* > _listLumiere;
	GLfloat  _lumiereAmbiante[4];
};

#endif