#include "Interactions.h"
#include "Camera.h"



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






void Interactions::eventsSpecialKey(int key, int x, int y)
{
	float mult = 0.1;
	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
	{
		mult *= -1;
	}

	double step_trans=0.1, step_rot=5, step_rot_obs=5;

	switch(key)
	{
		case GLUT_KEY_F1:	Interactions::get()->_scene->translateObjetSelectionne(1*mult,0,0);	break;
		case GLUT_KEY_F2:	Interactions::get()->_scene->translateObjetSelectionne(0,1*mult,0);	break;
		case GLUT_KEY_F3:	Interactions::get()->_scene->translateObjetSelectionne(0,0,1*mult);	break;
		case GLUT_KEY_F4:	Interactions::get()->_scene->rotateObjetSelectionne(1,0,0,90*mult);	break;
		case GLUT_KEY_F5:	Interactions::get()->_scene->rotateObjetSelectionne(0,1,0,90*mult);	break;
		case GLUT_KEY_F6:	Interactions::get()->_scene->rotateObjetSelectionne(0,0,1,90*mult);	break;
		case GLUT_KEY_F7:	Interactions::get()->_scene->toggleFilted();	break;
		case GLUT_KEY_F8:	Interactions::get()->_scene->tabsource[0].allume = !Interactions::get()->_scene->tabsource[0].allume; Interactions::get()->_ob->maj();	break;
		case GLUT_KEY_F9:	Interactions::get()->_scene->tabsource[1].allume = !Interactions::get()->_scene->tabsource[1].allume; Interactions::get()->_ob->maj();	break;
		case GLUT_KEY_F10:	Interactions::get()->_ob->rotationZ_obs(90*mult); break;
		case GLUT_KEY_F12:  Interactions::get()->_ob->changeView();
		/*case GLUT_KEY_DOWN:	Interactions::get()->_ob->tourner_tete(1, 90*mult); break;
		case GLUT_KEY_UP:	Interactions::get()->_ob->tourner_tete(1, -90*mult); break;
		case GLUT_KEY_RIGHT:	Interactions::get()->_ob->tourner_tete(2,  90*mult); break;
		case GLUT_KEY_LEFT: Interactions::get()->_ob->tourner_tete(2, -90*mult);	break;*/
			case GLUT_KEY_LEFT:
		if (mult==-1)
			Interactions::get()->_ob->translation_obs(1, step_trans);
		else
			Interactions::get()->_ob->tourner_tete(1, -step_rot_obs);
		break;
	case GLUT_KEY_RIGHT:
		if (mult==-1)
			Interactions::get()->_ob->translation_obs(1, -step_trans);
		else
			Interactions::get()->_ob->tourner_tete(1, step_rot_obs);
		break;
	case GLUT_KEY_UP:
		if (mult==-1)
			Interactions::get()->_ob->translation_obs(2, step_trans);
		else
			Interactions::get()->_ob->tourner_tete(2, -step_rot_obs);
		break;
	case GLUT_KEY_DOWN:
		if (mult==-1)
			Interactions::get()->_ob->translation_obs(2, -step_trans);
		else
			Interactions::get()->_ob->tourner_tete(2, step_rot_obs);
		break;
		default:	std::cout << key << std::endl;	break;
	}
//	Interactions::get()->_ob->maj();

}
void Interactions::eventsKey(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:	exit(0);	break;
		case 32 :	Interactions::get()->_scene->changerObjetSelectionne();	break;
		case 105 :  Interactions::get()->_scene->resetObjet();	break;
		case 111 :	Interactions::get()->_ob->resetVue();	break;

		default: std::cout << (int)key << std::endl;break;
	}
}
void Interactions::eventsMouse(int boutton, int etat, int x, int y)
{
	if(boutton == GLUT_LEFT_BUTTON)
	{
		if(etat == GLUT_DOWN)
		{
			Interactions::get()->_posCurseurX = x;
			Interactions::get()->_posCurseurY = y;
		}
	}
	else if(boutton ==GLUT_RIGHT_BUTTON)
	{
		if(etat == GLUT_DOWN)
		{
			Interactions::get()->_posCurseurX = x;
			Interactions::get()->_posCurseurY = y;
		}
	}
	else if(boutton ==GLUT_MIDDLE_BUTTON)
	{
		if(etat == GLUT_DOWN)
			{
				Interactions::get()->_posCurseurX = x;
				Interactions::get()->_posCurseurY = y;
			}
	}
	Interactions::get()->_mouseState = boutton;
}

void Interactions::eventsMotionMouse(int x, int y)
{
	switch(Interactions::get()->_mouseState)
	{
	case GLUT_RIGHT_BUTTON:
		Interactions::get()->_ob->translation_obs(2, ((float)Interactions::get()->_posCurseurY-y)/50);
		Interactions::get()->_ob->translation_obs(1,((float)Interactions::get()->_posCurseurX-x)/50);
		break;
	case GLUT_LEFT_BUTTON : 
		Interactions::get()->_ob->tourner_tete(1, ((float)Interactions::get()->_posCurseurX-x)/10);	
		Interactions::get()->_ob->tourner_tete(2, ((float)Interactions::get()->_posCurseurY-y)/10);	
		break;
	case GLUT_MIDDLE_BUTTON : Interactions::get()->_ob->rotationZ_obs(((float)Interactions::get()->_posCurseurX-x)/10); 
								// Interactions::get()->_ob->translate(0,0, ((float)Interactions::get()->_posCurseurY-y)/50);
		Interactions::get()->_ob->zoom(((float)Interactions::get()->_posCurseurY-y)/50);
		break;
		default: ;

	}

	Interactions::get()->_posCurseurX = x;
	Interactions::get()->_posCurseurY = y;

	//Interactions::get()->_ob->maj();
}



void Interactions::idle()
{

	//scene->transfo[0]= ((int)scene->transfo[0]+1) %5;

			// glMatrixMode(GL_MODELVIEW);
			 		//  gluLookAt(5,3,3,0,0,0,0,0,1);
			//glLoadMatrixd(scene->transfo);
					 // glMultMatrixf
					//  glRotated(i++,1, 0, 0);
			// glGetDoublev(GL_MODELVIEW_MATRIX, scene->transfo);
				
				
			 	Interactions::get()->_affiche->dessine_scene();
		//	glLoadIdentity();

}

void Interactions::reshape(int largeur, int hauteur)
{
		if(hauteur < 1)
		{ hauteur = 1;}
	glViewport(0, 0, largeur, hauteur);

 
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(90,((float) largeur)/hauteur,0.1,100) ;
		glMatrixMode(GL_MODELVIEW);
		Interactions::get()->_ob->maj();


}

void Interactions::dessine_scene()
{
	
	Interactions::get()->_affiche->dessine_scene();
}



void Interactions::initInteraction(Observateur* ob, Scene* scene, Affiche* affiche)
{
	_scene = scene;
	_ob = ob;
	_affiche = affiche;

	glutKeyboardFunc(eventsKey);
	glutMouseFunc(eventsMouse);
	glutSpecialFunc(eventsSpecialKey);
	glutMotionFunc(eventsMotionMouse);
	glutDisplayFunc(dessine_scene);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	_mouseState = -1;
	
}


