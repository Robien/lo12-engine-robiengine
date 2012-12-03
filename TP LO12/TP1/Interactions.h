#pragma once

#include <iostream>
#include "Singleton.h"
#include "Observateur.h"
#include "Scene.h"
#include "Affiche.h"
#include "Outil.h"
#include <vector>


class CB_Interraction
{
public:
	CB_Interraction(){}
	virtual ~CB_Interraction(){}
public:
	virtual void eventsSpecialKey(int key, int x, int y){}
	virtual void eventsKey(unsigned char key, int x, int y){}
	virtual void eventsMouse(int boutton, int etat, int x, int y){}
	virtual void eventsMotionMouse(int x, int y){}
	virtual void idle(){}
	virtual void reshape(int largeur, int hauteur){}
	virtual void dessine_scene(){}

};

class Interactions : public Singleton<Interactions>
{

public:
	Interactions();
	virtual ~Interactions();
	void initInteraction(Observateur* ob, Scene* scene, Affiche* affiche);

public:
	void addEventCallBack(CB_Interraction* callBack);


private:

	static void eventsSpecialKey(int key, int x, int y);
	static void eventsKey(unsigned char key, int x, int y);
	static void eventsMouse(int boutton, int etat, int x, int y);
	static void eventsMotionMouse(int x, int y);
	static void idle();
	static void reshape(int largeur, int hauteur);
	static void dessine_scene();


	Affiche* _affiche;
	Scene* _scene;
public:
	Observateur* _ob;
private:
	int _posCurseurX;
	int _posCurseurY;
	int _mouseState;

private:
	std::vector<CB_Interraction*> _cb;

};





