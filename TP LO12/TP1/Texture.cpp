#include "Texture.h"
#include "stdlib.h"
#include <iostream>




std::string Texture::getFilename()
{	
	return _filename;
}
GLint Texture::getWidth()
{
	return _width;
}
GLint Texture::getHeight()
{
	return _height;
}
GLenum Texture::getFormat()
{
	return _format;
}
GLint Texture::getInternalFormat()
{
	return _internalFormat;
}
GLubyte* Texture::getTexels()
{
	return _texels;
}
GLuint Texture::getGlnum()
{
	return _glnum;
}

void Texture::setFilename(std::string f)
{
	_filename = f;
}
void Texture::setWidth(GLint w)
{
	_width = w;
}
void Texture::setHeight(GLint h)
{
	_height = h;
}
void Texture::setFormat(GLenum f)
{
	_format = f;
}
void Texture::setInternalFormat(GLint i)
{
	_internalFormat = i;
}
void Texture::setTexels(GLubyte* t)
{
	_texels = t;
}
void Texture::setGlnum(GLuint num)
{
	_glnum = num;
}