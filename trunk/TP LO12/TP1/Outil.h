#ifndef _OUTIL_H	
#define _OUTIL_H

#include "const.h"
#include "Pngloader.h"
#include "Singleton.h"
#include "Vector3d.h"
#include <math.h>


class Outil : public Singleton<Outil>
{
public:
	template <typename T>
	Vector3d<T>* produitVectoriel(Vector3d<T> u, Vector3d<T> v)
	{
		Vector3d<T>* w = new Vector3d<T>();

		w->setX(u.getY() * v.getZ() - u.getZ() * v.getY());
		w->setY(u.getZ() * v.getX() - v.getZ() * u.getX());
		w->setZ(u.getX() * v.getY() - v.getX() * u.getY());

		return w;
	}
	template <typename T>
	T norme( Vector3d<T>& u)
	{
		return sqrt(u.getX() * u.getX() + u.getY() * u.getY() + u.getZ() * u.getZ());
	}

};

#endif