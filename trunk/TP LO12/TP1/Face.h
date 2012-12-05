#ifndef _FACE_H	
#define _FACE_H

#include "Vector2d.h"
#include "Vector3d.h"
#include "Outil.h"
#include "Material.h"
#include "Collider.h"

class Face
{
public:
	Face(Material* material);
	virtual ~Face();

public:
	//faire des new pour les différentes coordonnées et laisser la gestion de la mémoire à Face
	void addPoint(Vector3d<GLdouble>* coordonnees, Vector2d<GLdouble>* coordonnneesTexture = NULL);
	void calculeNormales();
	void setTexture(GLuint texture);
	Collider& getCollider();

public:
	virtual void affiche();
	void toggleFilted();

private:
	std::vector<Vector3d<GLdouble>* > _listePoints;
	std::vector<Vector2d<GLdouble>* > _listeCoordonneesTextures;
	Vector3d<GLdouble>* _normale;
	Material* _material;
	bool _isFilted;
	Collider _collider;

};

#endif