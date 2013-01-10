#include "CameraPolarView.h"
#include "Interactions.h"




class CameraPolarViewEvent : public CB_Interraction
{
public:
	CameraPolarViewEvent(CameraPolarView* camera) : _camera(camera)
	{
		_mouseState = -1;
	}
	virtual ~CameraPolarViewEvent(){}
public:
	virtual void eventsSpecialKey(int key, int x, int y)
	{
	
		float mult = 0.1;
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
		{
			mult *= -1;
		}

		double step_trans=0.1, step_rot=5, step_rot_obs=5;

		switch(key)
		{
		case GLUT_KEY_F10:	_camera->rotationZ_obs(90*mult); break;
		case GLUT_KEY_LEFT:
			if (mult==-1)
				_camera->translation_obs(1, step_trans);
			else
				_camera->tourner_tete(1, -step_rot_obs);
			break;
		case GLUT_KEY_RIGHT:
			if (mult==-1)
				_camera->translation_obs(1, -step_trans);
			else
				_camera->tourner_tete(1, step_rot_obs);
			break;
		case GLUT_KEY_UP:
			if (mult==-1)
				_camera->translation_obs(2, step_trans);
			else
				_camera->tourner_tete(2, -step_rot_obs);
			break;
		case GLUT_KEY_DOWN:
			if (mult==-1)
				_camera->translation_obs(2, -step_trans);
			else
				_camera->tourner_tete(2, step_rot_obs);
			break;
		}
		_camera->maj();
	}
	virtual void eventsKey(unsigned char key, int x, int y)
	{
		switch(key)
		{
		case 111 :	_camera->resetVue();_camera->maj();	break;
		}
	}
	virtual void eventsMouse(int boutton, int etat, int x, int y)
	{

		if(boutton == GLUT_LEFT_BUTTON)
		{
			if(etat == GLUT_DOWN)
			{
				_posCurseurX = x;
				_posCurseurY = y;
			}
		}
		else if(boutton ==GLUT_RIGHT_BUTTON)
		{
			if(etat == GLUT_DOWN)
			{
				_posCurseurX = x;
				_posCurseurY = y;
			}
		}
		else if(boutton ==GLUT_MIDDLE_BUTTON)
		{
			if(etat == GLUT_DOWN)
			{
				_posCurseurX = x;
				_posCurseurY = y;
			}
		}
		_mouseState = boutton;
	}
	virtual void eventsMotionMouse(int x, int y)
	{

		switch(_mouseState)
		{
		case GLUT_RIGHT_BUTTON:
			_camera->translation_obs(2, ((float)_posCurseurY-y)/50);
			_camera->translation_obs(1,((float)_posCurseurX-x)/50);
			break;
		case GLUT_LEFT_BUTTON : 
			_camera->tourner_tete(1, ((float)_posCurseurX-x)/10);	
			_camera->tourner_tete(2, ((float)_posCurseurY-y)/10);	
			break;
		case GLUT_MIDDLE_BUTTON : _camera->rotationZ_obs(((float)_posCurseurX-x)/10); 
			// Interactions::get()->_ob->translate(0,0, ((float)Interactions::get()->_posCurseurY-y)/50);
			_camera->zoom(((float)_posCurseurY-y)/50);
			break;
		default: ;

		}

		_posCurseurX = x;
		_posCurseurY = y;
		_camera->maj();
	}
	virtual void idle(){}
	virtual void reshape(int largeur, int hauteur)
	{
		if(hauteur < 1)
		{
			hauteur = 1;
		}

		glViewport(0, 0, largeur, hauteur);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90,((float) largeur)/hauteur,0.1,100) ;
		glMatrixMode(GL_MODELVIEW);
		_camera->maj();

	}
	virtual void dessine_scene(){}

private:
	CameraPolarView* _camera;

private:
	int _posCurseurX;
	int _posCurseurY;
	int _mouseState;

};




CameraPolarView::CameraPolarView()
{
	_interraction = new CameraPolarViewEvent(this);
	Interactions::get()->addEventCallBack(_interraction);
	resetVue();
}


CameraPolarView::~CameraPolarView()
{
	Interactions::get()->RemoveEventCallBack(_interraction);
}



void CameraPolarView::resetVue()
{

	_polarParam.azimut = 45;
	_polarParam.elevation = 45;
	_polarParam.distance = 6;
	_polarParam.twist = 0;

}


/****************************************************************************/
void CameraPolarView::affiche()						//applique l'observateur en cours //après modification de la variable typ_obs
{
	Camera::affiche();
	//glMatrixMode(GL_MODELVIEW);	
	//glLoadIdentity();
	polar_view(_polarParam.azimut, _polarParam.elevation, _polarParam.distance, _polarParam.twist);


	//glutPostRedisplay(); //rafraichit la zone de dessin (appelle dessine_scene)
}

/****************************************************************************/
void CameraPolarView::polar_view(double azimut, double elevation, double distance, double twist)
{	
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glTranslatef(0, 0, -distance);
	glRotatef(twist, 0, 0, 1);
	glRotatef(180, 0, 1, 0);
	glRotatef(-90-elevation, 1, 0, 0);
	glRotatef(90-azimut, 0, 0, 1);	
}


