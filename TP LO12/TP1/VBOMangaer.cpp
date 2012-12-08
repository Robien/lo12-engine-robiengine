#include "VBOMangaer.h"
#include <iostream>

void VBOMangaer::init()
{

	if (GLenum err =  glewInit() != GLEW_OK)
	{
		std::cout << "Il y a un probleme, glew mal initialise !" << std::endl  << glewGetErrorString(err);
		getchar();
		exit(0);
	}

}


GLuint VBOMangaer::makeVBO()
{
	GLuint buf = 0;
	glGenBuffers(1, &buf);
	return buf;
}

std::vector<GLuint>* VBOMangaer::makeVBO(int quantitee)
{
	std::vector<GLuint>* vect = new std::vector<GLuint>();

	GLuint* buf = (GLuint*) (malloc(quantitee*sizeof(GLuint)));
	glGenBuffers(1, buf);

	vect->assign(buf, buf + quantitee);
	return vect;
}

void VBOMangaer::deleteVBO(GLuint id)
{
	glDeleteBuffers(1, &id);
}