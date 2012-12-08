#ifndef _VBOMANAGER_H	
#define _VBOMANAGER_H

#include "Singleton.h"
#include "GL/glew.h"
#include <vector>
#include "VBO.h"
#include "Vector2d.h"
#include "Vector3d.h"


class VBOMangaer :	public Singleton<VBOMangaer>
{

public:
	void init();

public:
	VBO* makeVBO();
	std::vector<GLuint>* makeVBO(int quantitee);

	void deleteVBO(GLuint id, unsigned int size = 1);
	void alloueEtCharge(GLuint id, GLdouble* points, unsigned int sizePoint, GLdouble* textures, unsigned int sizeTexture, unsigned int first = 0)
	{
		alloue(id, sizePoint + sizeTexture);
		charge(id, points, sizePoint, textures, sizeTexture, first);
	}
	void alloue(GLuint id, unsigned int size); //size = la taille en octet (utilisez sizeof)
	void charge(GLuint id, GLdouble* points, unsigned int sizePoint, GLdouble* textures, unsigned int sizeTexture, unsigned int first = 0);
};

#endif