#include "Collider.h"


Collider::Collider()
{
	_isSet = false;
}


Collider::~Collider()
{
}

void Collider::reset()
{
	_isSet = false;
}

void Collider::addPoint(Vector3d<GLdouble>& point)
{
	if (!_isSet)
	{
		_CoordMin = point;
		_CoordMax = point;
		_isSet = true;
	}
	else
	{

		if (point.getX() < _CoordMin.getX())
		{
			_CoordMin.setX(point.getX());
		}
		if (point.getY() < _CoordMin.getY())
		{
			_CoordMin.setY(point.getY());
		}
		if (point.getZ() < _CoordMin.getZ())
		{
			_CoordMin.setZ(point.getZ());
		}


		if (point.getX() > _CoordMax.getX())
		{
			_CoordMax.setX(point.getX());
		}
		if (point.getY() > _CoordMax.getY())
		{
			_CoordMax.setY(point.getY());
		}
		if (point.getZ() > _CoordMax.getZ())
		{
			_CoordMax.setZ(point.getZ());
		}

	}

}

void  Collider::addCollider(Collider& collider)
{
	addPoint(collider.getMin());
	addPoint(collider.getMax());
}

bool Collider::colide(Vector3d<GLdouble>& point)
{
	if (!_isSet)
	{
		return false;
	}

	return (point.getX() > _CoordMin.getX() && point.getY() > _CoordMin.getY() && point.getZ() > _CoordMin.getZ()
		&&
		point.getX() < _CoordMax.getX() && point.getY() < _CoordMax.getY() && point.getZ() < _CoordMax.getZ());

}

Vector3d<GLdouble> Collider::getMin()
{
	return _CoordMin;
}
Vector3d<GLdouble> Collider::getMax()
{
	return _CoordMax;
}
Vector3d<GLdouble> mult(Vector3d<GLdouble>& vect, Matrice<GLdouble>& mat)
{
	Vector3d<GLdouble> res;

	res.setX(vect.getX() * mat.getVector16().at(0) + vect.getY() * mat.getVector16().at(1) + vect.getZ() * mat.getVector16().at(2));
	res.setY(vect.getX() * mat.getVector16().at(3) + vect.getY() * mat.getVector16().at(4) + vect.getZ() * mat.getVector16().at(5));
	res.setZ(vect.getX() * mat.getVector16().at(6) + vect.getY() * mat.getVector16().at(7) + vect.getZ() * mat.getVector16().at(8));

	return res;
}

void Collider::afficheWithMat(Matrice<GLdouble>* mat, Matrice<GLdouble>* m)
{
	glPushMatrix();
	//glLoadIdentity();
	Collider* coll = new Collider();
	
	mat->translate(-mat->getPosition().getX(), -mat->getPosition().getY(), -mat->getPosition().getZ());
	
	std::cout << mat->getPosition().getX() << std::endl;

	coll->addPoint(mult(_CoordMin, *mat));
	
	coll->addPoint(mult(Vector3d<GLdouble>(_CoordMin.getX(), _CoordMin.getY(), _CoordMax.getZ()), *mat));
	coll->addPoint(mult(Vector3d<GLdouble>(_CoordMin.getX(), _CoordMax.getY(), _CoordMin.getZ()), *mat));
	coll->addPoint(mult(Vector3d<GLdouble>(_CoordMin.getX(), _CoordMax.getY(), _CoordMax.getZ()), *mat));
	coll->addPoint(mult(Vector3d<GLdouble>(_CoordMax.getX(), _CoordMin.getY(), _CoordMin.getZ()), *mat));
	coll->addPoint(mult(Vector3d<GLdouble>(_CoordMax.getX(), _CoordMin.getY(), _CoordMax.getZ()), *mat));
	coll->addPoint(mult(Vector3d<GLdouble>(_CoordMax.getX(), _CoordMax.getY(), _CoordMin.getZ()), *mat));

	coll->addPoint(mult(_CoordMax, *mat));
	//glTranslated(mat->getPosition().getX(), mat->getPosition().getY(), mat->getPosition().getZ());
	affiche();
	coll->affiche();
	glPopMatrix();
}

