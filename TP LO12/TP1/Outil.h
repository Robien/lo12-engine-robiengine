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
	template <typename T>
	Vector3d<T>* centreGravite(Vector3d<T>* u, Vector3d<T>* v, Vector3d<T>* w)
	{
		Vector3d<T>* g = new Vector3d<T>();

		g->setX( (u->getX() + v->getX() + w->getX()) / 3.0);
		g->setY( (u->getY() + v->getY() + w->getY()) / 3.0);
		g->setZ( (u->getZ() + v->getZ() + w->getZ()) / 3.0);

		return g;
	}

	template <typename T>
	T random(T min, T max)
	{ 
		return (T) (min + ((float) rand() / RAND_MAX * (max - min + (T) 1.0)));
	}

	int getHauteurFenetre();
	int getLargeurFenetre();


	std::string readFile(std::string fileName); //TODO : ne pas faire une copie du string dans le retour

};

#endif