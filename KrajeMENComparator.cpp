#include "KrajeMENComparator.h"
#include "Kraj.h"
#include "Comparator.h"
#include <iostream>
#include <string>


KrajeMENComparator::KrajeMENComparator(int rok, std::string sposob)
	: Comparator<Kraj*>(),
	rok_(rok),
	sposob_(sposob)
{
}

KrajeMENComparator::~KrajeMENComparator()
{
}

bool KrajeMENComparator::compare(Kraj* k1, Kraj* k2)
{
	if (sposob_ == "v")
	{
		return k1->getMieraEvidovanejNezamestnanostiSpoluVRoku(rok_) > k2->getMieraEvidovanejNezamestnanostiSpoluVRoku(rok_);
	}
	return k1->getMieraEvidovanejNezamestnanostiSpoluVRoku(rok_) < k2->getMieraEvidovanejNezamestnanostiSpoluVRoku(rok_);
}
