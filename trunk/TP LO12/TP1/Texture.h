#ifndef _TEXTURE_H	
#define _TEXTURE_H

#include <iostream>
#include "const.h"

class Texture
{
public:
	Texture();
	virtual ~Texture();

	std::string getFilename();
	GLint getWidth();
	GLint getHeight();
	GLint* getPtWidth();
	GLint* getPtHeight();
	GLenum getFormat();
	GLint getInternalFormat();
	GLubyte* getTexels();
	GLuint getGlnum();

	void setFilename(std::string f);
	void setWidth(GLint w);
	void setHeight(GLint h);
	void setFormat(GLenum f);
	void setInternalFormat(GLint i);
	void setTexels(GLubyte* t);
	void setGlnum(GLuint num);

private:
	std::string _filename;
	GLint _width;
	GLint _height;
	GLenum _format;
	GLint _internalFormat;
	GLubyte* _texels;
	GLuint _glnum;

};

#endif