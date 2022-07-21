#include "WeatherModule.h"
#include"PlantGrowthModule.h"
#include"SoilWaterModule.h"
#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#define EULER 2.7182

WeatherModule::WeatherModule()
{
	sw_soil = 0;
	PAR = 0;
	DATE = 0;
	RAIN = 0;
	SRAD = 0;
	TMAX = 0;
	TMIN = 0;
}
WeatherModule::WeatherModule(WeatherModule& object)
{
	sw_soil = object.sw_soil;
	PAR = object.PAR;
	DATE = object.DATE;
	RAIN = object.RAIN;
	SRAD = object.SRAD;
	TMAX = object.TMAX;
	TMIN = object.TMIN;
}
void WeatherModule::Initialization()
{//
	weather_inp.open("WEATHER.INP", ios::in);
	string boo;
	getline(weather_inp, boo, delim);
	DATE = stof(boo);
	getline(weather_inp, boo, delim);
	SRAD = stof(boo);
	getline(weather_inp, boo, delim);
	TMAX = stof(boo);
	getline(weather_inp, boo, delim);
	TMIN = stof(boo);
	getline(weather_inp, boo, delim);
	RAIN = stof(boo);
	getline(weather_inp, boo, delim);
	PAR = stof(boo);

	weather_inp.close();
}
void WeatherModule::rateCalculations()
{

}
void WeatherModule::Close()
{
	weather_inp.close();
}
float WeatherModule::getTMAX()
{
	return TMAX;
}
float WeatherModule::getTMIN()
{
	return TMIN;
}
float WeatherModule::getSRAD()
{
	return SRAD;
}
float WeatherModule::getRAIN()
{
	return RAIN;
}