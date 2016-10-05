#pragma once
#include "Logger.h"

template <typename T, typename U>
//typedef int T;
//typedef int U;
class Collider
{
	public:
		Collider(T, U);
		~Collider();

		void set(T, U);
		bool collides();

	private:
		T mObject;
		U mProbe;
};

template <typename T, typename U>
Collider<T,U>::Collider(T object, U probe) : mObject(object), mProbe(probe)
{

}

template <typename T, typename U>
Collider<T,U>::~Collider()
{

}

template <typename T, typename U>
void Collider<T,U>::set(T object, U probe)
{
	mObject = object;
	mProbe = probe;
}

template <typename T, typename U>
bool Collider<T,U>::collides()
{
	if(std::is_same<T, sf::FloatRect>::value)
	{
		//Rectangle as initial object
		if(std::is_same<U, sf::Vector2i>::value)
		{
			float a,b,c,d,e,f;
			a = mObject.left;
			b = mObject.top;
			c = mObject.width;
			d = mObject.height;
			e = mProbe.x;
			f = mProbe.y;

			if( (e > a && e < a+c)
			&& (f > b && f < b+d))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	Log(Level::Warning) << "Cannot check collision for specified types!";
	return false;
}
