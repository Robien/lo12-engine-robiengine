#include "InterfaceVitesse.h"
#include "GestionnaireTexture.h"
#include "AnimationSurchauffe.h"

InterfaceVitesse::InterfaceVitesse(GLfloat x, GLfloat y, GLfloat largeur, GLfloat hauteur, std::string nameFront, Animation* anim) : Interface(x, y, largeur, hauteur,nameFront), _animation(anim)
{

	_pourcentage = 0;
}


InterfaceVitesse::~InterfaceVitesse()
{
}

void InterfaceVitesse::setPourcentage(float p)
{
	if(p<0)
	{p=0;}
	if(p>1)
	{p=1;}
	if(getActif() && _animation != NULL)
	{
		if(p>0.8)
		{
			((AnimationSurchauffe*)_animation)->setActif(true);
		}
		else
		{
			((AnimationSurchauffe*)_animation)->setActif(false);
		}
	}
	_pourcentage = p;
}

void InterfaceVitesse::affiche()
{
	beginInter();
	drawInter();
	Interface::drawInter();
	endInter();
}

void InterfaceVitesse::drawInter()
{
	appliqueTexture();
	glBegin(GL_POLYGON);	
	glColor3f(_pourcentage,(1-_pourcentage),0);
	 glVertex2f( _x, _y); 	
	 glVertex2f( _x+_largeur, _y);
	 glVertex2f( _x+_largeur, _y+_hauteur);
	glEnd();

}

void InterfaceVitesse::appliqueTexture()
{
		glBindTexture(GL_TEXTURE_2D, 0);
}

