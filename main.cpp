// main.cpp : Defines the entry point for the console application.
//
#include "structures\heap_monitor.h"
#include <iostream>
#include "structures\list\array_list.h"
#include "structures\vector\vector.h"
#include "HlavnaTrieda.h"

using namespace structures;

int main()
{
	initHeapMonitor();
	HlavnaTrieda* hlavnaTrieda = new HlavnaTrieda();
	hlavnaTrieda->zacni();
	delete hlavnaTrieda;
	return 0;
}
