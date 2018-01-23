#include "structures\heap_monitor.h"
#include "HlavnaTrieda.h"
#include "Okres.h"
#include <iostream>
#include <fstream>
#include <string>
#include "structures\table\unsorted_sequence_table.h"
#include "structures\table\sorting\heap_sort.h"
#include <iomanip> 
#include "KrajeDPUComparator.h"
#include "KrajeMENComparator.h"
#include "OkresyDPUComparator.h"
#include "OkresyMENComparator.h"
#include "Comparator.h"

HlavnaTrieda::HlavnaTrieda()
{
	okresyZoradene_ = new SortedSequenceTable<std::string, Okres*>();
	okresyNezoradene_ = new UnsortedSequenceTable<std::string, Okres*>();

	krajeZoradene_ = new SortedSequenceTable<std::string, Kraj*>();
	krajeNezoradene_ = new UnsortedSequenceTable<std::string, Kraj*>();
}


HlavnaTrieda::~HlavnaTrieda()
{
	for each (auto tableItem in *okresyZoradene_)
	{
		delete tableItem->accessData();
	}
	delete okresyZoradene_;
	okresyZoradene_ = nullptr;

	delete okresyNezoradene_;
	okresyNezoradene_ = nullptr;

	for each (auto tableItem in *krajeZoradene_)
	{
		delete tableItem->accessData();
	}
	delete krajeZoradene_;
	krajeZoradene_ = nullptr;

	delete krajeNezoradene_;
	krajeNezoradene_ = nullptr;
}

void HlavnaTrieda::zacni()
{
	std::cout << std::endl;
	std::cout << "********************************************************\n";
	std::cout << "> Dobry den, vitajte v systeme evidencie nezamestnanosti\n";
	std::cout << "********************************************************\n";
	std::cout << std::endl;
	nacitajZoSuboru();
	while (1)
	{
		std::cout << "\n> Stlacte tlacidlo\n";
		int volba = 0;
		std::cin >> volba;
		
		switch (volba)
		{
			/// tlacidlo 1 
		case 1:
		{
			bod1();
			break;
		}
		/// tlacidlo 2 
		case 2:
		{
			bod2();
			break;
		}

		/// tlacidlo 3 
		case 3:
		{
			bod3();
			break;
		}

		/// tlacidlo 4 
		case 4:
		{
			bod4();
			break;
		}

		/// tlacidlo 5
		case 5:
		{
			bod5();
			break;
		}

		/// tlacidlo 6
		case 6:
		{
			bod6();
			break;
		}
		/// tlacidlo 7
		case 7:
		{

			break;
		}
		/// tlacidlo 10 ukonci program
		case 10:
			return;

		default:
			std::cout << "Not implemented yet!\n";
		}
	}
}