/****************************************************************************/
void CameraPolarView::rotationZ_obs(double angle)   //rotation de l'observateur autour de l'axe Z de la scene
{	
	_polarParam.azimut+=angle; 
}
/****************************************************************************/
void CameraPolarView::tourner_tete(int dir, double angle)
{
	double Orig[3]={0, 0, 0};


	switch (dir)
		{
		case 1: //droite gauche			=>varier l'azimut	
			_polarParam.azimut+=angle;
			if (_polarParam.azimut>=360)
				_polarParam.azimut-=360;
			else 
				if(_polarParam.azimut<0)
					_polarParam.azimut+=360;
			
			break;		
		case 2: //haut	bas				=>varier l'élevation
			_polarParam.elevation+=angle;
			if (_polarParam.elevation>=360)
				_polarParam.elevation-=360;
			else 
				if(_polarParam.elevation<0)
					_polarParam.elevation+=360;
			break;
		}

}
/****************************************************************************/
void CameraPolarView::zoom(double pas) //permet d'avancer ou de reculer dans la scene
{
	pas *= 20;
	_polarParam.distance+=pas;

}
/****************************************************************************/
void CameraPolarView::translation_obs(int dir, double pas) //déplace l'observateur vers la droite, la gauche, le bas ou le haut
{
	double dx, dy, dz, piover180=PI/180, d; //vect2[3];
	switch (dir)
		{
		case 1: //droite gauche		=>pas de translation ici, on ne peut que tourner! 	
			_polarParam.azimut-=pas*3;
			break;		
		case 2: //haut	bas		=>translation le long de l'axe Z
			d=(_polarParam.distance*cos(_polarParam.elevation*piover180));//projection dans le plan OxOy
			dz=_polarParam.distance*sin(_polarParam.elevation*piover180);  //coordonnées cartésiennes
			dy=d*sin(_polarParam.azimut*piover180);
			dx=d*cos(_polarParam.azimut*piover180);
			dz+=pas;					//tranlation le long de Z
			_polarParam.distance=sqrt(dx*dx+ dy*dy+ dz*dz); //calcul de la nouvelle distance

			if(_polarParam.elevation>90 && _polarParam.elevation<270)  //calcul de la nouvelle elevation/ attention, 2 valeurs possible pour la fonction asin
				_polarParam.elevation=(PI-asin(dz/_polarParam.distance))/piover180;
			else
				_polarParam.elevation=asin(dz/_polarParam.distance)/piover180;
			if (_polarParam.elevation<0)
				_polarParam.elevation+=360;		

			/*autre methode
			dz=_polarParam.distance*sin(_polarParam.elevation*piover180);
			dz=dz+pas; //posZ=distance*sin(elevation)
			dx=_polarParam.distance*cos(_polarParam.elevation*piover180);
			_polarParam.distance=sqrt(dz*dz+ dx*dx);			
			d=asin( dz/_polarParam.distance); 			
			if(cos(d)*cos(_polarParam.elevation*piover180) <0)  
				_polarParam.elevation=(pi-d)/piover180;
			else
				_polarParam.elevation=d/piover180;*/
			break;			
		}

}

/****************************************************************************/
void CameraPolarView::rotation3D(double angle, double* axeVect, double* axePt, double* monPt, double* result)
	//effectue la rotation d'angle angle, d'un point de l'espace (monPt) autour d'un axe defini par son vecteur directeur axeVect, 
	//et un point appartenant (axePt)
{
	double longueur, ux, uy, uz, m11, m12, m13, m21, m22, m23, m31, m32, m33, c, s;
	//normalisation axe de rotation
	longueur = sqrt(axeVect[0]*axeVect[0]+ axeVect[1]*axeVect[1]+ axeVect[2]*axeVect[2]);
	ux=axeVect[0]/longueur;
	uy=axeVect[1]/longueur;
	uz=axeVect[2]/longueur;
	//matrice de rotation	
	c=cos(angle*PI/180);
	s=sin(angle*PI/180);
	if (abs(angle)==90)
		c=0;
	if (abs(angle)==180)
		s=0;
	m11=ux*ux+(1-ux*ux)*c;		m12=ux*uy*(1-c)-uz*s;		m13=ux*uz*(1-c)+uy*s;
	m21=ux*uy*(1-c)+uz*s;		m22=uy*uy+(1-uy*uy)*c;		m23=uy*uz*(1-c)-ux*s;
	m31=ux*uz*(1-c)-uy*s;		m32=uy*uz*(1-c)+ux*s;		m33=uz*uz+(1-uz*uz)*c;
	//on ramène le point à tourner à l'origine avant la rotation
	ux=monPt[0]-axePt[0];
	uy=monPt[1]-axePt[1];
	uz=monPt[2]-axePt[2];
	//rotation + translation
	result[0]=m11*ux + m12*uy + m13*uz +axePt[0];
	result[1]=m21*ux + m22*uy + m23*uz +axePt[1];
	result[2]=m31*ux + m32*uy + m33*uz +axePt[2];
}
/****************************************************************************/
void CameraPolarView::pause()
{
	Interactions::get()->RemoveEventCallBack(_interraction);
}

void CameraPolarView::unpause()
{
	Interactions::get()->addEventCallBack(_interraction);
}