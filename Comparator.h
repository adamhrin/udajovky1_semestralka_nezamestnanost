#pragma once

template <typename T>
class Comparator
{
public:
	Comparator();
	virtual ~Comparator();
	virtual bool compare(T o1, T o2) = 0;
};

template <typename T>
Comparator<T>::Comparator()
{
}

template <typename T>
Comparator<T>::~Comparator()
{
}