void HlavnaTrieda::nacitajZoSuboru()
{
	char oddelovac(';');
	std::ifstream suborUchadzaci("UchadzaciOZamestnanie.txt");

	if (suborUchadzaci.is_open())
	{
		while (!suborUchadzaci.eof())
		{
			std::string nazovOkresu;
			std::getline(suborUchadzaci, nazovOkresu, oddelovac);
			nazovOkresu = nazovOkresu.substr(6);
			Okres* okres = new Okres(nazovOkresu);
			for (int i = 0; i < 16; i++)
			{
				std::string zpUchadzaci, absolventi, mladistvi, dlhodobi;
				std::getline(suborUchadzaci, zpUchadzaci, oddelovac);
				std::getline(suborUchadzaci, absolventi, oddelovac);
				std::getline(suborUchadzaci, mladistvi, oddelovac);
				if (i == 15)
				{
					std::getline(suborUchadzaci, dlhodobi);
				}
				else
				{
					std::getline(suborUchadzaci, dlhodobi, oddelovac);
				}
				okres->pridajOkresVRoku(2001 + i, stoi(zpUchadzaci), stoi(absolventi), stoi(mladistvi), stoi(dlhodobi));
			}
			okresyZoradene_->insert(okres->getNazov(), okres); //O(n)
			okresyNezoradene_->insert(okres->getNazov(), okres); //O(1)
		}

		std::cout << "Uchadzaci o zamestnanie nacitani zo suboru\n";
		suborUchadzaci.close();
	}
	else
	{
		std::cout << "Subor UchadzaciOZamestnanie.txt sa nepodarilo otvorit\n";
	}


	// ------------------------------------------------------------------------------
	// subor MieraEvidovanejNezamestnanosti.txt
	// ------------------------------------------------------------------------------


	std::ifstream suborMieraNezamestnanosti("MieraEvidovanejNezamestnanosti.txt");
	if (suborMieraNezamestnanosti.is_open())
	{
		while (!suborMieraNezamestnanosti.eof())
		{
			std::string spoluMEN, muziMEN, zenyMEN, spoluEAO, muziEAO, zenyEAO, spoluDPU, muziDPU, zenyDPU;
			std::string nazovOkresu;
			std::getline(suborMieraNezamestnanosti, nazovOkresu, oddelovac);
			nazovOkresu = nazovOkresu.substr(6);
			Okres* vybranyOkres;
			if (!okresyZoradene_->tryFind(nazovOkresu, vybranyOkres)) // logN
			{
				throw std::logic_error("Pri nacitavani suboru MieraEvidovanejNezamestnanosti.txt sa okres nenasiel!");
			}

			std::string mieraEvidNezam;
			std::getline(suborMieraNezamestnanosti, mieraEvidNezam, oddelovac);
			if (mieraEvidNezam != "Miera evidovanej nezamestnanosti (v %)")
			{
				throw std::logic_error("Pri nacitavani suboru MieraEvidovanejNezamestnanosti.txt sa vyskytla chyba pri riadku 'miera evidovanej nezamestnanosti!'");
			}
			for (int i = 0; i < 16; i++)
			{
				std::getline(suborMieraNezamestnanosti, spoluMEN, oddelovac);
				std::getline(suborMieraNezamestnanosti, muziMEN, oddelovac);
				std::getline(suborMieraNezamestnanosti, zenyMEN, oddelovac);
				vybranyOkres->pridajMENvRoku(2001 + i, stod(spoluMEN), stod(muziMEN), stod(zenyMEN));
			}

			std::string EkonomAktObyv;
			std::getline(suborMieraNezamestnanosti, EkonomAktObyv, oddelovac);
			if (EkonomAktObyv != "Ekonomicky aktivne obyvatelstvo")
			{
				throw std::logic_error("Pri nacitavani suboru MieraEvidovanejNezamestnanosti.txt sa vyskytla chyba pri riadku 'ekonomicky aktivne obyvatelstvo'");
			}
			for (int i = 0; i < 16; i++)
			{
				std::getline(suborMieraNezamestnanosti, spoluEAO, oddelovac);
				std::getline(suborMieraNezamestnanosti, muziEAO, oddelovac);
				std::getline(suborMieraNezamestnanosti, zenyEAO, oddelovac);
				vybranyOkres->pridajEAOvRoku(2001 + i, stoi(spoluEAO), stoi(muziEAO), stoi(zenyEAO));
			}

			std::string DisponPocUch;
			std::getline(suborMieraNezamestnanosti, DisponPocUch, oddelovac);
			if (DisponPocUch != "Disponibilny pocet uchadzacov o zamestnanie")
			{
				throw std::logic_error("Pri nacitavani suboru MieraEvidovanejNezamestnanosti.txt sa vyskytla chyba pri riadku 'disponibilny pocet uchadzacov o zamestnanie'");
			}
			for (int i = 0; i < 16; i++)
			{
				std::getline(suborMieraNezamestnanosti, spoluDPU, oddelovac);
				std::getline(suborMieraNezamestnanosti, muziDPU, oddelovac);
				if (i == 15)
				{
				std::getline(suborMieraNezamestnanosti, zenyDPU);
				}
				else
				{
				std::getline(suborMieraNezamestnanosti, zenyDPU, oddelovac);
				}
				vybranyOkres->pridajDPUvRoku(2001 + i, stoi(spoluDPU), stoi(muziDPU), stoi(zenyDPU));
			}
		}

		std::cout << "Miera evidovanej nezamestnanosti nacitana zo suboru\n";
		suborMieraNezamestnanosti.close();
	}
	else
	{
		std::cout << "Subor MieraEvidovanejNezamestnanosti.txt sa nepodarilo otvorit\n";
	}

	// ------------------------------------------------------------------------------
	// subor Kraje.txt
	// ------------------------------------------------------------------------------

	// m*m*n*logN, n max pocet okresov kraja, m pocet krajov
	std::ifstream suborKraje("Kraje.txt");
	if (suborKraje.is_open())
	{
		while (!suborKraje.eof())
		{
			std::string nazovKraja;
			std::getline(suborKraje, nazovKraja);
			std::string pocetOkresov;
			std::getline(suborKraje, pocetOkresov);
			Kraj* kraj = new Kraj(nazovKraja);
			for (int i = 0; i < stoi(pocetOkresov); i++)
			{
				std::string nazovOkresu;
				std::getline(suborKraje, nazovOkresu);
				Okres* okresKraja;
				if (!okresyZoradene_->tryFind(nazovOkresu, okresKraja)) // logN
				{
					throw std::logic_error("Pri nacitavani suboru Kraje.txt sa okres nenasiel!");
				}
				kraj->pridajOkres(*okresKraja);
			}
			krajeZoradene_->insert(kraj->getNazov(), kraj); // O(m)
			krajeNezoradene_->insert(kraj->getNazov(), kraj); // O(1)
		}
		std::cout << "Kraje nacitane zo suboru\n";
		suborMieraNezamestnanosti.close();
	}
	else
	{
		std::cout << "Subor Kraje.txt sa nepodarilo otvorit\n";
	}
}

