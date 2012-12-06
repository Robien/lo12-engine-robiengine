#ifndef _INTERACTIONS_H	
#define _INTERACTIONS_H


#include <vector>
#include "Singleton.h"


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
	virtual void eventsPassiveMotionMouse(int x, int y){}
	virtual void idle(){}
	virtual void reshape(int largeur, int hauteur){}
	virtual void dessine_scene(){}

};

class Interactions : public Singleton<Interactions>
{

public:
	Interactions();
	virtual ~Interactions();
	void initInteraction();

public:
	void addEventCallBack(CB_Interraction* callBack);


private:

	static void eventsSpecialKey(int key, int x, int y);
	static void eventsKey(unsigned char key, int x, int y);
	static void eventsMouse(int boutton, int etat, int x, int y);
	static void eventsMotionMouse(int x, int y);
	static void eventsPassiveMotionMouse(int x, int y);
	static void idle();
	static void reshape(int largeur, int hauteur);
	static void dessine_scene();


private:
	std::vector<CB_Interraction*> _cb;

};


#endif;




