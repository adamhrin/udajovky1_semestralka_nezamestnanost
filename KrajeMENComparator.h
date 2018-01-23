#pragma once
#include "Comparator.h"
#include "Kraj.h"
#include <iostream>

class KrajeMENComparator : public Comparator<Kraj*>
{
public:
	KrajeMENComparator(int rok, std::string sposob);
	~KrajeMENComparator();
	bool compare(Kraj* o1, Kraj* o2) override;
private:
	int rok_;
	std::string sposob_;
};

