#include "CameraPilotView.h"
#include "Interactions.h"




class CameraPilotViewEvent : public CB_Interraction
{
public:
	CameraPilotViewEvent(CameraPilotView* camera) : _camera(camera)
	{
		_mouseState = -1;
	}
	virtual ~CameraPilotViewEvent(){}
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
	CameraPilotView* _camera;

private:
	int _posCurseurX;
	int _posCurseurY;
	int _mouseState;

};




CameraPilotView::CameraPilotView()
{
	_interraction = new CameraPilotViewEvent(this);
	Interactions::get()->addEventCallBack(_interraction);
	resetVue();
}


CameraPilotView::~CameraPilotView()
{
	Interactions::get()->RemoveEventCallBack(_interraction);
}



void CameraPilotView::resetVue()
{
	_pilotParam.posx = 0;
	_pilotParam.posy = 0;
	_pilotParam.posz = 7;
	_pilotParam.roulis = 0;
	_pilotParam.tangage = 0;
	_pilotParam.lacet = 0;

}


/****************************************************************************/
void CameraPilotView::affiche()						//applique l'observateur en cours //après modification de la variable typ_obs
{
	Camera::affiche();
	//glMatrixMode(GL_MODELVIEW);	
	//glLoadIdentity();
	pilot_view(_pilotParam.posx, _pilotParam.posy, _pilotParam.posz, _pilotParam.roulis, _pilotParam.tangage, _pilotParam.lacet);	


	//glutPostRedisplay(); //rafraichit la zone de dessin (appelle dessine_scene)
}
void CameraPilotView::pilot_view(double posx, double posy, double posz, double roulis, double tangage, double lacet)
{	
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glRotatef(roulis, 0, 0, 1);
	glRotatef(tangage, 1, 0, 0);
	glRotatef(lacet, 0, 1, 0);
	glTranslatef(-posx, -posy, -posz);		
}

/****************************************************************************/
void CameraPilotView::rotationZ_obs(double angle)   //rotation de l'observateur autour de l'axe Z de la scene
{	
	double x, y;
	angle=angle*PI/180.0;
	x=_pilotParam.posx;
	y=_pilotParam.posy;
	_pilotParam.posx=x*cos(angle)-y*sin(angle);
	_pilotParam.posy=x*sin(angle)+y*cos(angle);
}
/****************************************************************************/
void CameraPilotView::tourner_tete(int dir, double angle)
{
	switch (dir)
	{
	case 1: //droite gauche			=>varier le lacet
		_pilotParam.lacet+=angle;
		break;
	case 2: //haut bas				=>varier le tangage
		_pilotParam.tangage+=angle;		
		break;
	}

}
/****************************************************************************/
void CameraPilotView::zoom(double pas) //permet d'avancer ou de reculer dans la scene
{
	pas *= 20;
	double dx, dy, dz,  piover180=PI/180; 
	dx = -cos(_pilotParam.tangage*piover180)*sin(_pilotParam.lacet*piover180)*pas; //vecteur directeur normalisé de l'axe de l'avion
	dy = sin(_pilotParam.tangage*piover180)*pas;
	dz = cos(_pilotParam.tangage*piover180)*cos(_pilotParam.lacet*piover180)*pas;
	_pilotParam.posx+=dx;													//translation de la position de l'observateur
	_pilotParam.posy+=dy;
	_pilotParam.posz+=dz;

}
/****************************************************************************/
void CameraPilotView::translation_obs(int dir, double pas) //déplace l'observateur vers la droite, la gauche, le bas ou le haut
{
	double dx, dy, dz,  piover180=PI/180; //vect2[3];
			switch (dir)
		{
		case 1: //droite gauche
			dx = cos(_pilotParam.roulis*piover180)*sin((-90-_pilotParam.tangage)*piover180)*pas; //vecteur direction gauche de l'avion
			dy = sin(_pilotParam.roulis*piover180)*pas;
			dz = cos(_pilotParam.roulis*piover180)*cos((-90-_pilotParam.tangage)*piover180)*pas;
			_pilotParam.posx+=dx;  //translation de la position de l'avion
			_pilotParam.posy+=dy;
			_pilotParam.posz+=dz;
			break;
		case 2://haut bas
			dx = sin(_pilotParam.roulis*piover180)*sin((_pilotParam.tangage)*piover180)*pas; //vecteur direction haut de l'avion
			dy = cos(_pilotParam.roulis*piover180)*pas;
			dz = -sin(_pilotParam.roulis*piover180)*cos((_pilotParam.tangage)*piover180)*pas;
			_pilotParam.posx+=dx;	//translation de la position de l'avion
			_pilotParam.posy+=dy;
			_pilotParam.posz+=dz;
			break;		
		}

}

/****************************************************************************/
void CameraPilotView::rotation3D(double angle, double* axeVect, double* axePt, double* monPt, double* result)
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
void CameraPilotView::pause()
{
	Interactions::get()->RemoveEventCallBack(_interraction);
}

void CameraPilotView::unpause()
{
	Interactions::get()->addEventCallBack(_interraction);
}