#include "Texte.h"
#include <stdarg.h>  

Texte::Texte(std::string str, GLdouble x, GLdouble y)
{
	_texte = str;
	_police = GLUT_BITMAP_TIMES_ROMAN_24;
	
	setPosition(x,y);
	
}


Texte::~Texte()
{

}

void Texte::setPosition(GLdouble x, GLdouble y)
{
	if(x < 0)
	{x=0;}
	if(y < 0)
	{y=0;}
	if(x < 1)
	{
		_x = x * LARGEUR_FENETRE;
	}
	else
	{
		_x=x;
	}
	if(y < 1)
	{
		_y = y * HAUTEUR_FENETRE;
	}
	else
	{
		_y = y;
	}
}

void Texte::setTexte(std::string str)
{
	_texte = str;
}

void Texte::setPolice(void* font)
{
	_police = font;
}

void Texte::affiche()
{
	beginTexte();
	drawText(_x,_y,_texte);
	endText();
}

void Texte::beginTexte()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0,768/1.2,0,1024/1.2);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1,1,0.5);

}
void Texte::endText()
{
	glMatrixMode(GL_PROJECTION);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}
void Texte::drawText(float x, float y, std::string str)
{
	glRasterPos2f(x,y);

	for(unsigned int i=0; i < str.size();++i)
	{
		glutBitmapCharacter(_police, str.c_str()[i]);
	}
}