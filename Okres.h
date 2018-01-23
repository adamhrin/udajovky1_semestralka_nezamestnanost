#pragma once
#include <string>
#include "structures\array\array.h"
#include "structures\heap_monitor.h"
#include "OkresVRoku.h"

using namespace structures;

class Okres
{
public:
	Okres(std::string nazov);
	~Okres();
	void pridajOkresVRoku(int rok, int zpUchadzaci, int absolventi, int mladistvi, int dlhodobi);
	std::string getNazov();
	void zobrazStatistikyOUchadzacoch(int rokOd, int rokDo);
	void pridajMENvRoku(int rok, double spoluMEN, double muziMEN, double zenyMEN);
	void pridajEAOvRoku(int rok, int spoluEAO, int muziEAO, int zenyEAO);
	void pridajDPUvRoku(int rok, int spoluDPU, int muziDPU, int zenyDPU);
	double getMieraEvidovanejNezamestnanostiSpoluVRoku(int rok);
	int getDisponibilnyPocetUchadzacovSpoluVRoku(int rok);
	int getPriemernyPocetEAOSpoluVRozpati(int rokOd, int rokDo);
	double getPoklesMENmuziVRozpati(int rokOd, int rokDo);
	double getPoklesMENzenyVRozpati(int rokOd, int rokDo);
	double getPercentoAbsolventiVDPUVRozpati(int rokOd, int rokDo);
	int getZPUchadzaciVRoku(int rok);
	int getAbsolventiVRoku(int rok);
	int getMladistviVRoku(int rok);
	int getDlhodobiVRoku(int rok);
	int getEkonomickyAktivneObyvatelstvoVRoku(int rok);
	int getDisponibilnyPocetUchadzacovMuziVRoku(int rok);
	int getEkonomickyAktivneObyvatelstvoMuziVRoku(int rok);
	int getDisponibilnyPocetUchadzacovZenyVRoku(int rok);
	int getEkonomickyAktivneObyvatelstvoZenyVRoku(int rok);

private:
	std::string nazov_;
	Array<OkresVRoku*>* roky_;
	const int POSUN_INDEXU_PRE_ROKY = 2001;
};

