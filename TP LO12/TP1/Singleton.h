
#ifndef _SINGLETON_H_
#define _SINGLETON_H_


template <typename T>
class Singleton
{
protected:
	Singleton()
	{

	};
public:
  static T* get()
  {
    if (NULL == p)
      {
        p = new T;
      }

    return (static_cast<T*> (p));
  }
private:
	static T* p;
};

template <typename T>
T *Singleton<T>::p = NULL;

#endif

