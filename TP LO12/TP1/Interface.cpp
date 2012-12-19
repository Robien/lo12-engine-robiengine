#include "Interface.h"
#include "GestionnaireTexture.h"
#include "Interactions.h"


class InterractionInterface : public CB_Interraction
{
public:
	InterractionInterface(Interface* gui) : _interface(gui)
	{}
	virtual ~InterractionInterface(){}
public:
	virtual void reshape(int largeur, int hauteur)
	{
		_interface->recalculeSize();
	}
private:
	Interface* _interface;


};



Interface::Interface(GLfloat x, GLfloat y, GLfloat largeur, GLfloat hauteur, std::string name)
{
	if(name != "")
	{
		_indiceTex = GestionnaireTexture::get()->addTexture(name);
	}
	setPosition(x, y, largeur, hauteur);
	Interactions::get()->addEventCallBack(new InterractionInterface(this));

}


Interface::~Interface()
{
}
void Interface::recalculeSize()
{
	setPosition(_position.getX(), _position.getY(), _proportions.getX(), _proportions.getY());
}

void Interface::setPosition(GLfloat x, GLfloat y, GLfloat largeur, GLfloat hauteur)
{

	_position.setX(x);
	_position.setY(y);
	_proportions.setX(largeur);
	_proportions.setY(hauteur);



	if(x < 0)
	{x=0;}
	if(y < 0)
	{y=0;}
	if(largeur < 0)
	{largeur=0;}
	if(hauteur < 0)
	{hauteur=0;}

	if(x <= 1)
	{
		_x = x * Outil::get()->getLargeurFenetre();
	}
	else
	{
		_x = x;
	}

	if(y <= 1)
	{
		_y = y * Outil::get()->getHauteurFenetre();
	}
	else
	{
		_y = y;
	}

	if(largeur <= 1)
	{
		_largeur = largeur * Outil::get()->getLargeurFenetre();
	}
	else
	{
		_largeur=largeur;
	}

	if(hauteur <= 1)
	{
		_hauteur = hauteur * Outil::get()->getHauteurFenetre();
	}
	else
	{
		_hauteur = hauteur;
	}
}

void Interface::affiche()
{

	beginInter();
	drawInter();
	endInter();
}

void Interface::appliqueTexture()
{
	if ( _indiceTex > 0)
	{
		glBindTexture(GL_TEXTURE_2D, _indiceTex);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void Interface::beginInter()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, Outil::get()->getLargeurFenetre(), 0, Outil::get()->getHauteurFenetre());
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	//glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); 

	glColor4f(1,1,1,0.5);

}
void Interface::endInter()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();  
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
}

void Interface::drawInter()
{
	appliqueTexture();
	glBegin(GL_QUADS);				
	glTexCoord2f(0, 0); glVertex2f( _x, _y); 	
	glTexCoord2f(1.0, 0); glVertex2f( _x+_largeur, _y);
	glTexCoord2f(1.0, 1.0); glVertex2f( _x+_largeur, _y+_hauteur);
	glTexCoord2f(0, 1.0); glVertex2f( _x, _y+_hauteur);
	glEnd();
}