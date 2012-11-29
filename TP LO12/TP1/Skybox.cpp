#include "const.h"
#include "Texture.h"
#include "Skybox.h"

//*****************************************************************************************************************************
Skybox::Skybox()
{


}

Skybox::~Skybox()
{
}



void Skybox::charger()
{
	
	_tabText.push_back(Texture::get()->addTexture("textures/XN.png"));
    _tabText.push_back(Texture::get()->addTexture("textures/XP.png"));
    _tabText.push_back(Texture::get()->addTexture("textures/YN.png"));
    _tabText.push_back(Texture::get()->addTexture("textures/YP.png"));
    _tabText.push_back(Texture::get()->addTexture("textures/ZN.png"));
    _tabText.push_back(Texture::get()->addTexture("textures/ZP.png"));
}


//*****************************************************************************************************************************
void Skybox::dessine_box(Scene::MCOORD coord)
{
	float t=1.0;
	// Désactivation de l'écriture dans le Z-buffer
	 glDisable(GL_DEPTH_TEST);
	 glDepthMask(GL_FALSE);
	//Désactivation du calcul d'éclairage
	glDisable(GL_LIGHTING);
	
	glEnable(GL_TEXTURE_2D);
	
	// Réglage de la position de la box
	
	/* //test
	glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
	*/
	//glPushMatrix();
	//glLoadIdentity();
	 // test
   
	glPushMatrix();
	glLoadIdentity();
    gluLookAt(
        0,0,0,
        coord.x, coord.y, coord.z,
        0,1,0);
	

	//glTranslated(coord.x, coord.y, coord.z);

	glColor4f(1,1,1,1);
	// dessin de la box
    glBindTexture(GL_TEXTURE_2D, _tabText[0]);
	glBegin(GL_QUADS);			// X Négatif		
		glTexCoord2f(0.0, 0.0); glVertex3f(-t,-t,-t); 	
		glTexCoord2f(1.0, 0.0); glVertex3f(-t,t,-t);
		glTexCoord2f(1.0, 1.0); glVertex3f(-t,t,t);
		glTexCoord2f(0.0, 1.0); glVertex3f(-t,-t,t); 
	glEnd();

 glBindTexture(GL_TEXTURE_2D, _tabText[1]);
	glBegin(GL_QUADS);			// X Positif
		glTexCoord2f(0.0, 0.0); glVertex3f(t,t,-t); 	
		glTexCoord2f(1.0, 0.0); glVertex3f(t,-t,-t);
		glTexCoord2f(1.0, 1.0); glVertex3f(t,-t,t);
		glTexCoord2f(0.0, 1.0); glVertex3f(t,t,t); 	
	glEnd();

 glBindTexture(GL_TEXTURE_2D, _tabText[2]);
	glBegin(GL_QUADS);			// Y Négatif	
		glTexCoord2f(0.0, 0.0); glVertex3f(t,-t,-t);
		glTexCoord2f(1.0, 0.0); glVertex3f(-t,-t,-t);
		glTexCoord2f(1.0, 1.0); glVertex3f(-t,-t,t);
		glTexCoord2f(0.0, 1.0); glVertex3f(t,-t,t); 
	glEnd();

 glBindTexture(GL_TEXTURE_2D, _tabText[3]);
	glBegin(GL_QUADS);			// Y Positif		
		glTexCoord2f(0.0, 0.0); glVertex3f(-t,t,-t);
		glTexCoord2f(1.0, 0.0); glVertex3f(t,t,-t);
		glTexCoord2f(1.0, 1.0); glVertex3f(t,t,t);
		glTexCoord2f(0.0, 1.0); glVertex3f(-t,t,t); 	
	glEnd();

 glBindTexture(GL_TEXTURE_2D, _tabText[4]);
	glBegin(GL_QUADS);			// Z Négatif		
		glTexCoord2f(0.0, 0.0); glVertex3f(-t,t,-t);
		glTexCoord2f(1.0, 0.0); glVertex3f(t,t,-t);
		glTexCoord2f(1.0, 1.0); glVertex3f(t,-t,-t);
		glTexCoord2f(0.0, 1.0); glVertex3f(-t,-t,-t); 
	glEnd();

 glBindTexture(GL_TEXTURE_2D, _tabText[5]);
	glBegin(GL_QUADS);			// Z Positif	
		glTexCoord2f(0.0, 1.0); glVertex3f(-t,t,t);
		glTexCoord2f(0.0, 0.0); glVertex3f(t,t,t);
		glTexCoord2f(1.0, 0.0); glVertex3f(t,-t,t);
		glTexCoord2f(1.0, 1.0); glVertex3f(-t,-t,t);    
	glEnd();	
	
	glPopMatrix();

	// Réactivation des etats d'opengl
	 glDepthMask(GL_TRUE);
	 glEnable(GL_DEPTH_TEST);
	 glEnable(GL_LIGHTING);
	  //test
    /*glPopAttrib();
    glPopMatrix();*/
}

