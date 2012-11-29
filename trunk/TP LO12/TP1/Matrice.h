#ifndef _MATRICE_H	
#define _MATRICE_H

#include <vector>

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
		_data.assign(data, data + 16 - 1);
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
		std::cout << "Attention ! le sens n a pas ete verifie !" << std::endl;
		for (unsigned int i =0; i < 4; ++i)
		{
			for (unsigned int j =0; j < 4;++j)
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

private:
	std::vector<T> _data;

};


#endif