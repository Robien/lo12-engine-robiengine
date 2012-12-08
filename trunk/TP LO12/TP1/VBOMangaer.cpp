#include "VBOMangaer.h"
#include <iostream>
#include "VBO.h"

void VBOMangaer::init()
{

	if (GLenum err =  glewInit() != GLEW_OK)
	{
		std::cout << "Il y a un probleme, glew mal initialise !" << std::endl  << glewGetErrorString(err);
		getchar();
		exit(0);
	}

}


VBO* VBOMangaer::makeVBO()
{
	GLuint buf = 0;
	glGenBuffers(1, &buf);
	VBO* vbo = new VBO(buf);
	return vbo;
}

std::vector<GLuint>* VBOMangaer::makeVBO(int quantitee)
{
	std::vector<GLuint>* vect = new std::vector<GLuint>();

	GLuint* buf = (GLuint*) (malloc(quantitee*sizeof(GLuint)));
	glGenBuffers(1, buf);

	vect->assign(buf, buf + quantitee);
	return vect;
}

void VBOMangaer::deleteVBO(GLuint id, unsigned int size)
{
	glDeleteBuffers(1, &id);
}

void VBOMangaer::alloue(GLuint id, unsigned int size)
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW);

}

void VBOMangaer::charge(GLuint id, GLdouble* points, unsigned int sizePoint, GLdouble* textures, unsigned int sizeTexture, unsigned int first)
{
	//std::cout << "LES CHATS C'EST DES CONNARDS" << std::endl;
		glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferSubData(GL_ARRAY_BUFFER,first,sizePoint,points); 
	glBufferSubData(GL_ARRAY_BUFFER,first + sizePoint,sizeTexture, textures); 

	glBindBuffer(GL_ARRAY_BUFFER, id);


}