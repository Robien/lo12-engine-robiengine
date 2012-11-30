#ifndef PNGLOADER_H
#define PNGLOADER_H

#include "Scene.h"
#include "Texture.h"


int ReadPNGFromFile (Scene::MTEX *texinfo);
class Pngloader
{
	Pngloader();
	virtual ~Pngloader();
public:
	 static int ReadPNGFromFile (Texture* texinfo);
private:
	 static void GetPNGtextureInfo (int color_type, Texture* texinfo);

};

#endif

