#pragma once
#include "Comparator.h"
#include "Kraj.h"
#include <iostream>

class KrajeDPUComparator : public Comparator<Kraj*>
{
public:
	KrajeDPUComparator(int rok, std::string sposob);
	~KrajeDPUComparator();
	bool compare(Kraj* o1, Kraj* o2) override;
private:
	int rok_;
	std::string sposob_;
};