void HlavnaTrieda::bod1()
{
	Okres* najdeny;
	std::cout << "\n> Zadajte nazov okresu:\n";
	std::string nazovOkresu;
	std::cin.ignore();
	std::getline(std::cin, nazovOkresu);
	//std::cin >> nazovOkresu;
	if (!okresyZoradene_->tryFind(nazovOkresu, najdeny)) // nenasiel sa okres s danym nazvom
	{
		std::cout << "\n> Nenasiel sa okres s danym nazvom!";
		return;
	}

	std::cout << "\n> Zadajte rozpatie rokov:\n";
	std::cout << "\n> Zadajte pociatocny rok: [2001-2016]\n";
	std::string rokOdStr;
	std::cin >> rokOdStr;
	int rokOd = stoi(rokOdStr);
	if (rokOd < 2001 || rokOd > 2016)
	{
		std::cout << "\n> Pociatocny rok nie je v rozpati 2001-2016!";
		return;
	}
	std::cout << "\n> Zadajte koncovy rok: [2001-2016]\n";
	std::string rokDoStr;
	std::cin >> rokDoStr;
	int rokDo = stoi(rokDoStr);
	if (rokDo < 2001 || rokDo > 2016)
	{
		std::cout << "\n> Koncovy rok nie je v rozpati 2001-2016!";
		return;
	}
	if (rokOd > rokDo)
	{
		std::cout << "\n> 'Rok od' je vacsi ako 'rok do'!";
		return;
	}

	najdeny->zobrazStatistikyOUchadzacoch(rokOd, rokDo);
}

/// zlozitost O(n+n*logN+n) = O(n+n*logN) * 2 (to je to, ze pre plnu funkcnost bodu 2 ho musis zavolat dvakrat, raz ti vypise jeden bod, raz druhy) < O(n^2)

