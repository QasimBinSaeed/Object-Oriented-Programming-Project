#pragma once
#ifndef SIMULATIONMODUlE_H
#define SIMULATIONMODULE_H
#include <fstream>
#include <string>
#include"PlantGrowthModule.h"
#include"SoilWaterModule.h"
#include"WeatherModule.h"
using namespace std;

class SimulationModule
{
private:
	WeatherModule obj;
	PlantGrowthModule obj1;
	SoilWaterModule obj2;
public:
	SimulationModule();
	void Initialization();
	void rateCalculations();
	void Integration();
	void Output();
	void Close();
	float getLai();
	float w();
	float wc();
	float wr();
	float wf();
	float N();
	float TMAX();
	float TMIN();
	float SRAD();
	float RAIN();
	float IRR();
	float ROF();
	float DP();
	float INF();
	float DRN();
	float ETp();
	float ESa();
	float EPa();
	float SWC();
	float SWFAC1();
	float SWFAC2();
	float pint()//int of plant
	{
		return obj1.getint();
	}
	float intot()
	{
		return obj1.getintot();
	}
};
#endif // !SIMULATION_H