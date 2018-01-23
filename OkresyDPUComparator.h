#pragma once
#include "Comparator.h"
#include "Okres.h"
#include <iostream>

class OkresyDPUComparator : public Comparator<Okres*>
{
public:
	OkresyDPUComparator(int rok, std::string sposob);
	~OkresyDPUComparator(); 
	bool compare(Okres* o1, Okres* o2) override;
private:
	int rok_;
	std::string sposob_;
};

