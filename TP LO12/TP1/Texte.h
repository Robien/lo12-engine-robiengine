#ifndef _TEXTE_H	
#define _TEXTE_H

#include "Outil.h"
#include <string>

class Texte
{
public:
	Texte(std::string str, GLfloat x = 0, GLfloat y = 0);
	virtual ~Texte();
	void affiche();
	
	void setTexte(std::string str);
	void setPolice(void* font);
	void setPosition(GLfloat x, GLfloat y);
	void setCouleur(GLfloat r, GLfloat g, GLfloat b);
private:
	void beginTexte();
	void endText();
	void drawText(float x, float y, std::string str);

private:
	void* _police;
	std::string _texte;
	GLfloat _x;
	GLfloat _y;
	Vector3d<GLfloat> _couleur;
};

#endif