#ifndef _VBOMANAGER_H	
#define _VBOMANAGER_H

#include "Singleton.h"
#include "GL/glew.h"
#include <vector>


class VBOMangaer :	public Singleton<VBOMangaer>
{

public:
	void init();

public:
	GLuint makeVBO();
	std::vector<GLuint>* makeVBO(int quantitee);

	void deleteVBO(GLuint id);

};

#endif