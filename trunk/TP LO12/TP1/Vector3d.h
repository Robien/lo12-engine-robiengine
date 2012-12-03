#ifndef _VECTOR3D_H	
#define _VECTOR3D_H

template <typename T>
class Vector3d
{
public:
	Vector3d()
	{
		_test = (T*) (malloc(3*sizeof(T)));
	}
	Vector3d(const Vector3d<T>& c)
	{
		_x = c._x;
		_y = c._y;
		_z = c._z;
		_test = (T*) (malloc(3*sizeof(T)));
	}
	Vector3d(T x, T y, T z) :_x(x), _y(y), _z(z)
	{
		_test = (T*) (malloc(3*sizeof(T)));
	}
	virtual ~Vector3d()
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
	const T getZ()
	{
		return _z;
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
	template <typename S>
	Vector3d<T> operator/(const S& scalaire)
	{
		return Vector3d<T>(_x/scalaire, _y/scalaire, _z/scalaire);
	}
	T* getCStyle() //attention aux free !
	{
		
		_test[0] = _x;
		_test[1] = _y;
		_test[2] = _z;
		return _test;
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
	T* _test;

};


#endif