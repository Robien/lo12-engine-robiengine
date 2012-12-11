#ifndef _COLLIDER_H	
#define _COLLIDER_H

#include "Vector3d.h"
#include "Outil.h"
#include "Matrice.h"

class Collider
{
public:
	Collider();
	virtual ~Collider();
	
public:
	void addPoint(Vector3d<GLdouble>& point);
	void addCollider(Collider& collider);
	void reset();

public:
	bool colide(Vector3d<GLdouble>& point);

public:
	Vector3d<GLdouble> getMin();
	Vector3d<GLdouble> getMax();

public:
	void affiche();
	void afficheWithMat(Matrice<GLdouble>* mat, Matrice<GLdouble>* m);
	void majMatrice(Matrice<GLdouble>* mat);

	GLdouble getDistanceMax();

private:
	Vector3d<GLdouble> _CoordMin;
	Vector3d<GLdouble> _CoordMax;

	bool _isSet;

	GLdouble _distanceMax;
	Matrice<GLdouble> _matrice;

};

#endif
