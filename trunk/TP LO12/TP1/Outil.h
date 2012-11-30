#ifndef _OUTIL_H	
#define _OUTIL_H

#include "const.h"
#include "Pngloader.h"
#include "Singleton.h"
#include "Vector3d.h"


class Scene;

class Outil : public Singleton<Outil>
{
public:
	void initManager(Scene* scene);
	GLuint addTexture(char* filename); //TODO DELETE

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

	private:
	Scene* _scene;
};

#endif