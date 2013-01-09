#ifndef _INTERFACE_H	
#define _INTERFACE_H

#include "Vector2d.h"
#include "Vector3d.h"
#include "Outil.h"
#include "Material.h"
#include <vector>

class Interface
{
public:
	Interface(GLfloat x, GLfloat y, GLfloat largeur, GLfloat hauteur,std::string name = "");
	virtual ~Interface();

	virtual void affiche();
	virtual void setPosition(GLfloat _x, GLfloat _y, GLfloat _largeur, GLfloat _hauteur);
	void setCouleur(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	virtual void recalculeSize();
	void setActif(bool act);
	bool getActif();
protected:
	void beginInter();
	void endInter();
	void drawInter();
	void appliqueTexture();
protected:
	bool _actif;
	GLfloat _x, _y, _largeur, _hauteur;
	GLuint _indiceTex;						/* indice de la texture */
	Vector2d<GLdouble> _position;
	Vector2d<GLdouble> _proportions;
	Vector3d<GLfloat> _couleur;
	GLfloat _transparence;
};

#endif