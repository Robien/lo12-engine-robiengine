#ifndef _FACE_H	
#define _FACE_H

#include "Vector2d.h"
#include "Vector3d.h"
#include "Outil.h"
#include "Material.h"

class Face
{
public:
	Face(Material* material);
	virtual ~Face();

public:
	//faire des new pour les diff�rentes coordonn�es et laisser la gestion de la m�moire � Face
	void addPoint(Vector3d<GLdouble>* coordonnees, Vector2d<GLdouble>* coordonnneesTexture = NULL);
	void calculeNormales();
	void setTexture(GLuint texture);

public:
	virtual void affiche();

private:
	std::vector<Vector3d<GLdouble>* > _listePoints;
	std::vector<Vector2d<GLdouble>* > _listeCoordonneesTextures;
	Vector3d<GLdouble>* _normale;
	Material* _material;
};

#endif