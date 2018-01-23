#include "structures\heap_monitor.h"
#include "Okres.h"
#include "OkresVRoku.h"
#include <string>
#include <iostream>
#include "structures\array\array.h"

using namespace structures;

Okres::Okres(std::string nazov)
{
	nazov_ = nazov;
	roky_ = new Array<OkresVRoku*>(16); // roky su od 2001 do 2016
}


Okres::~Okres()
{
	for (int i = 0; i < roky_->size(); i++)
	{
		delete (*roky_)[i];
	}
	delete roky_;
	roky_ = nullptr;
}

void Okres::pridajOkresVRoku(int rok, int zpUchadzaci, int absolventi, int mladistvi, int dlhodobi)
{
	OkresVRoku* novyRok = new OkresVRoku(rok);
	novyRok->setZPUchadzaci(zpUchadzaci);
	novyRok->setAbsolventiUchadzaci(absolventi);
	novyRok->setMladistviUchadzaci(mladistvi);
	novyRok->setDlhodoboEvidovaniUchadzaci(dlhodobi);
	(*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)] = novyRok;
}

std::string Okres::getNazov()
{
	return nazov_;
}

void Okres::zobrazStatistikyOUchadzacoch(int rokOd, int rokDo)
{
	int zpUchadzaciSpolu = 0;
	int absolventiSpolu = 0;
	int mladistviSpolu = 0;
	int dlhodobiSpolu = 0;

	for (int i = (rokOd - POSUN_INDEXU_PRE_ROKY); i < (rokDo - POSUN_INDEXU_PRE_ROKY + 1); i++)
	{
		std::cout << "\n---------------------------------------------------\n";
		std::cout << "Rok " << (i + POSUN_INDEXU_PRE_ROKY) << std::endl;
		int momentalniZpUchadzaci = (*roky_)[i]->getZPUchadzaci();
		int momentalniAbsolventi = (*roky_)[i]->getAbsolventiUchadzaci();
		int momentalniMladistvi = (*roky_)[i]->getMladistviUchadzaci();
		int momentalniDlhodobi = (*roky_)[i]->getDlhodoboEvidovaniUchadzaci();

		std::cout << "Pocet uchadzacov o zamestnanie so ZP: " << momentalniZpUchadzaci << std::endl;
		zpUchadzaciSpolu += momentalniZpUchadzaci;

		std::cout << "Pocet uchadzacov o zamestnanie - absolventi: " << momentalniAbsolventi << std::endl;
		absolventiSpolu += momentalniAbsolventi;

		std::cout << "Pocet uchadzacov o zamestnanie - mladistvi: " << momentalniMladistvi << std::endl;
		mladistviSpolu += momentalniMladistvi;

		std::cout << "Pocet dlhodobo evidovavych uchadzacov o zamestnanie: " << momentalniDlhodobi << std::endl;
		dlhodobiSpolu += momentalniDlhodobi;
	}
	std::cout << "\n---------------------------------------------------\n";
	std::cout << "SPOLU:\n";
	std::cout << "Pocet uchadzacov o zamestnanie so ZP: " << zpUchadzaciSpolu << std::endl;
	std::cout << "Pocet uchadzacov o zamestnanie - absolventi: " << absolventiSpolu << std::endl;
	std::cout << "Pocet uchadzacov o zamestnanie - mladistvi: " << mladistviSpolu << std::endl;
	std::cout << "Pocet dlhodobo evidovavych uchadzacov o zamestnanie: " << dlhodobiSpolu << std::endl;
}

void Okres::pridajMENvRoku(int rok, double spoluMEN, double muziMEN, double zenyMEN)
{
	OkresVRoku* okresVRoku = (*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)];
	okresVRoku->setSpoluMEN(spoluMEN);
	okresVRoku->setMuziMEN(muziMEN);
	okresVRoku->setZenyMEN(zenyMEN);
}

void Okres::pridajEAOvRoku(int rok, int spoluEAO, int muziEAO, int zenyEAO)
{
	OkresVRoku* okresVRoku = (*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)];
	okresVRoku->setSpoluEAO(spoluEAO);
	okresVRoku->setMuziEAO(muziEAO);
	okresVRoku->setZenyEAO(zenyEAO);
}

