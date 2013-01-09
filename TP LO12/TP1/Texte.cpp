#include "Texte.h"
#include <stdarg.h> 
#include "Outil.h"
#include "Interactions.h"
#include "Shader.h"


class InterractionInterface : public CB_Interraction
{
public:
	InterractionInterface(Texte* texte) : _texte(texte)
	{}
	virtual ~InterractionInterface(){}
public:
	virtual void reshape(int largeur, int hauteur)
	{
		_texte->recalculeSize();
	}
private:
	Texte* _texte;


};





Texte::Texte(std::string str, GLfloat x, GLfloat y): _couleur(1,1,1)
{
	_texte = str;
	_police = GLUT_BITMAP_TIMES_ROMAN_24;
	_actif = true;
	setPosition(x,y);

}


Texte::~Texte()
{

}

void Texte::setPosition(GLfloat x, GLfloat y)
{
	_positon.setX(x);
	_positon.setY(y);


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
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, Outil::get()->getLargeurFenetre(), 0, Outil::get()->getHauteurFenetre());
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
	glEnable(GL_LIGHTING);
}
void Texte::drawText(float x, float y, std::string str)
{
	glRasterPos2f(x,y);
	for(unsigned int i=0; i < str.size();++i)
	{
		glutBitmapCharacter(_police, str.c_str()[i]);
	}
}

void Texte::recalculeSize()
{
	setPosition(_positon.getX(), _positon.getY());
}

void Texte::setActif(bool act)
{
	_actif = act;
}

bool Texte::getActif()
{
	return _actif;
}