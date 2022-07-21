#pragma once

#include<fstream>
#include<string>
using namespace std;

class WeatherModule
{
private:
	fstream weather_inp;
	float sw_soil;
	float PAR;
	float DATE;
	float RAIN;
	float SRAD;
	float TMAX, TMIN;
	char delim = ',';
public:
	WeatherModule();
	WeatherModule(WeatherModule& object);
	void Initialization();
	void rateCalculations();
	void Close();
	float getTMAX();
	float getTMIN();
	float getSRAD();
	float getRAIN();
	friend class PlantGrowthModule;
	friend class SoilWaterModule;
};