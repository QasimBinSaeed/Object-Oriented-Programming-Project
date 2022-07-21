#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include"PlantGrowthModule.h"
#include"WeatherModule.h"
#include"SoilWaterModule.h"
#define EULER 2.7182
using namespace std;

PlantGrowthModule::PlantGrowthModule()
{
	EMP1 = 0;

	EMP2 = 0;
	fc = 0;
	intot = 0;
	LAI = 0;
	Lfmax = 0;
	n = 0;
	nb = 0;
	p1 = 0;
	PD = 0;
	rm = 0;
	tb = 0;
	w = 0;
	wc = 0;
	wr = 0;
	//Input Done
	wf = 0;
	Y1 = 0;
	SLA = 0;
	ROWSPC = 0;
	PT = 0;
	PG = 0;
	N = 0;
	p = 0;
	dLAI = 0;
	di = 0;
	a = 0;
	dN = 0;
	SWFAC = 0;
}

PlantGrowthModule::PlantGrowthModule(const PlantGrowthModule& object)
{
	EMP1 = object.EMP1;
	EMP2 = object.EMP2;
	fc = object.fc;
	intot = object.intot;
	LAI = object.LAI;
	Lfmax = object.Lfmax;
	n = object.n;
	nb = object.nb;
	p1 = object.p1;
	PD = object.PD;
	rm = object.rm;
	tb = object.tb;
	w = object.w;
	wc = object.wc;
	wr = object.wr;
	//Input Done
	wf = object.wf;
	Y1 = object.Y1;
	SLA = object.SLA;
	ROWSPC = object.ROWSPC;
	PT = object.PT;
	PG = object.PG;
	N = object.N;
	p = object.p;
	dLAI = object.dLAI;
	di = object.di;
	a = object.a;
	dN = object.dN;
	SWFAC = object.SWFAC;
}

void PlantGrowthModule::Initialization()
{

	PLANT_INP.open("PLANT.INP", ios::in);
	string boo;
	getline(PLANT_INP, boo, delim);
	EMP1 = stof(boo);
	getline(PLANT_INP, boo, delim);
	EMP2 = stof(boo);
	getline(PLANT_INP, boo, delim);
	fc = stof(boo);
	getline(PLANT_INP, boo, delim);
	intot = stof(boo);
	getline(PLANT_INP, boo, delim);
	lai = stof(boo);
	getline(PLANT_INP, boo, delim);
	Lfmax = stof(boo);
	getline(PLANT_INP, boo, delim);
	n = stof(boo);
	getline(PLANT_INP, boo, delim);
	nb = stof(boo);
	getline(PLANT_INP, boo, delim);
	p1 = stof(boo);
	getline(PLANT_INP, boo, delim);
	PD = stof(boo);
	getline(PLANT_INP, boo, delim);
	rm = stof(boo);
	getline(PLANT_INP, boo, delim);
	tb = stof(boo);
	getline(PLANT_INP, boo, delim);
	w = stof(boo);
	getline(PLANT_INP, boo, delim);
	wc = stof(boo);
	getline(PLANT_INP, boo, delim);
	wr = stof(boo);
	PLANT_INP.close();
}
void PlantGrowthModule::PlantGrowthModule::LAIS(WeatherModule& obj, SoilWaterModule& obj1)
{
	SWFAC = min(obj1.SWFAC1, obj1.SWFAC2);
	if (FL == 1)
	{
		a = exp(EMP2 * (N - nb));
		dLAI = SWFAC * PD * EMP1 * PT * (a / (1 + a)) * dN;
	}
	else if (FL == 2)
	{
		dLAI = -PD * di * p1 * SLA;
	}
}
void PlantGrowthModule::PTS(WeatherModule& obj)
{

	PT = 1 - 0.0025 * (pow((0.25 * obj.TMIN - 0.75 * obj.TMAX) - 26, 2));
}
void PlantGrowthModule::PGS(WeatherModule& obj, SoilWaterModule& obj1)
{
	SWFAC = min(obj1.SWFAC1, obj1.SWFAC2);
	ROWSPC = 60.0;
	Y1 = 1.5 - 0.768 * pow((pow((ROWSPC * 0.01), 2) * PD), 0.1);
	PG = 2.1 * (obj.SRAD / PD) * (1.0 - pow(EULER, -Y1 * LAI));
}
void PlantGrowthModule::Integration()
{
	LAI = LAI + dLAI;
	w = w + dw;
	wc = wc + dwc;
	wr = wr + dwr;
	wf = wf + dwf;
	N = N + dN;
	LAI = max(LAI, float(0)); // to avoid error as MAX(FLOAT,FLOAT) 
	w = max(w, float(0));
	wc = max(wc, float(0.0));
	wr = max(wr, float(0.0));
	wf = max(wf, float(0.0));
}
float PlantGrowthModule::rateCalculations(WeatherModule& obj, SoilWaterModule& obj1)
{
	TMEAN = 0.5 * (obj.TMAX + obj.TMIN);
	PTS(obj);
	PGS(obj, obj1);
	if (N < Lfmax)
	{
		//Vegetative Phase
		FL = 1.0;
		E = 1.0;
		dN = rm * PT;
		LAIS(obj, obj1);
		dw = E * (PG)*PD;
		dwc = fc * dw;
		dwr = (1 - fc) * dw;
		dwf = 0.0;
	}
	else
	{
		//Reproductive Phase
		FL = 2.0;
		if (TMEAN > tb && TMEAN < 25)
		{
			di = TMEAN - tb;
		}
		else
		{
			di = 0.0;
		}
		accTemp = accTemp + di;
		E = 1.0;
		LAIS(obj, obj1);
		dw = E * (PG)*PD;
		dwf = dw;
		dwc = 0.0;
		dwr = 0.0;
		dN = 0.0;
	}
	return LAI;
}
void PlantGrowthModule::Output()
{
	PLANT_OUT.open("PLANT.OUT", ios::app);
	//DAILY OUTPUT
	PLANT_OUT << LAI << delim << w << delim << wc << delim << wr << delim << wf << delim << N << endl;
}
void PlantGrowthModule::Close()
{
	PLANT_OUT.close();
}
float PlantGrowthModule::getw()
{
	return w;
}
float PlantGrowthModule::getwc()
{
	return wc;
}
float PlantGrowthModule::getwr()
{
	return wr;
}
float PlantGrowthModule::getwf()
{
	return wf;
}
float PlantGrowthModule::getN()
{
	return N;
}
float PlantGrowthModule::getint()
{
	return accTemp;
}
float PlantGrowthModule::getintot()
{
	return intot;
}