void Collider::affiche()
{
	glMatrixMode(GL_MODELVIEW);

	glBegin(GL_LINE_LOOP); // affichage fils de fer
	//glColor3f(scene->tabmat[scene->tabface[iface].imat].ambiante.r,scene->tabmat[scene->tabface[iface].imat].ambiante.g,scene->tabmat[scene->tabface[iface].imat].ambiante.b); 
	glColor3f(1, 1, 1); 
	glVertex3d(_CoordMin.getX(),_CoordMin.getY(),_CoordMin.getZ());
	glVertex3d(_CoordMin.getX(),_CoordMax.getY(),_CoordMin.getZ());
	glVertex3d(_CoordMin.getX(),_CoordMax.getY(),_CoordMax.getZ());
	glVertex3d(_CoordMin.getX(),_CoordMin.getY(),_CoordMax.getZ());
	glEnd();

	glBegin(GL_LINE_LOOP); // affichage fils de fer
	//glColor3f(scene->tabmat[scene->tabface[iface].imat].ambiante.r,scene->tabmat[scene->tabface[iface].imat].ambiante.g,scene->tabmat[scene->tabface[iface].imat].ambiante.b); 
	glColor3f(1, 1, 1); 
	glVertex3d(_CoordMin.getX(),_CoordMin.getY(),_CoordMin.getZ());
	glVertex3d(_CoordMax.getX(),_CoordMin.getY(),_CoordMin.getZ());
	glVertex3d(_CoordMax.getX(),_CoordMax.getY(),_CoordMin.getZ());
	glVertex3d(_CoordMin.getX(),_CoordMax.getY(),_CoordMin.getZ());
	glEnd();

		glBegin(GL_LINE_LOOP); // affichage fils de fer
	//glColor3f(scene->tabmat[scene->tabface[iface].imat].ambiante.r,scene->tabmat[scene->tabface[iface].imat].ambiante.g,scene->tabmat[scene->tabface[iface].imat].ambiante.b); 
	glColor3f(1, 1, 1); 
	glVertex3d(_CoordMin.getX(),_CoordMin.getY(),_CoordMin.getZ());
	glVertex3d(_CoordMax.getX(),_CoordMin.getY(),_CoordMin.getZ());
	glVertex3d(_CoordMax.getX(),_CoordMin.getY(),_CoordMax.getZ());
	glVertex3d(_CoordMin.getX(),_CoordMin.getY(),_CoordMax.getZ());
	glEnd();

			glBegin(GL_LINE_LOOP); // affichage fils de fer
	//glColor3f(scene->tabmat[scene->tabface[iface].imat].ambiante.r,scene->tabmat[scene->tabface[iface].imat].ambiante.g,scene->tabmat[scene->tabface[iface].imat].ambiante.b); 
	glColor3f(1, 1, 1); 
	glVertex3d(_CoordMax.getX(),_CoordMax.getY(),_CoordMax.getZ());
	glVertex3d(_CoordMin.getX(),_CoordMax.getY(),_CoordMax.getZ());
	glVertex3d(_CoordMin.getX(),_CoordMin.getY(),_CoordMax.getZ());
	glVertex3d(_CoordMax.getX(),_CoordMin.getY(),_CoordMax.getZ());
	glEnd();

	
			glBegin(GL_LINE_LOOP); // affichage fils de fer
	//glColor3f(scene->tabmat[scene->tabface[iface].imat].ambiante.r,scene->tabmat[scene->tabface[iface].imat].ambiante.g,scene->tabmat[scene->tabface[iface].imat].ambiante.b); 
	glColor3f(1, 1, 1); 
	glVertex3d(_CoordMax.getX(),_CoordMax.getY(),_CoordMax.getZ());
	glVertex3d(_CoordMin.getX(),_CoordMax.getY(),_CoordMax.getZ());
	glVertex3d(_CoordMin.getX(),_CoordMax.getY(),_CoordMin.getZ());
	glVertex3d(_CoordMax.getX(),_CoordMax.getY(),_CoordMin.getZ());
	glEnd();

				glBegin(GL_LINE_LOOP); // affichage fils de fer
	//glColor3f(scene->tabmat[scene->tabface[iface].imat].ambiante.r,scene->tabmat[scene->tabface[iface].imat].ambiante.g,scene->tabmat[scene->tabface[iface].imat].ambiante.b); 
	glColor3f(1, 1, 1); 
	glVertex3d(_CoordMax.getX(),_CoordMax.getY(),_CoordMax.getZ());
	glVertex3d(_CoordMax.getX(),_CoordMin.getY(),_CoordMax.getZ());
	glVertex3d(_CoordMax.getX(),_CoordMin.getY(),_CoordMin.getZ());
	glVertex3d(_CoordMax.getX(),_CoordMax.getY(),_CoordMin.getZ());
	glEnd();


}