void HlavnaTrieda::bod2()
{
	std::cout << "\n> Zadajte rok:\n";
	std::string rokStr;
	std::cin >> rokStr;
	int rok = stoi(rokStr);
	if (rok < 2001 || rok > 2016)
	{
		std::cout << "\n> Rok nie je v rozpati 2001-2016";
		return;
	}
	std::cout << "\n> Zadajte, ci chcete vypisat" << std::endl;
	std::cout << "   [1] mieru evidovanej nezamestnanosti" << std::endl;
	std::cout << "   [2] disponibilny pocet uchadzacov\n";
	std::string volba;
	std::cin >> volba;

	std::cout << "\n> Zadajte, ci chcete zoradit vzostupne alebo zostupne [v/z]:\n";
	std::string zoraditAko;
	std::cin >> zoraditAko;
	switch (stoi(volba))
	{
	case 1: // vypisujem mieru evidovanej nezamestnanosti
	{
		HeapSort<std::string, Okres*>* triedic = new HeapSort<std::string, Okres*>();
		Comparator<Okres*>* comp;

		if (zoraditAko == "v") // vzostupne
		{
			comp = new OkresyMENComparator(rok, "v");
		}
		else // zostupne
		{
			comp = new OkresyMENComparator(rok, "z");
		}

		triedic->sort(*okresyNezoradene_, *comp); // n*logN

		for each (auto item in *okresyNezoradene_)
		{
			std::cout << std::setw(20) << item->accessData()->getNazov() << " | " << item->accessData()->getMieraEvidovanejNezamestnanostiSpoluVRoku(rok) << "%" << std::endl; //O(n)
		}
		delete triedic;
		delete comp;
		break;
	}
	case 2: // vypisujem disponibilny pocet uchadzacov
	{
		HeapSort<std::string, Okres*>* triedic = new HeapSort<std::string, Okres*>();
		Comparator<Okres*>* comp;

		if (zoraditAko == "v") // vzostupne
		{
			comp = new OkresyDPUComparator(rok, "v");
		}
		else // zostupne
		{
			comp = new OkresyDPUComparator(rok, "z");
		}

		triedic->sort(*okresyNezoradene_, *comp); // n*logN

		for each (auto item in *okresyNezoradene_)
		{
			std::cout << std::setw(20) << item->accessData()->getNazov() << " | " << item->accessData()->getDisponibilnyPocetUchadzacovSpoluVRoku(rok) << std::endl;
		}
		delete triedic;
		delete comp;
		break;
	}
	default:
		break;
	}
	
}

