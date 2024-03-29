
#ifndef INTERFACE_VITESSE_H
#define INTERFACE_VITESSE_H

#include "Interface.h"
#include "Outil.h"
#include "Animation.h"

class InterfaceVitesse : public Interface
{
public:
	InterfaceVitesse(GLfloat x, GLfloat y, GLfloat largeur, GLfloat hauteur,std::string nameFront = "", Animation* anim = NULL);
	virtual ~InterfaceVitesse();

	virtual void affiche();
	void setPourcentage(float p);
private:
	void drawInter();
	void appliqueTexture();

private:
	float _pourcentage;
	Animation* _animation;

};

#endif
