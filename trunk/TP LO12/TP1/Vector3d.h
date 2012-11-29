#ifndef _VECTOR2D_H	
#define _VECTOR2D_H

template <typename T>
class Vector3d
{
public:
	Vector3d(){}
	Vector3d(const Vector3d<T>& c)
	{
		_x = c.getX();
		_y = c.getY();
		_z = c.getZ();
	}
	Vector3d(T x, T y, T z) :_x(x), _y(y), _z(z)
	{

	}
	virtual ~Vector3d(){}

public:
	const T getX()
	{
		return _x;
	}
	const T getY()
	{
		return _y;
	}
	const T getZ()
	{
		return _Z;
	}
	void setX(T x)
	{
		_x = x;
	}
	void setY(T y)
	{
		_y = y;
	}
	void setZ(T z)
	{
		_z = z;
	}

	Vector3d<T> operator+(const Vector3d<T>& other)
	{
		return Vector3d<T>(other._x + _x, other._y + _y, other._z + _z);
	}
	Vector3d<T> operator-(const Vector3d<T>& other)
	{
		return Vector3d<T>(other._x - _x, other._y - _y, other._z - _z);
	}
	

public:
	virtual void print()
	{
		std::cout << "X=" << _x << ", Y=" << _y << ", Z=" << _z;
	}
	virtual void println()
	{
		std::cout << "X=" << _x << ", Y=" << _y << ", Z=" << _z << std::endl;
	}

private:
	T _x, _y, _z;

};


#endif