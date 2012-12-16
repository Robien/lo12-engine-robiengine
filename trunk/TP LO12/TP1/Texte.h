#ifndef _TEXTE_H	
#define _TEXTE_H

#include "Outil.h"
#include <string>
class Texte
{
public:
	Texte(std::string str, GLdouble x = 0, GLdouble y = 0);
	virtual ~Texte();
	void affiche();
	
	void setTexte(std::string str);
	void setPolice(void* font);
	void setPosition(GLdouble x, GLdouble y);
private:
	void beginTexte();
	void endText();
	void drawText(float x, float y, std::string str);

private:
	void* _police;
	std::string _texte;
	GLdouble _x;
	GLdouble _y;
};

#endif