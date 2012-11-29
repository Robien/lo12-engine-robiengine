#pragma once

#include <iostream>

#ifdef _MSC_VER
#define TEMPO_WIN32
#else
#define TEMPO_UNIX
#endif

#ifdef TEMPO_UNIX
#include <unistd.h> /*Temporisation pour unix*/
#endif

#ifdef TEMPO_WIN32
#include <windows.h> /*Temporisation pour windows*/
#endif

#if defined(__APPLE__) && defined(__MACH__)
        #include <GLUT/glut.h>
        #include <OpenGL/gl.h>
        #include <OpenGL/glu.h>
#else
        #include <glut.h>
        #include <GL/gl.h>
        #include <GL/glu.h>
#endif


#include "Singleton.h"
#include "Observateur.h"
#include "Scene.h"
#include "Affiche.h"

class Interactions : public Singleton<Interactions>
{

public:
	Interactions();
	virtual ~Interactions();
	void initInteraction(Observateur* ob, Scene* scene, Affiche* affiche);

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
public :Observateur* _ob;
private:
	int _posCurseurX;
	int _posCurseurY;
	int _mouseState;
};





