#include "Observateur.h"
#include "math.h"
#include "const.h"
#include <iostream>
#include "Camera.h"

Observateur::Observateur(Eclairage* eclairage)
{
	//_azimut = 0;
	_eclairage = eclairage;
	resetVue();
	_typeView = LOOK_AT_VIEW;


}


Observateur::~Observateur()
{
}


void Observateur::maj()
{


	place_observateur();
	/*
	if (_typeView == POLAR_VIEW)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslated(0, 0, -_distance);
		glRotated(-_twist, 0.0, 0.0, 1.0);
		glRotated(180, 0, 1, 0);
		glRotated(-90-_elevation, 1, 0, 0);
		glRotated(90-_azimut, 0, 0, 1);
	}
	else if (_typeView == PILOT_VIEW)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotated(_roulis, 0.0, 0.0, 1.0);
		glRotated(_tangage, 0.0, 1.0, 0.0);
		glRotated(_lacet, 1.0, 0.0, 0.0);
		glTranslated(-_planex, -_planey, -_planez);
		glRotated(90-_azimut, 0, 0, 1);
	}
	*/
	_eclairage->defAllSources();
}


void Observateur::resetVue()
{

		_polarParam.azimut = 45;
		_polarParam.elevation = 45;
		 _polarParam.distance = 6;
		 _polarParam.twist = 0;

		 _pilotParam.posx = 0;
		 _pilotParam.posy = 0;
		 _pilotParam.posz = 7;
		 _pilotParam.roulis = 0;
		 _pilotParam.tangage = 0;
		 _pilotParam.lacet = 0;

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


/****************************************************************************/
void Observateur::place_observateur()						//applique l'observateur en cours //après modification de la variable typ_obs
{
	switch (_typeView)
	{
	case LOOK_AT_VIEW://gluLookAt()
		glMatrixMode(GL_MODELVIEW);	
		glLoadIdentity();
		gluLookAt(_lookAtParam.eyex,_lookAtParam.eyey,_lookAtParam.eyez, _lookAtParam.centrex, _lookAtParam.centrey, _lookAtParam.centrez, _lookAtParam.upx, _lookAtParam.upy, _lookAtParam.upz);
		glutSetWindowTitle("View Mode: gluLookAt");
		break;

	case POLAR_VIEW://polar_view
		polar_view(_polarParam.azimut, _polarParam.elevation, _polarParam.distance, _polarParam.twist);
		glutSetWindowTitle("View Mode: polar_view");
		break;

	case PILOT_VIEW://pilot_view				
		pilot_view(_pilotParam.posx, _pilotParam.posy, _pilotParam.posz, _pilotParam.roulis, _pilotParam.tangage, _pilotParam.lacet);	
		glutSetWindowTitle("View Mode: pilot_view");
		break;

	}	
	glutPostRedisplay(); //rafraichit la zone de dessin (appelle dessine_scene)
}

/****************************************************************************/
void Observateur::polar_view(double azimut, double elevation, double distance, double twist)
{	
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glTranslatef(0, 0, -distance);
	glRotatef(twist, 0, 0, 1);
	glRotatef(180, 0, 1, 0);
	glRotatef(-90-elevation, 1, 0, 0);
	glRotatef(90-azimut, 0, 0, 1);	
}

/****************************************************************************///default gluLookAt(0,0,0, 0,0,-1, 0,1,0) 
void Observateur::pilot_view(double posx, double posy, double posz, double roulis, double tangage, double lacet)
{	
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	glRotatef(roulis, 0, 0, 1);
	glRotatef(tangage, 1, 0, 0);
	glRotatef(lacet, 0, 1, 0);
	glTranslatef(-posx, -posy, -posz);		
}

/****************************************************************************/
void Observateur::rotationZ_obs(double angle)   //rotation de l'observateur autour de l'axe Z de la scene
{	
	double x, y;
	switch (_typeView)
	{
	case LOOK_AT_VIEW: //gluLookAt			=>rotation de la position de l'observateur
		angle=angle*PI/180.0;
		x=_lookAtParam.eyex;
		y=_lookAtParam.eyey;
		_lookAtParam.eyex=x*cos(angle)-y*sin(angle);
		_lookAtParam.eyey=x*sin(angle)+y*cos(angle);
		break;
	case POLAR_VIEW: //polar				=>varier l'azimuth
		_polarParam.azimut+=angle; 
		break;
	case PILOT_VIEW: //pilot				=>rotation de la position de l'observateur	
		angle=angle*PI/180.0;
		x=_pilotParam.posx;
		y=_pilotParam.posy;
		_pilotParam.posx=x*cos(angle)-y*sin(angle);
		_pilotParam.posy=x*sin(angle)+y*cos(angle);
		break;
	}
	maj();		//replacer l'observateur après la modification des ses paramètres
}
/****************************************************************************/
void Observateur::tourner_tete(int dir, double angle)
{
	double vect[3], vect2[3], vect3[3], Orig[3]={0, 0, 0};

	switch (_typeView)
	{
	case LOOK_AT_VIEW: //gluLookAt		
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
		break;
	case POLAR_VIEW: //polar			
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
		break;
	case PILOT_VIEW: //pilot
		switch (dir)
		{
		case 1: //droite gauche			=>varier le lacet
			_pilotParam.lacet+=angle;
			break;
		case 2: //haut bas				=>varier le tangage
			_pilotParam.tangage+=angle;		
			break;
		}
		break;
	}	
	maj();				//replacer l'observateur après la modification des ses paramètres
}
/****************************************************************************/
void Observateur::zoom(double pas) //permet d'avancer ou de reculer dans la scene
{
	double dx, dy, dz, dist, piover180=PI/180; //vect2[3];
	switch (_typeView)
	{
	case LOOK_AT_VIEW: //gluLookAt  => déplacer l'observateur suivant l'axe PositionObservateur-PointObservé 
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
		break;
	case POLAR_VIEW: //polar		=>varier le parametre distance
		_polarParam.distance+=pas;
		break;
	case PILOT_VIEW: //pilot		=>déplacer l'observateur suivant l'axe de "l'avion" (à déterminer)
		dx = -cos(_pilotParam.tangage*piover180)*sin(_pilotParam.lacet*piover180)*pas; //vecteur directeur normalisé de l'axe de l'avion
		dy = sin(_pilotParam.tangage*piover180)*pas;
		dz = cos(_pilotParam.tangage*piover180)*cos(_pilotParam.lacet*piover180)*pas;
		_pilotParam.posx+=dx;													//translation de la position de l'observateur
		_pilotParam.posy+=dy;
		_pilotParam.posz+=dz;
		break;
	}
	maj();			
}
/****************************************************************************/
void Observateur::translation_obs(int dir, double pas) //déplace l'observateur vers la droite, la gauche, le bas ou le haut
{
	double dx, dy, dz, vect[3], piover180=PI/180, d; //vect2[3];
	switch (_typeView)
	{
	case LOOK_AT_VIEW: //gluLookAt
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
		break;
	case POLAR_VIEW: //polar 
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
	case PILOT_VIEW: //pilot
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
		break;
	}
	maj();
}
			
/****************************************************************************/
void Observateur::rotation3D(double angle, double* axeVect, double* axePt, double* monPt, double* result)
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


void Observateur::changeView()
{
	_typeView = (TYPE_VIEW) (((int) _typeView+1)%3+1);
	std::cout << (int)_typeView << std::endl;
	//_typeView = VIVE_LES_POMMES;
	maj();
}


Scene::MCOORD Observateur::getPosition()
{
	Scene::MCOORD pos;
	GLdouble d;
	
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;
	switch (_typeView)
	{
	case LOOK_AT_VIEW://gluLookAt()
		pos.x = _lookAtParam.eyex;
		pos.y = _lookAtParam.eyey;
		pos.z = _lookAtParam.eyez;
		pos.w = 0;
		break;
	case POLAR_VIEW://polar_view
		pos.z =  _polarParam.distance* sin(_polarParam.elevation*PI/180);
		d = _polarParam.distance * cos(_polarParam.elevation*PI/180);
		pos.x = cos(_polarParam.azimut*PI/180)*d;
		pos.y = sin(_polarParam.azimut*PI/180)*d;
		pos.w = 0;
		break;
	case PILOT_VIEW://pilot_view				
		pos.x = _pilotParam.posx;
		pos.y =  _pilotParam.posy;
		pos.z =  _pilotParam.posz;
		pos.w = 0;
	break;
	}	
	return pos;
}

/*
void Observateur::polarView(GLdouble distance, GLdouble azimut, GLdouble elevation, GLdouble twist)
{
	_distance = distance;
	_azimut = azimut;
	_elevation = elevation;
	_twist = twist;

	_typeView = POLAR_VIEW;

	maj();
}

void Observateur::pilotView(GLdouble planex, GLdouble planey, GLdouble planez, GLdouble roulis, GLdouble tangage, GLdouble lacet)
{

	_planex = planex;
	_planey = planey;
	_planez = planez;

	_roulis = roulis;
	_tangage = tangage;
	_lacet = lacet;

	_typeView = PILOT_VIEW;


	maj();

}

void Observateur::rotateAzimut(GLdouble angle)
{
	_azimut += angle;
	maj();
}
void Observateur::rotateHead(GLdouble angleLR, GLdouble angleUD)
{
	_tangage += angleLR;
	_lacet += angleUD;
	maj();
}
void Observateur::zoom(GLdouble facteur)
{
	//_planex += _planex/(sqrt(_planex*_planex + _planey*_planey + _planez*_planez));
	//_planey += _planey/(sqrt(_planex*_planex + _planey*_planey + _planez*_planez));
	//_planez += _planez/(sqrt(_planex*_planex + _planey*_planey + _planez*_planez));


	_planex += facteur*cos(_tangage*PI/180)*sin(-_lacet*PI/180);
	_planey += facteur*sin(_tangage*PI/180);
	_planez += facteur*cos(_tangage*PI/180)*cos(-_lacet*PI/180);
	


	maj();

}

void Observateur::translate (GLdouble x, GLdouble y, GLdouble z)
{
	_planex += x;
	_planey += y;
	_planez += z;

	maj();
}
*/