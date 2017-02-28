#pragma once

#include <array>

template <typename T, unsigned int N> // Type, dimensions 
class PVector
{
	public:
		PVector();
		PVector(std::array<T, N> c);
		PVector(const PVector<T, N>& pv);

		~PVector();

		PVector<T, N>& operator=(const PVector<T, N>& pv);
		bool operator==(const PVector<T, N>& pv) const;

		PVector<T, N> operator*(const double& s) const;
		double dot(const PVector<T, N>& pv) const;

		PVector<T, N> operator+(const PVector<T, N>& pv) const;
		PVector<T, N> operator-(const PVector<T, N>& pv) const;

		PVector<T, N>& mag() const;

		std::array<T, N> c; // Components
};

template <typename T, unsigned int N>
PVector<T, N>::PVector()
{

}
template <typename T, unsigned int N>
PVector<T, N>::PVector(std::array<T, N> c)
{
	this->c = c;
}
template <typename T, unsigned int N>
PVector<T, N>::PVector(const PVector<T, N>& pv)
{
	c = pv.c;
}

template <typename T, unsigned int N>
PVector<T, N>::~PVector() {};

template <typename T, unsigned int N>
PVector<T, N>& PVector<T, N>::operator=(const PVector<T, N>& pv)
{
	c = pv.c;

	return *this;
};
template <typename T, unsigned int N>
bool PVector<T, N>::operator==(const PVector<T, N>& pv) const
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
PVector<T, N> PVector<T, N>::operator*(const double& s) const
{
	PVector<T, N> r;

	std::memcpy(r.c, c, sizeof(c));
	for(unsigned int i = 0; i < N; i++)
	{
		r.c[i] *= s;
	}

	return r;
};
template <typename T, unsigned int N>
double PVector<T, N>::dot(const PVector<T, N>& pv) const
{
	double r;

	for(unsigned int i = 0; i < N; i++)
	{
		r = c[i] * pv[i];
	}

	return r;
}

template <typename T, unsigned int N>
PVector<T, N> PVector<T, N>::operator+(const PVector<T, N>& pv) const
{
	PVector<T, N> r;

	std::memcpy(r.c, c, sizeof(c));
	for(unsigned int i = 0; i < N; i++)
	{
		r.c[i] += pv.c[i];
	}
}
template <typename T, unsigned int N>
PVector<T, N> PVector<T, N>::operator-(const PVector<T, N>& pv) const
{
	PVector<T, N> r;

	std::memcpy(r.c, c, sizeof(c));
	for(unsigned int i = 0; i < N; i++)
	{
		r.c[i] -= pv.c[i];
	}
}

template <typename T, unsigned int N>
PVector<T, N>& PVector<T, N>::mag() const
{
	double mag = 0;

	for(unsigned int i = 0; i < N; i++)
	{
		mag += c[i] * c[i];
	}

	return sqrt(mag);
};