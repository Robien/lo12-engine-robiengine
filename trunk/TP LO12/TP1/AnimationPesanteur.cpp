#include "AnimationPesanteur.h"
#include "Outil.h"


AnimationPesanteur::AnimationPesanteur(AbstractObjet* objlie): Animation(objlie), _direction(), _rotation()
{
	setLimite(-50,50);
	_direction.setX(Outil::get()->random<GLdouble>(-2,2)/100);
	_direction.setY( Outil::get()->random<GLdouble>(-2,2)/100);
	_direction.setZ( Outil::get()->random<GLdouble>(-2,2)/100);
	_rotation.setX(Outil::get()->random<GLdouble>(-1,1));
	_rotation.setY( Outil::get()->random<GLdouble>(-1,1));
	_rotation.setZ( Outil::get()->random<GLdouble>(-1,1));
	_vitesseRotation = Outil::get()->random<GLdouble>(-2,2);
}


AnimationPesanteur::~AnimationPesanteur()
{
}

void AnimationPesanteur::update()
{
	if(_actif)
	{
		Vector3d<GLdouble> position = getActeur()->getMatrice()->getPosition();
		if(position.getX() > _limiteMax || position.getX() < _limiteMin)
		{
			_direction.setX(-_direction.getX());
		}
		if(position.getY() > _limiteMax || position.getY() < _limiteMin)
		{
			_direction.setY(-_direction.getY());
		}
		if(position.getZ() > _limiteMax || position.getZ() < _limiteMin)
		{
			_direction.setZ(-_direction.getZ());
		}
		getActeur()->getMatrice()->translate(_direction.getX(),_direction.getY(),_direction.getZ());
		getActeur()->getMatrice()->rotate(_vitesseRotation, _direction.getX(),_direction.getY(),_direction.getZ());
	}
}

void AnimationPesanteur::setLimite(GLdouble min,GLdouble max)
{
	_limiteMax = max;
	_limiteMin = min;
}