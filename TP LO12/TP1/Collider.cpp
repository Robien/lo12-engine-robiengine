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