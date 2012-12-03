#ifndef _MATRICE_H	
#define _MATRICE_H

#include <vector>
#include "const.h"

template <typename T>
class Matrice
{
public:
	Matrice()
	{
		for (unsigned int i = 0; i < 16; ++i)
		{
			if (i%4 == i/4)
			{
				_data.push_back(1);
			}
			else
			{
				_data.push_back(0);
			}
		}
	}
	Matrice(const Matrice<T>& c)
	{
		for (unsigned int i = 0; i < _data.size(); ++i)
		{
			_data.at(i) = c.getVector16().at(i);
		}

	}
	Matrice(T* data)
	{
		//TODO : vérifier la taille
		_data.assign(data, data + 16);
		//std::cout << _data.size() << std::endl;
	}
	virtual ~Matrice(){}

public:
	const T* getMat()
	{
		return _data.data();
	}
	const std::vector<T>& getVector16()
	{
		return _data;
	}

public:
	virtual void print()
	{
		println();
	}
	virtual void println()
	{
		for (unsigned int i = 0; i < 4; ++i)
		{
			for (unsigned int j = 0; j < 4;++j)
			{
				std::cout << _data.at(4*i+j);
				if (j != 3)
				{
					std::cout << " - ";
				}
			}
			std::cout << std::endl;
		}
	}

	void rotate(GLdouble angle, GLdouble axeX, GLdouble axeY, GLdouble axeZ)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		//glLoadIdentity();
		glLoadMatrixd(getMat());
		glRotated(angle, axeX, axeY, axeZ);
		//glTranslated(1.0,10.0, 0); 
		T* newData = (T*) malloc(16*sizeof(T));
		glGetDoublev(GL_MODELVIEW_MATRIX, newData);
		_data.clear();
		_data.assign(newData, newData + 16);
		glPopMatrix();

	}
	void translate(GLdouble x, GLdouble y, GLdouble z)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		//glLoadIdentity();
		glLoadMatrixd(getMat());
		glTranslated(x,y,z); 
		T* newData = (T*) malloc(16*sizeof(T));
		glGetDoublev(GL_MODELVIEW_MATRIX, newData);
		_data.clear();
		_data.assign(newData, newData + 16);
		glPopMatrix();

	}

	void scale(GLdouble x, GLdouble y, GLdouble z)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		//glLoadIdentity();
		glLoadMatrixd(getMat());
		glScaled(x,y,z); 
		T* newData = (T*) malloc(16*sizeof(T));
		glGetDoublev(GL_MODELVIEW_MATRIX, newData);
		_data.clear();
		_data.assign(newData, newData + 16);
		glPopMatrix();

	}
private:
	std::vector<T> _data;

};


#endif