#pragma once
#include "Comparator.h"
#include "Okres.h"
#include <iostream>

class OkresyMENComparator : public Comparator<Okres*>
{
public:
	OkresyMENComparator(int rok, std::string sposob);
	~OkresyMENComparator();
	bool compare(Okres* o1, Okres* o2) override;
private:
	int rok_;
	std::string sposob_;
};

