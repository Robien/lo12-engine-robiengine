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
	Interface(GLuint indTex = 0);
	virtual ~Interface();

	void afficher();
	void addPoint(Vector3d<GLdouble>* coordonnees, Vector2d<GLdouble>* coordonnneesTexture = NULL);
private:
	void beginTexte();
	void endText();
	void drawText();
	void appliqueTexture();
private:
	std::vector<Vector3d<GLdouble>* > _listePoints;
	std::vector<Vector2d<GLdouble>* > _listeCoordonneesTextures;
	GLuint _indiceTex;						/* indice de la texture */
};

#endif