#include "OkresyDPUComparator.h"
#include "Okres.h"
#include "Comparator.h"
#include <iostream>
#include <string>


OkresyDPUComparator::OkresyDPUComparator(int rok, std::string sposob)
	: Comparator<Okres*>(),
	rok_(rok),
	sposob_(sposob)
{
}

OkresyDPUComparator::~OkresyDPUComparator()
{
}

bool OkresyDPUComparator::compare(Okres* o1, Okres* o2)
{
	if (sposob_ == "v")
	{
		return o1->getDisponibilnyPocetUchadzacovSpoluVRoku(rok_) > o2->getDisponibilnyPocetUchadzacovSpoluVRoku(rok_);
	}
	return o1->getDisponibilnyPocetUchadzacovSpoluVRoku(rok_) < o2->getDisponibilnyPocetUchadzacovSpoluVRoku(rok_);
}
