#include "Outil.h"
#include "stdlib.h"
#include "Pngloader.h"
#include <iostream>


void Outil::initManager(Scene* scene)
{
	_scene = scene;
}


GLuint Outil::addTexture(char* filename)
{
	Scene::MTEX * texture = (Scene::MTEX*) malloc (sizeof(Scene::MTEX));
	texture->filename = filename;

	bool exist = false;
		unsigned int i;
	for (i = 0; !exist && i < _scene->tabtex.size(); ++i)
	{
		
		if (strcmp(_scene->tabtex.at(i).filename, filename) == 0)
		{
			exist = true;
		}
	}



	if (exist)
	{
		return _scene->tabtex.at(i).glnum;
	}

	if(ReadPNGFromFile(texture))
	{
		std::cout << "Fichiers introuvables ! : " << filename << std::endl;
	}
	_scene->tabtex.push_back(*texture);
	GLuint tmp;
	glGenTextures(1, &tmp);
	_scene->_tabTexture.push_back(tmp);
	texture->glnum = tmp;

	glBindTexture(GL_TEXTURE_2D,texture->glnum);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0,texture->internalFormat, texture->width,texture->height,0, texture->format, GL_UNSIGNED_BYTE,texture->texels);

	

	return tmp;
}

