#include "KrajeDPUComparator.h"
#include "Kraj.h"
#include "Comparator.h"
#include <iostream>
#include <string>


KrajeDPUComparator::KrajeDPUComparator(int rok, std::string sposob)
	: Comparator<Kraj*>(),
	rok_(rok),
	sposob_(sposob)
{
}

KrajeDPUComparator::~KrajeDPUComparator()
{
}

bool KrajeDPUComparator::compare(Kraj* k1, Kraj* k2)
{
	if (sposob_ == "v")
	{
		return k1->getDisponibilnyPocetUchadzacovSpoluVRoku(rok_) > k2->getDisponibilnyPocetUchadzacovSpoluVRoku(rok_);
	}
	return k1->getDisponibilnyPocetUchadzacovSpoluVRoku(rok_) < k2->getDisponibilnyPocetUchadzacovSpoluVRoku(rok_);
}
