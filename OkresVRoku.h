#pragma once
#include "structures\heap_monitor.h"

class OkresVRoku
{
public:
	OkresVRoku(int rok);
	~OkresVRoku();
	int getZPUchadzaci();
	int getAbsolventiUchadzaci();
	int getMladistviUchadzaci();
	int getDlhodoboEvidovaniUchadzaci();
	void setZPUchadzaci(int cislo);
	void setAbsolventiUchadzaci(int cislo);
	void setMladistviUchadzaci(int cislo);
	void setDlhodoboEvidovaniUchadzaci(int cislo);

	double getSpoluMEN();
	double getMuziMEN();
	double getZenyMEN();
	int getSpoluEAO();
	int getMuziEAO();
	int getZenyEAO();
	int getSpoluDPU();
	int getMuziDPU();
	int getZenyDPU();
	void setSpoluMEN(double cislo);
	void setMuziMEN(double cislo);
	void setZenyMEN(double cislo);
	void setSpoluEAO(int cislo);
	void setMuziEAO(int cislo);
	void setZenyEAO(int cislo);
	void setSpoluDPU(int cislo);
	void setMuziDPU(int cislo);
	void setZenyDPU(int cislo);

private:
	int rok_;
	int zpUchadzaci_;
	int absolventiUchadzaci_;
	int mladistviUchadzaci_;
	int dlhodoboEvidovaniUchadzaci_;
	double spoluMEN_;
	double muziMEN_;
	double zenyMEN_;
	int spoluEAO_;
	int muziEAO_;
	int zenyEAO_;
	int spoluDPU_;
	int muziDPU_;
	int zenyDPU_;
};

