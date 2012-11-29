#ifndef _TEXTURE_H	
#define _TEXTURE_H

#include "Scene.h"
#include "Pngloader.h"
#include "Singleton.h"

class Texture : public Singleton<Texture>
{
public:
	void initManager(Scene* scene);
	void initTexture();
	
	GLuint* addTexture(char* filename);

private:
	Scene* _scene;

};

#endif