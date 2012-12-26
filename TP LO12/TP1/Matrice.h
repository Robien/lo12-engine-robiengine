#ifndef _MATRICE_H	
#define _MATRICE_H

#include <vector>
#include "Vector3d.h"
#include "const.h"

template <typename T>
class Matrice
{
public:
	Matrice() : _testScale(1, 1, 1)
	{
		reset();
	}
	Matrice(const Matrice<T>& c) : _testScale(1, 1, 1)
	{
		_testScale = 1;
		for (unsigned int i = 0; i < _data.size(); ++i)
		{
			_data.at(i) = c._data.at(i);
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
	std::vector<T>& getVector16()
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

	Vector3d<T> getPosition()
	{
		Vector3d<T> pos;
		pos.setX(_data.at(12)/_data.at(15));
		pos.setY(_data.at(13)/_data.at(15));
		pos.setZ(_data.at(14)/_data.at(15));

		return pos;
	}

	Vector3d<T> getDirection()
	{
		Vector3d<T> dir;
		dir.setX(_data.at(0));
		dir.setY(_data.at(5));
		dir.setZ(_data.at(11));

		return dir;
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
		_testScale.setX(_testScale.getX() * x);
		_testScale.setY(_testScale.getX() * x);
		_testScale.setZ(_testScale.getX() * x);

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
	Vector3d<T>& getScale()
	{
		return _testScale;
	}

	void reset()
	{
		_data.clear();
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

private:
	std::vector<T> _data;
	Vector3d<T> _testScale;

};


#endif