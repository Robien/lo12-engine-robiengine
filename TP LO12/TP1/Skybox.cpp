#include "const.h"
#include "Outil.h"
#include "Skybox.h"
#include "Matrice.h"
#include "GestionnaireTexture.h"

//*****************************************************************************************************************************
Skybox::Skybox()
{


}

Skybox::~Skybox()
{
}



void Skybox::charger()
{
	
	_tabText.push_back(GestionnaireTexture::get()->addTexture("textures/Space1/space1_back6.png"));
    _tabText.push_back(GestionnaireTexture::get()->addTexture("textures/Space1/space1_front5.png"));
    _tabText.push_back(GestionnaireTexture::get()->addTexture("textures/Space1/space1_right1.png"));
    _tabText.push_back(GestionnaireTexture::get()->addTexture("textures/Space1/space1_left2.png"));
    _tabText.push_back(GestionnaireTexture::get()->addTexture("textures/Space1/space1_bottom4.png"));
    _tabText.push_back(GestionnaireTexture::get()->addTexture("textures/Space1/space1_top3.png"));
}


//*****************************************************************************************************************************
void Skybox::dessine_box()
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
	//glLoadIdentity();
    //gluLookAt(
     //   0,0,0,
     //   coord.x, coord.y, coord.z,
      //  0,1,0);
	
	GLdouble* newData = (GLdouble*) malloc(16*sizeof(GLdouble));
	glGetDoublev(GL_MODELVIEW_MATRIX, newData);
	newData[12] = 0;
	newData[13] = 0;
	newData[14] = 0;
	newData[15] = 1;
	glLoadMatrixd(newData);
	delete newData;

	//glTranslated(coord.x, coord.y, coord.z);

		//	
		



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
		/* backup 
		glTexCoord2f(0.0, 0.0); glVertex3f(-t,t,-t);
		glTexCoord2f(1.0, 0.0); glVertex3f(t,t,-t);
		glTexCoord2f(1.0, 1.0); glVertex3f(t,-t,-t);
		glTexCoord2f(0.0, 1.0); glVertex3f(-t,-t,-t); */

		glTexCoord2f(0.0, 0.0); glVertex3f(-t,t,-t);
		 glTexCoord2f(0.0, 1.0);glVertex3f(t,t,-t);
		glTexCoord2f(1.0, 1.0); glVertex3f(t,-t,-t);
		glTexCoord2f(1.0, 0.0); glVertex3f(-t,-t,-t); 

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

