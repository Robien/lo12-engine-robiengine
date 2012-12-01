#ifndef _VECTOR2D_H	
#define _VECTOR2D_H

template <typename T>
class Vector2d
{
public:
	Vector2d()
	{
		_test = (T*) (malloc(2*sizeof(T)));
	}
	Vector2d(const Vector2d<T>& c)
	{
		_x = c._x
		_y = c._y
		_test = (T*) (malloc(2*sizeof(T)));
	}
	Vector2d(T x, T y) :_x(x), _y(y)
	{
		_test = (T*) (malloc(2*sizeof(T)));
	}
	virtual ~Vector2d()
	{
		delete _test;
	}

public:
	const T getX()
	{
		return _x;
	}
	const T getY()
	{
		return _y;
	}
	void setX(T x)
	{
		_x = x;
	}
	void setY(T y)
	{
		_y = y;
	}
	Vector2d<T> operator+(const Vector2d<T>& other)
	{
		return Vector2d<T>(other._x + _x, other._y + _y);
	}
	Vector2d<T> operator-(const Vector2d<T>& other)
	{
		return Vector2d<T>(other._x - _x, other._y - _y);
	}
	
	T* getCStyle() //attention aux free !
	{
		_test[0] = _x;
		_test[1] = _y;
		return _test;
	}
public:
	virtual void print()
	{
		std::cout << "X=" << _x << ", Y=" << _y;
	}
	virtual void println()
	{
		std::cout << "X=" << _x << ", Y=" << _y << std::endl;
	}

private:
	T _x, _y;
	T* _test;

};


#endif