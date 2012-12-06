#include "CameraVaisseau.h"
#include "Interactions.h"




class CameraVaisseauEvent : public CB_Interraction
{
public:
	CameraVaisseauEvent(CameraVaisseau* camera) : _camera(camera)
	{
		_mouseState = -1;
		_acceleration = 0;
	}
	virtual ~CameraVaisseauEvent(){}
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
		if (etat == GLUT_DOWN)
		{
			_mouseState = boutton;
		}
		else
		{
				_mouseState = -1;
		}
	}
	virtual void eventsMotionMouse(int x, int y)
	{
		_posCurseurX = x;
		_posCurseurY = y;
		_camera->maj();
	}
	virtual void eventsPassiveMotionMouse(int x, int y)
	{
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
	virtual void dessine_scene()
	{

		GLint m_viewport[4];

		glGetIntegerv( GL_VIEWPORT, m_viewport );


		if (((float)_posCurseurX-m_viewport[2]/2)/50 > 1)
		{
			_camera->tourner_tete(1, ((float)_posCurseurX-m_viewport[2]/2)/50 - 1);	
		}
				if (((float)_posCurseurX-m_viewport[2]/2)/50 < -1)
		{
			_camera->tourner_tete(1, ((float)_posCurseurX-m_viewport[2]/2)/50 + 1);	
		}
		if ( ((float)_posCurseurY-m_viewport[3]/2)/50 > 1 )
		{
			_camera->tourner_tete(2, ((float)_posCurseurY-m_viewport[3]/2)/50 - 1);
		}
		if (  ((float)_posCurseurY-m_viewport[3]/2)/50 < -1)
		{
			_camera->tourner_tete(2, ((float)_posCurseurY-m_viewport[3]/2)/50 + 1);
		}


		if (_mouseState == GLUT_LEFT_BUTTON)
		{

			_acceleration += 2;
			_acceleration *= 0.99;
		}
		else if (_mouseState == GLUT_RIGHT_BUTTON)
		{
			_acceleration *= 0.93-0.09;
		}
		else
		{
			_acceleration *= 0.97;
		}
		
		
		if (_acceleration < 0.01)
		{
			_acceleration = 0;
		}
		//std::cout << _acceleration << std::endl;
		_camera->zoom(-_acceleration/50);
	}

private:
	CameraVaisseau* _camera;

private:
	int _posCurseurX;
	int _posCurseurY;
	int _mouseState;
	float _acceleration;

};

void CameraVaisseau::resetVue()
{
	getMatrice()->reset();
	_lookAtParam.eyex = -4;
	_lookAtParam.eyey = -4;
	_lookAtParam.eyez = 0;
	_lookAtParam.centrex = 0;
	_lookAtParam.centrey = 0;
	_lookAtParam.centrez = 0;
	_lookAtParam.upx = 0;
	_lookAtParam.upy = 0;
	_lookAtParam.upz = 1;
}



CameraVaisseau::CameraVaisseau()
{
	Interactions::get()->addEventCallBack(new CameraVaisseauEvent(this));
	resetVue();
}


CameraVaisseau::~CameraVaisseau()
{
}



/****************************************************************************/
void CameraVaisseau::affiche()						//applique l'observateur en cours //après modification de la variable typ_obs
{
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	gluLookAt(_lookAtParam.eyex,_lookAtParam.eyey,_lookAtParam.eyez, _lookAtParam.centrex, _lookAtParam.centrey, _lookAtParam.centrez, _lookAtParam.upx, _lookAtParam.upy, _lookAtParam.upz);
	glutSetWindowTitle("View Mode: gluLookAt");

	//glutPostRedisplay(); //rafraichit la zone de dessin (appelle dessine_scene)
}


