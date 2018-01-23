#pragma once
#include "structures\heap_monitor.h"
#include "structures\table\sorted_sequence_table.h"
#include "structures\table\unsorted_sequence_table.h"
#include "Okres.h"
#include <string>
#include "Kraj.h"

using namespace structures;

class HlavnaTrieda
{
public:
	HlavnaTrieda();
	~HlavnaTrieda();
	void zacni();
	void nacitajZoSuboru();
	void bod1();
	void bod2();
	void bod3();
	void bod4();
	void bod5();
	void bod6();

private:
	SortedSequenceTable<std::string, Okres*>* okresyZoradene_;
	UnsortedSequenceTable<std::string, Okres*>* okresyNezoradene_;

	SortedSequenceTable<std::string, Kraj*>* krajeZoradene_;
	UnsortedSequenceTable<std::string, Kraj*>* krajeNezoradene_;
};

