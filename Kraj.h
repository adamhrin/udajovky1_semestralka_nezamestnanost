#pragma once
#include <string>
#include "structures\list\array_list.h"
#include "Okres.h"

using namespace structures;

class Kraj
{
public:
	Kraj(std::string nazov);
	~Kraj();
	void pridajOkres(Okres & okres);
	std::string getNazov();
	void zobrazSumarneStatistikyOUchadzacoch(int rokOd, int rokDo);
	double getMieraEvidovanejNezamestnanostiSpoluVRoku(int rok);
	double getMieraEvidovanejNezamestnanostiMuziVRoku(int rok);
	double getMieraEvidovanejNezamestnanostiZenyVRoku(int rok);
	int getDisponibilnyPocetUchadzacovSpoluVRoku(int rok);
	int getAbsolventiVRoku(int rok);
	int getEAOvRoku(int rok);
	int getPriemernyPocetEAOSpoluVRozpati(int rokOd, int rokDo);
	double getPoklesMENmuziVRozpati(int rokOd, int rokDo);
	double getPoklesMENzenyVRozpati(int rokOd, int rokDo);
	double getPercentoAbsolventiVDPUVRozpati(int rokOd, int rokDo);
	int getDPUvRokuMuzi(int rok);
	int getEAOvRokuMuzi(int rok);
	int getDPUvRokuZeny(int rok);
	int getEAOvRokuZeny(int rok);


private:
	std::string nazov_;
	ArrayList<Okres*>* okresy_;
	const int POSUN_INDEXU_PRE_ROKY = 2001;
};

