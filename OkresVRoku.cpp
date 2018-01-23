#include "OkresVRoku.h"
#include "structures\heap_monitor.h"



OkresVRoku::OkresVRoku(int rok)
{
	rok_ = rok;
	zpUchadzaci_ = 0;
	absolventiUchadzaci_ = 0;
	mladistviUchadzaci_ = 0;
	dlhodoboEvidovaniUchadzaci_ = 0;
}


OkresVRoku::~OkresVRoku()
{
}

int OkresVRoku::getZPUchadzaci()
{
	return zpUchadzaci_;
}

int OkresVRoku::getAbsolventiUchadzaci()
{
	return absolventiUchadzaci_;
}

int OkresVRoku::getMladistviUchadzaci()
{
	return mladistviUchadzaci_;
}

int OkresVRoku::getDlhodoboEvidovaniUchadzaci()
{
	return dlhodoboEvidovaniUchadzaci_;
}

void OkresVRoku::setZPUchadzaci(int cislo)
{
	zpUchadzaci_ = cislo;
}

void OkresVRoku::setAbsolventiUchadzaci(int cislo)
{
	absolventiUchadzaci_ = cislo;
}

void OkresVRoku::setMladistviUchadzaci(int cislo)
{
	mladistviUchadzaci_ = cislo;
}

void OkresVRoku::setDlhodoboEvidovaniUchadzaci(int cislo)
{
	dlhodoboEvidovaniUchadzaci_ = cislo;
}

double OkresVRoku::getSpoluMEN()
{
	return spoluMEN_;
}

double OkresVRoku::getMuziMEN()
{
	return muziMEN_;
}

double OkresVRoku::getZenyMEN()
{
	return zenyMEN_;
}

int OkresVRoku::getSpoluEAO()
{
	return spoluEAO_;
}

int OkresVRoku::getMuziEAO()
{
	return muziEAO_;
}

int OkresVRoku::getZenyEAO()
{
	return zenyEAO_;
}

int OkresVRoku::getSpoluDPU()
{
	return spoluDPU_;
}

int OkresVRoku::getMuziDPU()
{
	return muziDPU_;
}

int OkresVRoku::getZenyDPU()
{
	return zenyDPU_;
}

void OkresVRoku::setSpoluMEN(double cislo)
{
	spoluMEN_ = cislo;
}

void OkresVRoku::setMuziMEN(double cislo)
{
	muziMEN_ = cislo;
}

void OkresVRoku::setZenyMEN(double cislo)
{
	zenyMEN_ = cislo;
}

void OkresVRoku::setSpoluEAO(int cislo)
{
	spoluEAO_ = cislo;
}

void OkresVRoku::setMuziEAO(int cislo)
{
	muziEAO_ = cislo;
}

void OkresVRoku::setZenyEAO(int cislo)
{
	zenyEAO_ = cislo;
}

void OkresVRoku::setSpoluDPU(int cislo)
{
	spoluDPU_ = cislo;
}

void OkresVRoku::setMuziDPU(int cislo)
{
	muziDPU_ = cislo;
}

void OkresVRoku::setZenyDPU(int cislo)
{
	zenyDPU_ = cislo;
}
