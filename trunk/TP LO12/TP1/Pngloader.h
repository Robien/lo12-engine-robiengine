#ifndef PNGLOADER_H
#define PNGLOADER_H

#include "Scene.h"
#include "Texture.h"


int ReadPNGFromFile (Scene::MTEX *texinfo);
class Pngloader
{
public:
	int ReadPNGFromFile (Texture* texinfo);
private:
	void GetPNGtextureInfo (int color_type, Texture* texinfo);

};

#endif