/// zlozitost 3*n
void HlavnaTrieda::bod3()
{
	std::cout << "\n> Zadajte rozpatie rokov:\n";
	std::cout << "\n> Zadajte pociatocny rok: [2001-2016]\n";
	std::string rokOdStr;
	std::cin >> rokOdStr;
	int rokOd = stoi(rokOdStr);
	if (rokOd < 2001 || rokOd > 2016)
	{
		std::cout << "\n> Pociatocny rok nie je v rozpati 2001-2016!";
		return;
	}
	std::cout << "\n> Zadajte koncovy rok: [2001-2016]\n";
	std::string rokDoStr;
	std::cin >> rokDoStr;
	int rokDo = stoi(rokDoStr);
	if (rokDo < 2001 || rokDo > 2016)
	{
		std::cout << "\n> Koncovy rok nie je v rozpati 2001-2016!";
		return;
	}
	if (rokOd > rokDo)
	{
		std::cout << "\n> 'Rok od' je vacsi ako 'rok do'!";
		return;
	}

	//------------------------------------------------------------
	// max a min priemerny pocet ekonomicky aktivneho obyvatelstva
	//------------------------------------------------------------

	int maxPriemernyPocetEAO = 0;
	int minPriemernyPocetEAO = INT_MAX;
	Okres* maxOkresEAO = nullptr;
	Okres* minOkresEAO = nullptr;

	for each (auto item in *okresyZoradene_)
	{
		int priemernyPocetEAO = item->accessData()->getPriemernyPocetEAOSpoluVRozpati(rokOd, rokDo);
		if (priemernyPocetEAO > maxPriemernyPocetEAO)
		{
			maxPriemernyPocetEAO = priemernyPocetEAO;
			maxOkresEAO = item->accessData();
		}

		if (priemernyPocetEAO < minPriemernyPocetEAO)
		{
			minPriemernyPocetEAO = priemernyPocetEAO;
			minOkresEAO = item->accessData();
		}
	}
	std::cout << "\nOkres s najvacsim priemernym poctom ekonomicky aktivneho obyvatelstva v tychto rokoch:\n";
	std::cout << maxOkresEAO->getNazov() << " | " << maxPriemernyPocetEAO << "\n" << std::endl;

	std::cout << "Okres s najmensim priemernym poctom ekonomicky aktivneho obyvatelstva v tychto rokoch:\n";
	std::cout << minOkresEAO->getNazov() << " | " << minPriemernyPocetEAO << "\n" << std::endl;

	//-------------------------------------------------------
	// max pokles miery evidovanej nezamestnanosti muzi, zeny
	//-------------------------------------------------------

	double maxPoklesMENmuzi = 0;
	double maxPoklesMENzeny = 0;
	Okres* maxPoklesMuziOkres = nullptr;
	Okres* maxPoklesZenyOkres = nullptr;
	for each (auto item in *okresyZoradene_)
	{
		double poklesMENmuzi = item->accessData()->getPoklesMENmuziVRozpati(rokOd, rokDo);
		double poklesMENzeny = item->accessData()->getPoklesMENzenyVRozpati(rokOd, rokDo);

		if (poklesMENmuzi > maxPoklesMENmuzi)
		{
			maxPoklesMENmuzi = poklesMENmuzi;
			maxPoklesMuziOkres = item->accessData();
		}

		if (poklesMENzeny > maxPoklesMENzeny)
		{
			maxPoklesMENzeny = poklesMENzeny;
			maxPoklesZenyOkres = item->accessData();
		}
	}
	if (maxPoklesMuziOkres != nullptr)
	{
		std::cout << "Okres s najvacsim poklesom miery evidovanej nezamestnanosti v tychto rokoch u muzov:\n";
		std::cout << maxPoklesMuziOkres->getNazov() << " | " << maxPoklesMENmuzi << "%\n" << std::endl;
	}
	else
	{
		std::cout << "V ziadnom z okresov nenastal pokles miery evidovanej nezamestnanosti v tychto rokoch u muzov!\n";
	}
	
	if (maxPoklesZenyOkres != nullptr)
	{
		std::cout << "Okres s najvacsim poklesom miery evidovanej nezamestnanosti v tychto rokoch u zien:\n";
		std::cout << maxPoklesZenyOkres->getNazov() << " | " << maxPoklesMENzeny << "%\n" << std::endl;
	}
	else
	{
		std::cout << "V ziadnom z okresov nenastal pokles miery evidovanej nezamestnanosti v tychto rokoch u zien!\n";
	}

	//-------------------------------------------------------
	// najlepsi pomer DPU : absolventi
	//-------------------------------------------------------

	double bestPercento = 100; // ak je najlepsie pomer najvacsie cislo (pre najmensie daj INT_MAX)
	Okres* bestPercentoOkres = nullptr;

	for each (auto item in *okresyZoradene_)
	{
		double percentoAboslventiVDPU = item->accessData()->getPercentoAbsolventiVDPUVRozpati(rokOd, rokDo);
		if (percentoAboslventiVDPU < bestPercento) // pre najmensie cislo: <
		{
			bestPercento = percentoAboslventiVDPU;
			bestPercentoOkres = item->accessData();
		}
	}
	std::cout << "Okres s najmensim percentom absolventov medzi disponibilnymi uchadzacmi v tychto rokoch:\n";
	std::cout << bestPercentoOkres->getNazov() << " | " << bestPercento << "%\n" << std::endl;
}

void HlavnaTrieda::bod4()
{
	Kraj* najdeny;
	std::cout << "\n> Zadajte nazov kraju:\n";
	std::string nazovKraja;
	std::cin.ignore();
	std::getline(std::cin, nazovKraja);
	if (!krajeZoradene_->tryFind(nazovKraja, najdeny)) // nenasiel sa kraj s danym nazvom
	{
		std::cout << "\n> Nenasiel sa kraj s danym nazvom!";
		return;
	}

	std::cout << "\n> Zadajte rozpatie rokov:\n";
	std::cout << "\n> Zadajte pociatocny rok: [2001-2016]\n";
	std::string rokOdStr;
	std::cin >> rokOdStr;
	int rokOd = stoi(rokOdStr);
	if (rokOd < 2001 || rokOd > 2016)
	{
		std::cout << "\n> Pociatocny rok nie je v rozpati 2001-2016!";
		return;
	}
	std::cout << "\n> Zadajte koncovy rok: [2001-2016]\n";
	std::string rokDoStr;
	std::cin >> rokDoStr;
	int rokDo = stoi(rokDoStr);
	if (rokDo < 2001 || rokDo > 2016)
	{
		std::cout << "\n> Koncovy rok nie je v rozpati 2001-2016!";
		return;
	}
	if (rokOd > rokDo)
	{
		std::cout << "\n> 'Rok od' je vacsi ako 'rok do'!";
		return;
	}

	najdeny->zobrazSumarneStatistikyOUchadzacoch(rokOd, rokDo);
}

