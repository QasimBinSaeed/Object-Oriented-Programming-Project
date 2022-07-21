#include "SimulationModule.h"
#include <fstream>
#include <string>
#include"PlantGrowthModule.h"
#include"SoilWaterModule.h"
#include"WeatherModule.h"
using namespace std;

SimulationModule::SimulationModule()
{
}
void SimulationModule::Initialization()
{
	obj.Initialization();
	obj1.Initialization();
	obj2.Initialization();
}
void SimulationModule::rateCalculations()
{
	obj.rateCalculations();
	obj1.rateCalculations(obj, obj2);
	obj2.rateCalculations(obj, obj1);
}
void SimulationModule::Integration()
{
	obj1.Integration();
	obj2.Integration();
}
void SimulationModule::Output()
{
	obj1.Output();
	obj2.Output(obj);
}
void SimulationModule::Close()
{
	obj.Close();
	obj1.Close();
	obj2.Close(obj);
}
float SimulationModule::getLai()
{
	return obj1.rateCalculations(obj, obj2);
}
float SimulationModule::w()
{
	return obj1.getw();
}
float SimulationModule::wc()
{
	return obj1.getwc();
}
float SimulationModule::wr()
{
	return obj1.getwr();
}
float SimulationModule::wf()
{
	return obj1.getwf();
}
float SimulationModule::N()
{
	return obj1.getN();
}
float SimulationModule::TMAX()
{
	return obj.getTMAX();
}
float SimulationModule::TMIN()
{
	return obj.getTMIN();
}
float SimulationModule::SRAD()
{
	return obj.getSRAD();
}
float SimulationModule::RAIN()
{
	return obj.getRAIN();
}
float SimulationModule::IRR()
{
	return obj2.getIRR();
}
float SimulationModule::ROF()
{
	return obj2.getROF();
}
float SimulationModule::DP()
{
	return obj2.getDP();
}
float SimulationModule::INF()
{
	return obj2.getINF();
}
float SimulationModule::DRN()
{
	return obj2.getDRN();
}
float SimulationModule::ETp()
{
	return obj2.getETp();
}
float SimulationModule::ESa()
{
	return obj2.getESa();
}
float SimulationModule::EPa()
{
	return obj2.getEPa();
}
float SimulationModule::SWC()
{
	return obj2.getSWC();
}
float SimulationModule::SWFAC1()
{
	return obj2.getSWFAC1();
}
float SimulationModule::SWFAC2()
{
	return obj2.getSWFAC2();
}