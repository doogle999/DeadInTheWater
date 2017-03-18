#pragma once

#include <SFML\System\Vector2.hpp>

#include <array>

template <typename T, unsigned int N>
class PVector;

template <typename T, unsigned int N> // Type, dimensions 
class PVectorBase
{
	public:
		PVectorBase();
		PVectorBase(std::array<T, N> c);

		template <typename otherT>
		PVector<otherT, N> convert();

		bool operator==(const PVector<T, N>& pv) const;

		PVector<T, N> operator*(const double& s) const;
		double dot(const PVector<T, N>& pv) const;

		PVector<T, N> operator+(const PVector<T, N>& pv) const;
		PVector<T, N> operator-(const PVector<T, N>& pv) const;

		double mag() const;

		std::array<T, N> c; // Components
};

template <typename T, unsigned int N>
PVectorBase<T, N>::PVectorBase() {}
template <typename T, unsigned int N>
PVectorBase<T, N>::PVectorBase(std::array<T, N> c)
{
	this->c = c;
}

template <typename T, unsigned int N>
template <typename otherT>
PVector<otherT, N> PVectorBase<T, N>::convert()
{
	PVector<otherT, N> pv;

	for(unsigned int i = 0; i < N; i++)
	{
		pv.c[i] = c[i];
	}

	return pv;
}

template <typename T, unsigned int N>
bool PVectorBase<T, N>::operator==(const PVector<T, N>& pv) const
{
	for(unsigned int i = 0; i < N; i++)
	{
		if(pv.c[i] != c[i])
		{
			return false;
		}
	}

	return true;
}

template <typename T, unsigned int N>
PVector<T, N> PVectorBase<T, N>::operator*(const double& s) const
{
	PVector<T, N> r;

	for(unsigned int i = 0; i < N; i++)
	{
		r.c[i] = c[i] * s;
	}

	return r;
};
template <typename T, unsigned int N>
double PVectorBase<T, N>::dot(const PVector<T, N>& pv) const
{
	double r = 0;

	for(unsigned int i = 0; i < N; i++)
	{
		r += c[i] * pv.c[i];
	}

	return r;
}

template <typename T, unsigned int N>
PVector<T, N> PVectorBase<T, N>::operator+(const PVector<T, N>& pv) const
{
	PVector<T, N> r;

	for(unsigned int i = 0; i < N; i++)
	{
		r.c[i] = c[i] + pv.c[i];
	}

	return r;
}
template <typename T, unsigned int N>
PVector<T, N> PVectorBase<T, N>::operator-(const PVector<T, N>& pv) const
{
	PVector<T, N> r;

	for(unsigned int i = 0; i < N; i++)
	{
		r.c[i] = c[i] - pv.c[i];
	}

	return r;
}

template <typename T, unsigned int N>
double PVectorBase<T, N>::mag() const
{
	double mag = 0;

	for(unsigned int i = 0; i < N; i++)
	{
		mag += c[i] * c[i];
	}

	return sqrt(mag);
};

													//--
													//--
													//-- Now Entering: Specialization Land!
													//--
													//--

template <typename T, unsigned int N>
class PVector : public PVectorBase<T, N> 
{
	public:
		PVector();
};

template <typename T, unsigned int N>
PVector<T, N>::PVector() 
{

}

template <typename T>
class PVector<T, 2> : public PVectorBase<T, 2>
{
	public:
		PVector();
		PVector(const sf::Vector2<T>& sfv);
		sf::Vector2<T> toVector2() const;

		void setMagAngle(double m, double a); // Angle from positive x-axis, radians
		double angle();
};

template <typename T>
PVector<T, 2>::PVector()
{

}
template <typename T>
PVector<T, 2>::PVector(const sf::Vector2<T>& sfv)
{
	c[0] = sfv.x;
	c[1] = sfv.y;
}
template <typename T>
sf::Vector2<T> PVector<T, 2>::toVector2() const
{
	sf::Vector2<T> sfv;

	sfv.x = c[0];
	sfv.y = c[1];

	return sfv;
}

template <typename T>
void PVector<T, 2>::setMagAngle(double m, double a)
{
	c[0] = m * cos(a);
	c[1] = m * sin(a);
}
template <typename T>
double PVector<T, 2>::angle()
{
	return atan2(c[1], c[0]);
}
