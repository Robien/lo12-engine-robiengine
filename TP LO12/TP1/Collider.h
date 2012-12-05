#ifndef _COLLIDER_H	
#define _COLLIDER_H

#include "Vector3d.h"
#include "Outil.h"

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

private:
	Vector3d<GLdouble> _CoordMin;
	Vector3d<GLdouble> _CoordMax;

	bool _isSet;

};

#endif
