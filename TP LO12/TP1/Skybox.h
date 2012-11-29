#ifndef _SKYBOX_H	
#define _SKYBOX_H

#include "Scene.h"
#include "Pngloader.h"
#include <vector>

class Skybox
{
public:
	Skybox();
	virtual ~Skybox();

	void charger();
	void dessine_box(Scene::MCOORD coord, std::vector<GLuint>* _tabTexture);

private:
	std::vector<GLuint*> _tabText;

};

#endif