#ifndef _CONST_H_
#define _CONST_H_

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

	#ifdef TEMPO_UNIX
		#define SLEEP(x) sleep(x);glFlush()
	#endif
	#ifdef TEMPO_WIN32
		#define SLEEP(x) Sleep(x);glFlush()
	#endif

#define PI 3.1415926535 

#endif
