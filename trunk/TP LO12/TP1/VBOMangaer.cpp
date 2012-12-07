#include "VBOMangaer.h"


GLuint VBOMangaer::makeVBO()
{
	GLuint buf;
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