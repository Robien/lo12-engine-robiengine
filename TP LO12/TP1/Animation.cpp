#include "Animation.h"


class AnimInteraction : public CB_Interraction
{
public:
	AnimInteraction(Animation* anim): _animation(anim)
	{
		_isOnPause = false;
	}
	~AnimInteraction(){}

public:
	virtual void eventsSpecialKey(int key, int x, int y) {}
	virtual void eventsKey(unsigned char key, int x, int y)
	{
		switch(key)
		{
		case 'p' :  _isOnPause = !_isOnPause;
		break;
		}
	}
	virtual void eventsMouse(int boutton, int etat, int x, int y){}
	virtual void eventsMotionMouse(int x, int y){}
	virtual void idle() {}
	virtual void reshape(int largeur, int hauteur) {}
	virtual void dessine_scene() {}
	virtual void periodicEvent()
	{
		if(!_isOnPause)
		{_animation->update();}
	} 

private:
	Animation* _animation;
	bool _isOnPause;

};


Animation::Animation(AbstractObjet* objlie): _acteur(objlie)
{
	Interactions::get()->addEventCallBack(new AnimInteraction(this));
	objlie->setAnimation(this);
}


Animation::~Animation()
{
}


void Animation::update()
{

}


AbstractObjet* Animation::getActeur()
{
	return _acteur;
}

void Animation::proxEvent(GLdouble distance)
{
}