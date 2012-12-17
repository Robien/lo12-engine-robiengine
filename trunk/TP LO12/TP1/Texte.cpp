#include "Texte.h"
#include <stdarg.h> 
#include "Outil.h"

Texte::Texte(std::string str, GLdouble x, GLdouble y): _couleur(0,0,0)
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
		_x = x * Outil::get()->getLargeurFenetre();
	}
	else
	{
		_x=x;
	}
	if(y < 1)
	{
		_y = y * Outil::get()->getHauteurFenetre();
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
void Texte::setCouleur(GLfloat r, GLfloat g, GLfloat b)
{
	_couleur.setX(r);
	_couleur.setY(g);
	_couleur.setZ(b);
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
	gluOrtho2D(0, Outil::get()->getHauteurFenetre(), 0, Outil::get()->getLargeurFenetre());
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3fv(_couleur.getCStyle());

}
void Texte::endText()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
void Texte::drawText(float x, float y, std::string str)
{
	glRasterPos2f(x,y);

	for(unsigned int i=0; i < str.size();++i)
	{
		glutBitmapCharacter(_police, str.c_str()[i]);
	}
}