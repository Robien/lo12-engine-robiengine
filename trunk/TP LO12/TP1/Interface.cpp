#include "Interface.h"


Interface::Interface(GLuint indTex)
{
	_indiceTex = indTex;
}


Interface::~Interface()
{
}

void Interface::afficher()
{

	beginTexte();
	drawText();
	endText();
}

void Interface::addPoint(Vector3d<GLdouble>* coordonnees, Vector2d<GLdouble>* coordonnneesTexture)
{
	_listePoints.push_back(coordonnees);
	_listeCoordonneesTextures.push_back(coordonnneesTexture);
}

void Interface::appliqueTexture()
{
	if (_listeCoordonneesTextures.size() != 0 && _listeCoordonneesTextures.at(0) != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, _indiceTex);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
}

void Interface::beginTexte()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, Outil::get()->getHauteurFenetre(), 0, Outil::get()->getLargeurFenetre());
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);


	appliqueTexture();


}
void Interface::endText()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();  
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
}
void Interface::drawText()
{
	glBegin(GL_TRIANGLES);           // Each set of 4 vertices form a quad
		glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2f( 100, 20);    

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f( 130, 50);
	glVertex2f( 130,  20);
	glEnd();
}