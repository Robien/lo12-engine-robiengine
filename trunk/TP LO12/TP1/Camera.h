#ifndef _CAMERA_H	
#define _CAMERA_H

class Camera
{
public:
	Camera();
	virtual ~Camera();

	virtual void affiche();
private:
	int i;
};


#endif