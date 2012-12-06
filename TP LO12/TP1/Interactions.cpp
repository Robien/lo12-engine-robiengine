#include "Interactions.h"
#include "Outil.h"



Interactions::Interactions()
{
	/*
	glutKeyboardFunc(eventsKeyc);
	glutMouseFunc(eventsMouse);
	glutSpecialFunc(eventsSpecialKey)
	*/
}


Interactions::~Interactions()
{
}

void Interactions::addEventCallBack(CB_Interraction* callBack)
{
	_cb.push_back(callBack);
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

}



void Interactions::initInteraction()
{

	

	glutKeyboardFunc(eventsKey);
	glutMouseFunc(eventsMouse);
	glutSpecialFunc(eventsSpecialKey);
	glutMotionFunc(eventsMotionMouse);
	glutPassiveMotionFunc(eventsPassiveMotionMouse);
	glutDisplayFunc(dessine_scene);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	
}


