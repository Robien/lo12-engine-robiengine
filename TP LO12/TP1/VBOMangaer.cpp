#include "VBOMangaer.h"

void VBOMangaer::init()
{
	 glewInit();
}


GLuint VBOMangaer::makeVBO()
{
	GLuint buf = 0;
//	glGenBuffers(1, &buf);
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