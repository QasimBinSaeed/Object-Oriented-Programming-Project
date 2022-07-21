#pragma once
#ifndef SOILWATERMODULE_H
#define SOILWATERMODULE_H
#include"WeatherModule.h"
#include"PlantGrowthModule.h"
#include<fstream>
#include<string>
using namespace std;

class SoilWaterModule
{
private:
	char delim = ',';
	//INPUT OPEN
	fstream SW_OUT;
	fstream IRRIG;
	fstream WBAL_OUT;
	float SWC;
	float CN;
	float DP;
	float DRNp;
	float FCp;
	float STp;
	float WPp;
	//INPUT DONE
	//converted values in mm
	float WP;
	float FC;
	float ST;
	//IRRIGATION PART
	//CUMULATIVE VALUES
	float TRAIN;
	float TIRR;
	float TESA;
	float TEPA;
	float TROF;
	float TDRN;
	float TINF;
	//OTHER INPUT VALUES FROM IRRIGATION.INP
	float IRR;
	float ESA;
	float EPA;
	float ROF;
	float DRN;
	float INF;
	//SELF TAKEN
	float ETp;
	float EPp;
	float POTINF; //potential infiltration
	float S;
	float TMEAN;
	float ESp;
	float WTABLE;
	float W_BAL;
	float THE;
	float SWFAC;
	float SWFAC1;
	float SWFAC2;
	float STRESS_DEPTH;
	float ESa;
	float EPa;
	float DWT;
	//additional 
	float SWC_ADJ;
public:
	SoilWaterModule();
	void Initialization();
	void rateCalculations(WeatherModule& obj, PlantGrowthModule& obj1);
	void Integration();
	void DRAINE();
	void WBAL(WeatherModule& obj);
	void ETpS(WeatherModule& obj, PlantGrowthModule& obj1);
	void Output(WeatherModule& obj);
	void Close(WeatherModule& obj);
	void RUNOFF();
	void STRESS();
	void ESaS();
	float getIRR();
	float getROF();
	float getDP();
	float getINF();
	float getDRN();
	float getETp();
	float getESa();
	float getEPa();
	float getSWC();
	float getSWFAC1();
	float getSWFAC2();
	friend class PlantGrowthModule;
};

#endif // !SOILWATERMODULE_H