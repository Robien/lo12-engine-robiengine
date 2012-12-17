#include "InterfaceVitesse.h"
#include "GestionnaireTexture.h"

InterfaceVitesse::InterfaceVitesse(GLfloat x, GLfloat y, GLfloat largeur, GLfloat hauteur, std::string nameFront, std::string nameBack) : Interface(x, y, largeur, hauteur,nameFront)
{
	if(nameFront != "")
	{
		_indiceTexFront = GestionnaireTexture::get()->addTexture(nameBack);
	}
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
	glTexCoord2f(0, 0); glVertex2f( _x, _y); 	
	glTexCoord2f(_pourcentage, 0); glVertex2f( _x+_largeur, _y);
	glTexCoord2f(_pourcentage, 1.0); glVertex2f( _x+_largeur, _y+_hauteur);
	glEnd();

}

void InterfaceVitesse::appliqueTexture()
{
	if ( _indiceTexFront > 0)
	{
		glBindTexture(GL_TEXTURE_2D, _indiceTexFront);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