void HlavnaTrieda::bod5()
{
	std::cout << "\n> Zadajte rok:\n";
	std::string rokStr;
	std::cin >> rokStr;
	int rok = stoi(rokStr);
	if (rok < 2001 || rok > 2016)
	{
		std::cout << "\n> Rok nie je v rozpati 2001-2016";
		return;
	}
	std::cout << "\n> Zadajte, ci chcete vypisat" << std::endl;
	std::cout << "   [1] mieru evidovanej nezamestnanosti" << std::endl;
	std::cout << "   [2] disponibilny pocet uchadzacov\n";
	std::string volba;
	std::cin >> volba;

	std::cout << "\n> Zadajte, ci chcete zoradit vzostupne alebo zostupne [v/z]:\n";
	std::string zoraditAko;
	std::cin >> zoraditAko;
	switch (stoi(volba))
	{
	case 1: // vypisujem mieru evidovanej nezamestnanosti
	{
		HeapSort<std::string, Kraj*>* triedic = new HeapSort<std::string, Kraj*>();
		Comparator<Kraj*>* comp;

		if (zoraditAko == "v") // vzostupne
		{
			comp = new KrajeMENComparator(rok, "v");
		}
		else // zostupne
		{
			comp = new KrajeMENComparator(rok, "z");
		}

		triedic->sort(*krajeNezoradene_, *comp); // n*logN

		for each (auto item in *krajeNezoradene_)
		{
			std::cout << std::setw(20) << item->accessData()->getNazov() << " | " << item->accessData()->getMieraEvidovanejNezamestnanostiSpoluVRoku(rok) << "%" << std::endl; // O(n)
		}

		delete triedic;
		delete comp;
		break;
	}
	case 2: // vypisujem disponibilny pocet uchadzacov
	{
		HeapSort<std::string, Kraj*>* triedic = new HeapSort<std::string, Kraj*>();
		Comparator<Kraj*>* comp;

		if (zoraditAko == "v") // vzostupne
		{
			comp = new KrajeDPUComparator(rok, "v");
		}
		else // zostupne
		{
			comp = new KrajeDPUComparator(rok, "z");
		}

		triedic->sort(*krajeNezoradene_, *comp); // n*logN

		for each (auto item in *krajeNezoradene_)
		{
			std::cout << std::setw(20) << item->accessData()->getNazov() << " | " << item->accessData()->getDisponibilnyPocetUchadzacovSpoluVRoku(rok) << std::endl;
		}

		delete triedic;
		delete comp;
		break;
	}
	default:
		break;
	}
}

