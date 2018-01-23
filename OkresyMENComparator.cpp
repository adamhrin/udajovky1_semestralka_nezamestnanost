#include "OkresyMENComparator.h"
#include "Okres.h"
#include "Comparator.h"
#include <iostream>
#include <string>

OkresyMENComparator::OkresyMENComparator(int rok, std::string sposob)
	: Comparator<Okres*>(),
	rok_(rok),
	sposob_(sposob)
{
}

OkresyMENComparator::~OkresyMENComparator()
{
}

bool OkresyMENComparator::compare(Okres* o1, Okres* o2)
{
	if (sposob_ == "v")
	{
		return o1->getMieraEvidovanejNezamestnanostiSpoluVRoku(rok_) > o2->getMieraEvidovanejNezamestnanostiSpoluVRoku(rok_);
	}
	return o1->getMieraEvidovanejNezamestnanostiSpoluVRoku(rok_) < o2->getMieraEvidovanejNezamestnanostiSpoluVRoku(rok_);
}


