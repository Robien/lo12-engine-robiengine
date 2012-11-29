#ifndef _FACE_H	
#define _FACE_H

#include "Vector2d.h"
#include "Vector3d.h"
#include "Outil.h"

class Face
{
public:
	Face(GLuint texture = NULL);
	virtual ~Face();

public:
	//faire des new pour les différentes coordonnées et laisser la gestion de la mémoire à Face
	void addPoint(Vector3d<GLdouble>* coordonnees, Vector2d<GLdouble>* coordonnneesTexture = NULL);
	void calculeNormales();

public:
	virtual void affiche();

private:
	std::vector<Vector3d<GLdouble>* > _listePoints;
	std::vector<Vector2d<GLdouble>* > _listeCoordonneesTextures;
	Vector3d<GLdouble>* _normale;
	GLuint _texture;
};

#endif