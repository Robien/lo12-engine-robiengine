#include "Texture.h"
#include "stdlib.h"
#include "Pngloader.h"
#include <iostream>


void Texture::initManager(Scene* scene)
{
	_scene = scene;
}


GLuint* Texture::addTexture(char* filename)
{
	Scene::MTEX * texture = (Scene::MTEX*) malloc (sizeof(Scene::MTEX));
	texture->filename = filename;
	if(ReadPNGFromFile(texture))
	{
		std::cout << "Fichiers introuvables ! : " << filename << std::endl;
	}
	_scene->tabtex.push_back(*texture);
	_scene->_tabTexture.push_back(texture->glnum);
	return &texture->glnum;
}

void Texture::initTexture()
{

	glGenTextures(_scene->tabtex.size(), _scene->_tabTexture.data());

	for (unsigned int i = 0; i < _scene->tabtex.size(); ++i)
	{
		_scene->tabtex[i].glnum = _scene->_tabTexture[i];
	}

	for (unsigned int i = 0; i < _scene->tabtex.size(); ++i)
	{
		glBindTexture(GL_TEXTURE_2D,_scene->tabtex[i].glnum);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, _scene->tabtex[i].internalFormat,_scene->tabtex[i].width,_scene->tabtex[i].height,0, _scene->tabtex[i].format, GL_UNSIGNED_BYTE, _scene->tabtex[i].texels);
	}
}

