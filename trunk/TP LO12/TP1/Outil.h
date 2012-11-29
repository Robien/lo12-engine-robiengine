#ifndef _OUTIL_H	
#define _OUTIL_H


#include "Scene.h"
#include "Pngloader.h"
#include "Singleton.h"

class Outil : public Singleton<Outil>
{
public:
	void initManager(Scene* scene);
	GLuint addTexture(char* filename);

	private:
	Scene* _scene;
};

#endif