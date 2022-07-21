#pragma once
#ifndef PLANTGROWTHMODULE_H
#define PLANTGROWTHMODULE_H
#include"WeatherModule.h"
#include"SoilWaterModule.h"
#include<fstream>
#include<string>

using namespace std;
class PlantGrowthModule
{
private:
	//Input Start
	float accTemp;//intS
	float TMEAN;
	fstream PLANT_INP;
	fstream PLANT_OUT;
	float EMP1;
	float EMP2;
	float fc;
	float intot;
	float LAI;
	float Lfmax;
	float n;
	float nb;
	float p1;
	float PD;
	float rm;
	float tb;
	float w;
	float wc;
	float wr;
	//Input Done

	float wf;
	float Y1;
	float SLA;
	float ROWSPC;
	float PT;
	float PG;
	float N;
	float p;
	float lai;
	float dLAI;
	float di;
	float a;
	float dN;
	char delim = ',';
	float SWFAC;
	float FL, E, dw, dwc, dwr, dwf;

public:
	PlantGrowthModule();
	PlantGrowthModule(const PlantGrowthModule& object);
	void Close();
	void Initialization();
	void LAIS(WeatherModule& obj, SoilWaterModule& obj1);
	void PTS(WeatherModule& obj);
	void PGS(WeatherModule& obj, SoilWaterModule& obj1);
	void Integration();
	float rateCalculations(WeatherModule& obj, SoilWaterModule& obj1);
	void Output();
	float getw();
	float getwc();
	float getwr();
	float getwf();
	float getN();
	float getint();
	float getintot();
	friend class SoilWaterModule;
};
#endif // !PLANTGROWTH_H