/****************************************************************************/
void CameraVaisseau::rotationZ_obs(double angle)   //rotation de l'observateur autour de l'axe Z de la scene
{	
	double x, y;
	angle=angle*PI/180.0;
	x=_lookAtParam.eyex;
	y=_lookAtParam.eyey;
	_lookAtParam.eyex=x*cos(angle)-y*sin(angle);
	_lookAtParam.eyey=x*sin(angle)+y*cos(angle);
}
/****************************************************************************/
void CameraVaisseau::tourner_tete(int dir, double angle)
{
	double vect[3], vect2[3], vect3[3], Orig[3]={0, 0, 0};


	switch (dir)
	{
	case 1: //droite gauche					=>rotation du point observé autour de l'axe Up (mémorisé dans lookAtParam)
		rotation3D(-angle, &_lookAtParam.upx, &_lookAtParam.eyex, &_lookAtParam.centrex, vect); //rotation +
		_lookAtParam.centrex=vect[0];														//mémorisation du point observé
		_lookAtParam.centrey=vect[1];
		_lookAtParam.centrez=vect[2];
		break;
	case 2://haut bas						=>rotation du Center Pt autour de l'axe Left (à déterminer)		
		rotation3D(90, &_lookAtParam.upx, &_lookAtParam.eyex, &_lookAtParam.centrex, vect2); //rotation du point observé, de 90 autour de l'axe Up  
		vect2[0]=vect2[0]-_lookAtParam.eyex;										//calcul de l'axe Left
		vect2[1]=vect2[1]-_lookAtParam.eyey;
		vect2[2]=vect2[2]-_lookAtParam.eyez;
		rotation3D(angle, vect2, &_lookAtParam.eyex, &_lookAtParam.centrex, vect);		//rotation du point observé autour de l'axe Left			
		rotation3D(angle, vect2, &Orig[0], &_lookAtParam.upx, vect3);				//rotation de l'axe Up autour de l'axe Left
		_lookAtParam.centrex=vect[0];													//mémorisation du point observé
		_lookAtParam.centrey=vect[1];
		_lookAtParam.centrez=vect[2];
		_lookAtParam.upx=vect3[0];												//mémorisation du Up
		_lookAtParam.upy=vect3[1];
		_lookAtParam.upz=vect3[2];
		break;		
	}

}
/****************************************************************************/
void CameraVaisseau::zoom(double pas) //permet d'avancer ou de reculer dans la scene
{
	double dx, dy, dz, dist, piover180=PI/180; //vect2[3];

	dx=_lookAtParam.eyex-_lookAtParam.centrex;				//détermination du vecteur directeur de l'axe
	dy=_lookAtParam.eyey-_lookAtParam.centrey;
	dz=_lookAtParam.eyez-_lookAtParam.centrez;
	dist=sqrt(pow(dx, 2)+pow(dy, 2)+pow(dz, 2));	//normalisation du vecteur + multiplication par le pas de déplacement
	dx=pas*dx/dist;
	dy=pas*dy/dist;
	dz=pas*dz/dist;
	_lookAtParam.eyex+=dx;								//translation de la position de l'observateur
	_lookAtParam.eyey+=dy;
	_lookAtParam.eyez+=dz;
	_lookAtParam.centrex+=dx;								//translation du point observé
	_lookAtParam.centrey+=dy;
	_lookAtParam.centrez+=dz;

}
/****************************************************************************/
void CameraVaisseau::translation_obs(int dir, double pas) //déplace l'observateur vers la droite, la gauche, le bas ou le haut
{
	double /*dx, dy, dz,*/ vect[3], piover180=PI/180, d; //vect2[3];
	switch (dir)
	{
	case 1: //droite gauche		=> translation suivant l'axe Left (à déterminer)	
		rotation3D(90, &_lookAtParam.upx, &_lookAtParam.eyex, &_lookAtParam.centrex, vect); //rotation du point observé, de 90 autour de l'axe Up
		vect[0]=vect[0]-_lookAtParam.eyex;											 //calcul de l'axe Left de l'obs		
		vect[1]=vect[1]-_lookAtParam.eyey;
		vect[2]=vect[2]-_lookAtParam.eyez;
		d=sqrt(vect[0]*vect[0]+vect[1]*vect[1]+vect[2]*vect[2]);				//nomalisation
		vect[0]=vect[0]/d *pas;
		vect[1]=vect[1]/d *pas;
		vect[2]=vect[2]/d *pas;
		_lookAtParam.eyex+=vect[0];			//translation de la position de l'obs
		_lookAtParam.eyey+=vect[1];
		_lookAtParam.eyez+=vect[2];
		_lookAtParam.centrex+=vect[0];			//translation du point observé
		_lookAtParam.centrey+=vect[1];
		_lookAtParam.centrez+=vect[2];
		break;
	case 2://haut bas			=>translation suivant l'axe Up 
		//normaliser vecteur Up s'il ne l'est pas à l'initialisation (=> fonction init)
		_lookAtParam.eyex+=_lookAtParam.upx*pas; //translation de la position
		_lookAtParam.eyey+=_lookAtParam.upy*pas;
		_lookAtParam.eyez+=_lookAtParam.upz*pas;
		_lookAtParam.centrex+=_lookAtParam.upx*pas; //translation du point observé
		_lookAtParam.centrey+=_lookAtParam.upy*pas;
		_lookAtParam.centrez+=_lookAtParam.upz*pas;
		break;		
	}

}

/****************************************************************************/
void CameraVaisseau::rotation3D(double angle, double* axeVect, double* axePt, double* monPt, double* result)
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
