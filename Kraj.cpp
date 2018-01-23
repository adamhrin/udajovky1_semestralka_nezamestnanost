#include "Kraj.h"
#include <string>
#include "Okres.h"
#include <iostream>


Kraj::Kraj(std::string nazov)
{
	nazov_ = nazov;
	okresy_ = new ArrayList<Okres*>();
}

Kraj::~Kraj()
{
	delete okresy_;
	okresy_ = nullptr;
}

void Kraj::pridajOkres(Okres & okres)
{
	okresy_->add(&okres);
}

std::string Kraj::getNazov()
{
	return nazov_;
}

void Kraj::zobrazSumarneStatistikyOUchadzacoch(int rokOd, int rokDo)
{
	int zpUchadzaciSumarneSpolu = 0;
	int absolventiSumarneSpolu = 0;
	int mladistviSumarneSpolu = 0;
	int dlhodobiSumarneSpolu = 0;

	for (int i = (rokOd - POSUN_INDEXU_PRE_ROKY); i < (rokDo - POSUN_INDEXU_PRE_ROKY + 1); i++)
	{
		std::cout << "\n---------------------------------------------------\n";
		std::cout << "Rok " << (i + POSUN_INDEXU_PRE_ROKY) << std::endl;
		int momentalniZpUchadzaciSumarne = 0;
		int momentalniAbsolventiSumarne = 0;
		int momentalniMladistviSumarne = 0;
		int momentalniDlhodobiSumarne = 0;

		for each (auto okres in *okresy_)
		{
			momentalniZpUchadzaciSumarne += okres->getZPUchadzaciVRoku(i + POSUN_INDEXU_PRE_ROKY);
			momentalniAbsolventiSumarne += okres->getAbsolventiVRoku(i + POSUN_INDEXU_PRE_ROKY);
			momentalniMladistviSumarne += okres->getMladistviVRoku(i + POSUN_INDEXU_PRE_ROKY);
			momentalniDlhodobiSumarne += okres->getDlhodobiVRoku(i + POSUN_INDEXU_PRE_ROKY);
		}

		std::cout << "Pocet uchadzacov o zamestnanie so ZP SUMARNE: " << momentalniZpUchadzaciSumarne << std::endl;
		zpUchadzaciSumarneSpolu += momentalniZpUchadzaciSumarne;

		std::cout << "Pocet uchadzacov o zamestnanie - absolventi SUMARNE: " << momentalniAbsolventiSumarne << std::endl;
		absolventiSumarneSpolu += momentalniAbsolventiSumarne;

		std::cout << "Pocet uchadzacov o zamestnanie - mladistvi SUMARNE: " << momentalniMladistviSumarne << std::endl;
		mladistviSumarneSpolu += momentalniMladistviSumarne;

		std::cout << "Pocet dlhodobo evidovavych uchadzacov o zamestnanie SUMARNE: " << momentalniDlhodobiSumarne << std::endl;
		dlhodobiSumarneSpolu += momentalniDlhodobiSumarne;
	}
	std::cout << "\n---------------------------------------------------\n";
	std::cout << "SPOLU:\n";
	std::cout << "Pocet uchadzacov o zamestnanie so ZP SUMARNE: " << zpUchadzaciSumarneSpolu << std::endl;
	std::cout << "Pocet uchadzacov o zamestnanie - absolventi SUMARNE: " << absolventiSumarneSpolu << std::endl;
	std::cout << "Pocet uchadzacov o zamestnanie - mladistvi SUMARNE: " << mladistviSumarneSpolu << std::endl;
	std::cout << "Pocet dlhodobo evidovavych uchadzacov o zamestnanie SUMARNE: " << dlhodobiSumarneSpolu << std::endl;
}

double Kraj::getMieraEvidovanejNezamestnanostiSpoluVRoku(int rok)
{
	return ((double)getDisponibilnyPocetUchadzacovSpoluVRoku(rok) / (double)getEAOvRoku(rok)) * 100;
}

