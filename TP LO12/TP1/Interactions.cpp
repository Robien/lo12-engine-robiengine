#include "Interactions.h"
#include "Outil.h"



Interactions::Interactions()
{
	/*
	glutKeyboardFunc(eventsKeyc);
	glutMouseFunc(eventsMouse);
	glutSpecialFunc(eventsSpecialKey)
	*/
	_deltaTimePeriodicEvent = 0;

}


Interactions::~Interactions()
{
}

void Interactions::addEventCallBack(CB_Interraction* callBack)
{
	_cb.push_back(callBack);
}

void Interactions::RemoveEventCallBack(CB_Interraction* callBack)
{
	for (unsigned int i = 0; i < _cb.size(); ++i) // détecter found ?
	{
		if (_cb.at(i) == callBack)
		{
			_cb.at(i) = _cb.at(_cb.size() - 1);
			_cb.pop_back();
		}
	}
}


void Interactions::eventsSpecialKey(int key, int x, int y)
{
	for (unsigned int i = 0; i < Interactions::get()->_cb.size(); ++i)
	{
		Interactions::get()->_cb.at(i)->eventsSpecialKey(key, x, y);
	}


}
void Interactions::eventsKey(unsigned char key, int x, int y)
{
	for (unsigned int i = 0; i < Interactions::get()->_cb.size(); ++i)
	{
		Interactions::get()->_cb.at(i)->eventsKey(key, x, y);
	}

}
void Interactions::eventsMouse(int boutton, int etat, int x, int y)
{

	for (unsigned int i = 0; i < Interactions::get()->_cb.size(); ++i)
	{
		Interactions::get()->_cb.at(i)->eventsMouse(boutton, etat, x, y);
	}

}

void Interactions::eventsMotionMouse(int x, int y)
{

	for (unsigned int i = 0; i < Interactions::get()->_cb.size(); ++i)
	{
		Interactions::get()->_cb.at(i)->eventsMotionMouse(x, y);
	}

}

void Interactions::eventsPassiveMotionMouse(int x, int y)
{

	for (unsigned int i = 0; i < Interactions::get()->_cb.size(); ++i)
	{
		Interactions::get()->_cb.at(i)->eventsPassiveMotionMouse(x, y);
	}

}


void Interactions::idle()
{
	GLdouble tmp = glutGet(GLUT_ELAPSED_TIME);
	Interactions::get()->_deltaTime = tmp - Interactions::get()->_previousTime;
	Interactions::get()->_previousTime = tmp;

	for (unsigned int i = 0; i < Interactions::get()->_cb.size(); ++i)
	{
		Interactions::get()->_cb.at(i)->idle();
	}

}

void Interactions::reshape(int largeur, int hauteur)
{

	for (unsigned int i = 0; i < Interactions::get()->_cb.size(); ++i)
	{
		Interactions::get()->_cb.at(i)->reshape(largeur, hauteur);
	}


}

void Interactions::dessine_scene()
{

	for (unsigned int i = 0; i < Interactions::get()->_cb.size(); ++i)
	{
		Interactions::get()->_cb.at(i)->dessine_scene();
	}

	Interactions::get()->_deltaTimePeriodicEvent += Interactions::get()->_deltaTime;

	if (Interactions::get()->_deltaTimePeriodicEvent > 0.1)
	{
		for (unsigned int i = 0; i < Interactions::get()->_cb.size(); ++i)
		{
			Interactions::get()->_cb.at(i)->periodicEvent();
		}
	}

}



void Interactions::initInteraction()
{

	_deltaTime = 0;
	_previousTime = glutGet(GLUT_ELAPSED_TIME);

	glutKeyboardFunc(eventsKey);
	glutMouseFunc(eventsMouse);
	glutSpecialFunc(eventsSpecialKey);
	glutMotionFunc(eventsMotionMouse);
	glutPassiveMotionFunc(eventsPassiveMotionMouse);
	glutDisplayFunc(dessine_scene);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);


}

GLdouble Interactions::getDeltaTime()
{
	return _deltaTime;
}