void Okres::pridajDPUvRoku(int rok, int spoluDPU, int muziDPU, int zenyDPU)
{
	OkresVRoku* okresVRoku = (*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)];
	okresVRoku->setSpoluDPU(spoluDPU);
	okresVRoku->setMuziDPU(muziDPU);
	okresVRoku->setZenyDPU(zenyDPU);
}

double Okres::getMieraEvidovanejNezamestnanostiSpoluVRoku(int rok)
{
	OkresVRoku* okresVRoku = (*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)];
	return okresVRoku->getSpoluMEN();
}

int Okres::getDisponibilnyPocetUchadzacovSpoluVRoku(int rok)
{
	OkresVRoku* okresVRoku = (*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)];
	return okresVRoku->getSpoluDPU();
}

int Okres::getPriemernyPocetEAOSpoluVRozpati(int rokOd, int rokDo)
{
	int pocetRokov = rokDo - rokOd + 1;
	int celkovyPocet = 0;
	for (int i = (rokOd - POSUN_INDEXU_PRE_ROKY); i < (rokDo - POSUN_INDEXU_PRE_ROKY + 1); i++)
	{
		celkovyPocet += (*roky_)[i]->getSpoluEAO();
	}
	return (celkovyPocet / pocetRokov);
}

double Okres::getPoklesMENmuziVRozpati(int rokOd, int rokDo)
{
	return (*roky_)[(rokOd - POSUN_INDEXU_PRE_ROKY)]->getMuziMEN() - (*roky_)[(rokDo - POSUN_INDEXU_PRE_ROKY)]->getMuziMEN();
}

double Okres::getPoklesMENzenyVRozpati(int rokOd, int rokDo)
{
	return (*roky_)[(rokOd - POSUN_INDEXU_PRE_ROKY)]->getZenyMEN() - (*roky_)[(rokDo - POSUN_INDEXU_PRE_ROKY)]->getZenyMEN();
}

double Okres::getPercentoAbsolventiVDPUVRozpati(int rokOd, int rokDo)
{
	int pocetRokov = rokDo - rokOd + 1;
	double celkovePercento = 0;
	for (int i = (rokOd - POSUN_INDEXU_PRE_ROKY); i < (rokDo - POSUN_INDEXU_PRE_ROKY + 1); i++)
	{
		celkovePercento += (double)(*roky_)[i]->getAbsolventiUchadzaci() / (double)(*roky_)[i]->getSpoluDPU();
	}
	return (celkovePercento / pocetRokov) * 100;
}

int Okres::getZPUchadzaciVRoku(int rok)
{
	return (*roky_)[rok - POSUN_INDEXU_PRE_ROKY]->getZPUchadzaci();
}

int Okres::getAbsolventiVRoku(int rok)
{
	return (*roky_)[rok - POSUN_INDEXU_PRE_ROKY]->getAbsolventiUchadzaci();
}

int Okres::getMladistviVRoku(int rok)
{
	return (*roky_)[rok - POSUN_INDEXU_PRE_ROKY]->getMladistviUchadzaci();
}

int Okres::getDlhodobiVRoku(int rok)
{
	return (*roky_)[rok - POSUN_INDEXU_PRE_ROKY]->getDlhodoboEvidovaniUchadzaci();
}

int Okres::getEkonomickyAktivneObyvatelstvoVRoku(int rok)
{
	OkresVRoku* okresVRoku = (*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)];
	return okresVRoku->getSpoluEAO();
}

int Okres::getDisponibilnyPocetUchadzacovMuziVRoku(int rok)
{
	OkresVRoku* okresVRoku = (*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)];
	return okresVRoku->getMuziDPU();
}

int Okres::getEkonomickyAktivneObyvatelstvoMuziVRoku(int rok)
{
	OkresVRoku* okresVRoku = (*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)];
	return okresVRoku->getMuziEAO();
}

int Okres::getDisponibilnyPocetUchadzacovZenyVRoku(int rok)
{
	OkresVRoku* okresVRoku = (*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)];
	return okresVRoku->getZenyDPU();
}

int Okres::getEkonomickyAktivneObyvatelstvoZenyVRoku(int rok)
{
	OkresVRoku* okresVRoku = (*roky_)[(rok - POSUN_INDEXU_PRE_ROKY)];
	return okresVRoku->getZenyEAO();
}