double Kraj::getMieraEvidovanejNezamestnanostiMuziVRoku(int rok)
{
	return ((double)getDPUvRokuMuzi(rok) / (double)getEAOvRokuMuzi(rok)) * 100;
}

double Kraj::getMieraEvidovanejNezamestnanostiZenyVRoku(int rok)
{
	return ((double)getDPUvRokuZeny(rok) / (double)getEAOvRokuZeny(rok)) * 100;
}

int Kraj::getDisponibilnyPocetUchadzacovSpoluVRoku(int rok)
{
	int vysledok = 0;
	for each (auto okres in *okresy_)
	{
		vysledok += okres->getDisponibilnyPocetUchadzacovSpoluVRoku(rok);
	}
	return vysledok;
}

int Kraj::getAbsolventiVRoku(int rok)
{
	int vysledok = 0;
	for each (auto okres in *okresy_)
	{
		vysledok += okres->getAbsolventiVRoku(rok);
	}
	return vysledok;
}

int Kraj::getEAOvRoku(int rok)
{
	int vysledok = 0;
	for each (auto okres in *okresy_)
	{
		vysledok += okres->getEkonomickyAktivneObyvatelstvoVRoku(rok);
	}
	return vysledok;
}

int Kraj::getPriemernyPocetEAOSpoluVRozpati(int rokOd, int rokDo)
{
	int pocetRokov = rokDo - rokOd + 1;
	int celkovyPocet = 0;
	for (int i = (rokOd - POSUN_INDEXU_PRE_ROKY); i < (rokDo - POSUN_INDEXU_PRE_ROKY + 1); i++)
	{
		celkovyPocet += getEAOvRoku(i + POSUN_INDEXU_PRE_ROKY);
	}
	return (celkovyPocet / pocetRokov);
}

double Kraj::getPoklesMENmuziVRozpati(int rokOd, int rokDo)
{
	return getMieraEvidovanejNezamestnanostiMuziVRoku(rokOd) - getMieraEvidovanejNezamestnanostiMuziVRoku(rokDo);
}

double Kraj::getPoklesMENzenyVRozpati(int rokOd, int rokDo)
{
	return getMieraEvidovanejNezamestnanostiZenyVRoku(rokOd) - getMieraEvidovanejNezamestnanostiZenyVRoku(rokDo);
}

double Kraj::getPercentoAbsolventiVDPUVRozpati(int rokOd, int rokDo)
{
	int pocetRokov = rokDo - rokOd + 1;
	double celkovePercento = 0;
	for (int i = (rokOd - POSUN_INDEXU_PRE_ROKY); i < (rokDo - POSUN_INDEXU_PRE_ROKY + 1); i++)
	{
		celkovePercento += (double)getAbsolventiVRoku(i + POSUN_INDEXU_PRE_ROKY) / (double)getDisponibilnyPocetUchadzacovSpoluVRoku(i + POSUN_INDEXU_PRE_ROKY);
	}
	return (celkovePercento / pocetRokov) * 100;
}

int Kraj::getDPUvRokuMuzi(int rok)
{
	int vysledok = 0;
	for each (auto okres in *okresy_)
	{
		vysledok += okres->getDisponibilnyPocetUchadzacovMuziVRoku(rok);
	}
	return vysledok;
}

int Kraj::getEAOvRokuMuzi(int rok)
{
	int vysledok = 0;
	for each (auto okres in *okresy_)
	{
		vysledok += okres->getEkonomickyAktivneObyvatelstvoMuziVRoku(rok);
	}
	return vysledok;
}

int Kraj::getDPUvRokuZeny(int rok)
{
	int vysledok = 0;
	for each (auto okres in *okresy_)
	{
		vysledok += okres->getDisponibilnyPocetUchadzacovZenyVRoku(rok);
	}
	return vysledok;
}

int Kraj::getEAOvRokuZeny(int rok)
{
	int vysledok = 0;
	for each (auto okres in *okresy_)
	{
		vysledok += okres->getEkonomickyAktivneObyvatelstvoZenyVRoku(rok);
	}
	return vysledok;
}