void HlavnaTrieda::bod6()
{
	std::cout << "\n> Zadajte rozpatie rokov:\n";
	std::cout << "\n> Zadajte pociatocny rok: [2001-2016]\n";
	std::string rokOdStr;
	std::cin >> rokOdStr;
	int rokOd = stoi(rokOdStr);
	if (rokOd < 2001 || rokOd > 2016)
	{
		std::cout << "\n> Pociatocny rok nie je v rozpati 2001-2016!";
		return;
	}
	std::cout << "\n> Zadajte koncovy rok: [2001-2016]\n";
	std::string rokDoStr;
	std::cin >> rokDoStr;
	int rokDo = stoi(rokDoStr);
	if (rokDo < 2001 || rokDo > 2016)
	{
		std::cout << "\n> Koncovy rok nie je v rozpati 2001-2016!";
		return;
	}
	if (rokOd > rokDo)
	{
		std::cout << "\n> 'Rok od' je vacsi ako 'rok do'!";
		return;
	}

	//------------------------------------------------------------
	// Kraje s max a min priemernym poctom ekonomicky aktivneho obyvatelstva 
	//------------------------------------------------------------

	int maxPriemernyPocetEAO = 0;
	int minPriemernyPocetEAO = INT_MAX;
	Kraj* maxOkresEAO = nullptr;
	Kraj* minOkresEAO = nullptr;

	for each (auto item in *krajeZoradene_)
	{
		int priemernyPocetEAO = item->accessData()->getPriemernyPocetEAOSpoluVRozpati(rokOd, rokDo);
		if (priemernyPocetEAO > maxPriemernyPocetEAO)
		{
			maxPriemernyPocetEAO = priemernyPocetEAO;
			maxOkresEAO = item->accessData();
		}

		if (priemernyPocetEAO < minPriemernyPocetEAO)
		{
			minPriemernyPocetEAO = priemernyPocetEAO;
			minOkresEAO = item->accessData();
		}
	}
	std::cout << "\nKraj s najvacsim priemernym poctom ekonomicky aktivneho obyvatelstva v tychto rokoch:\n";
	std::cout << maxOkresEAO->getNazov() << " | " << maxPriemernyPocetEAO << "\n" << std::endl;

	std::cout << "Kraj s najmensim priemernym poctom ekonomicky aktivneho obyvatelstva v tychto rokoch:\n";
	std::cout << minOkresEAO->getNazov() << " | " << minPriemernyPocetEAO << "\n" << std::endl;

	//----------------------------------------------------------------
	// Kraje s max poklesom miery evidovanej nezamestnanosti muzi, zeny
	//----------------------------------------------------------------

	double maxPoklesMENmuzi = 0;
	double maxPoklesMENzeny = 0;
	Kraj* maxPoklesMuziOkres = nullptr;
	Kraj* maxPoklesZenyOkres = nullptr;
	for each (auto item in *krajeZoradene_)
	{
		double poklesMENmuzi = item->accessData()->getPoklesMENmuziVRozpati(rokOd, rokDo);
		double poklesMENzeny = item->accessData()->getPoklesMENzenyVRozpati(rokOd, rokDo);

		if (poklesMENmuzi > maxPoklesMENmuzi)
		{
			maxPoklesMENmuzi = poklesMENmuzi;
			maxPoklesMuziOkres = item->accessData();
		}

		if (poklesMENzeny > maxPoklesMENzeny)
		{
			maxPoklesMENzeny = poklesMENzeny;
			maxPoklesZenyOkres = item->accessData();
		}
	}
	if (maxPoklesMuziOkres != nullptr)
	{
		std::cout << "Kraj s najvacsim poklesom miery evidovanej nezamestnanosti v tychto rokoch u muzov:\n";
		std::cout << maxPoklesMuziOkres->getNazov() << " | " << maxPoklesMENmuzi << "%\n" << std::endl;
	}
	else
	{
		std::cout << "V ziadnom z krajov nenastal pokles miery evidovanej nezamestnanosti v tychto rokoch u muzov!\n";
	}

	if (maxPoklesZenyOkres != nullptr)
	{
		std::cout << "Kraj s najvacsim poklesom miery evidovanej nezamestnanosti v tychto rokoch u zien:\n";
		std::cout << maxPoklesZenyOkres->getNazov() << " | " << maxPoklesMENzeny << "%\n" << std::endl;
	}
	else
	{
		std::cout << "V ziadnom z krajov nenastal pokles miery evidovanej nezamestnanosti v tychto rokoch u zien!\n";
	}

	//-------------------------------------------------------
	// kraj s najlepsim pomerom DPU : absolventi
	//-------------------------------------------------------

	double bestPercento = 0; // ak je najlepsie pomer najvacsie cislo (pre najmensie daj INT_MAX)
	Kraj* bestPercentoOkres = nullptr;

	for each (auto item in *krajeZoradene_)
	{
		double percentoAbsolventiVDPU = item->accessData()->getPercentoAbsolventiVDPUVRozpati(rokOd, rokDo);
		if (percentoAbsolventiVDPU > bestPercento) // pre najmensie cislo: <
		{
			bestPercento = percentoAbsolventiVDPU;
			bestPercentoOkres = item->accessData();
		}
	}
	std::cout << "Kraj s najmensim percentom absolventov medzi disponibilnymi uchadzacmi v tychto rokoch:\n";
	std::cout << bestPercentoOkres->getNazov() << " | " << bestPercento << "%\n" << std::endl;
}
	
