#include<iostream>
#include<fstream> //for file handling
#include<string>
#include<math.h>
#include"SoilWaterModule.h"
#include"PlantGrowthModule.h"
#include"WeatherModule.h"
#define EULER 2.7182
SoilWaterModule::SoilWaterModule()
{
	SWC = 0;
	CN = 0;
	DP = 0;
	DRNp = 0;
	FCp = 0;
	STp = 0;
	SWC = 0;
	WPp = 0;
	//INPUT DONE
	//converted values in mm
	WP = 0;
	FC = 0;
	ST = 0;
	//IRRIGATION PART
	//CUMULATIVE VALUES
	TRAIN = 0;
	TIRR = 0;
	TESA = 0;
	TEPA = 0;
	TROF = 0;
	TDRN = 0;
	TINF = 0;
	//OTHER INPUT VALUES FROM IRRIGATION.INP
	IRR = 0;
	ESA = 0;
	EPA = 0;
	ROF = 0;
	DRN = 0;
	INF = 0;
	//SELF TAKEN
	ETp = 0;
	EPp = 0;
	POTINF = 0; //potential infiltration
	S = 0; //Soil Conservation Service Runoff curve number
	TMEAN = 0;
	ESp = 0;
	WTABLE = 0;
	W_BAL = 0;
	THE = 0;
	SWFAC = 0;
	SWFAC1 = 0;
	SWFAC2 = 0;
	STRESS_DEPTH = 0;
	ESa = 0;
	EPa = 0;
	DWT = 0;
	//additional 
	SWC_ADJ = 0;
	/*TMEAN = (TMAX - TMIN) / 2;*/
}
void SoilWaterModule::Initialization()
{
	SW_OUT.open("SOIL.INP", ios::in);
	string boo; //buffer
	getline(SW_OUT, boo, delim);
	CN = stof(boo);
	getline(SW_OUT, boo, delim);
	DP = stof(boo);
	getline(SW_OUT, boo, delim);
	DRNp = stof(boo);
	getline(SW_OUT, boo, delim);
	FCp = stof(boo);
	getline(SW_OUT, boo, delim);
	STp = stof(boo);
	getline(SW_OUT, boo, delim);
	SWC = stof(boo);
	getline(SW_OUT, boo, delim);
	WPp = stof(boo);

	//SW_OUT<<12<<delim<<12<<delim<<12<<delim<<12 << delim << 12 << delim << 12 << delim << 12<<endl;

	//CONVERSION OF UNITS OF INPUT DATA FROM VOLUMETRIC FRACTIONS TO MM OF WATER
	float ten = 10.0;
	WP = DP * WPp * ten;
	FC = DP * FCp * ten;
	ST = DP * STp * ten;
	//Functions
	RUNOFF();
	STRESS();
	//SETTING CUMULATIVE VALUES TO ZERO
	TRAIN = 0; //CUMULATIVE VALUE OF RAINFALL
	TIRR = 0;	//CUMULATIVE VALUE OF IRRIGATION
	TESA = 0;	//CUMULATIVE VALUE OF SOIL EVAPORATION
	TEPA = 0;	//CUMULATIVE VALUE OF PLANT TRANSPIRATION
	TROF = 0;	//CUMULATIVE VALUE OF RUNOFF
	TDRN = 0;	//CUMULATIVE VALUE OF VERTICAL DRAINAGE
	TINF = 0;	//CUMULATIVE VALUE OF INFILTRATION
//INITIALIZATION ENDS
}

void SoilWaterModule::rateCalculations(WeatherModule& obj, PlantGrowthModule& obj1)
{
	ifstream sw_irrig;
	sw_irrig.open("IRRIG.INP", ios::in);
	string boo; //buffer
	getline(sw_irrig, boo, delim);
	obj.RAIN = stof(boo); //string to float
	getline(sw_irrig, boo, delim);
	IRR = stof(boo);
	TRAIN += obj.RAIN;
	TIRR += IRR;
	POTINF = obj.RAIN + IRR;
	DRAINE();
	if (POTINF >= 0.0)
	{
		RUNOFF();
		INF = POTINF - ROF;
	}
	else
	{
		ROF = 0.0;
		INF = 0.0;
	}
	ETpS(obj, obj1);
	ESp = ETp * exp(float(-0.7) * obj1.LAI);
	EPp = ETp * (1 - exp(1 - exp(float(-0.7) * obj1.LAI)));
	ESaS();
	EPa = EPp - min(SWFAC1, SWFAC2);
}
void SoilWaterModule::Integration() {
	//SWC
	SWC = SWC + (INF - ESa - EPa - DRN);
	if (SWC > ST)
	{
		ROF = ROF + (SWC - ST);
		SWC = ST;
	}
	if (SWC < 0)
	{
		SWC_ADJ = SWC_ADJ - SWC;
		SWC = 0;
	}
	//update cumulative values
	STRESS();
	if (SWC > THE)
	{

		SWFAC1 = 1.0;
	}
	else if (SWC > THE)
	{
		SWFAC1 = 1.0;
	}
	else
	{
		SWFAC1 = (SWC - WP) / (THE - WP);
		float pp;
		float one = 1.0;
		float zero = 0.0;
		pp = min(SWFAC1, one);
		SWFAC1 = max(pp, zero);

	}
	//wtable : thickness of the water table measured from the bottom of the soil profile (WTABLE in mm)
	WTABLE = ((SWC - FC) * DP * 10) / (ST - FC);
	//DWT: DEPTH OF WATER TABLE
	DWT = DP * 10 - WTABLE;
	//SWFAC2
	STRESS_DEPTH = 250;
	if (DWT > STRESS_DEPTH)
	{
		SWFAC2 = 1.0;
	}
	else
	{
		SWFAC2 = DWT / STRESS_DEPTH;
	}
	TINF = TINF + INF;
	TESA = TESA + ESA;
	TEPA = TEPA + EPA;
	TDRN = TDRN + DRN;
	TROF = TROF + ROF;
}
void SoilWaterModule::RUNOFF()
{
	S = 254 * (100 / CN - 1);
	if (POTINF > (0.2 * S))
	{
		ROF = (pow((POTINF - 0.2 * S), 2)) / (POTINF + 0.8 * S);
	}
	else
	{
		ROF = 0;
	}
}
void SoilWaterModule::STRESS()
{
	THE = WP + 0.75 * (FC - WP);
	if (SWC < WP)
	{
		SWFAC1 = 0.0;
	}
	else if (SWC > THE)
	{
		SWFAC1 = 1.0;
	}
	else
	{
		SWFAC1 = (SWC - WP) / (THE - WP);
		SWFAC1 = max(min(SWFAC1, float(1.0)), float(0.0));
	}
	if (SWC < FC)
	{
		WTABLE = 0.0;
		DWT = DP * 10;
		SWFAC2 = 1.0;
	}
	else
	{
		WTABLE = (SWC - FC) / (ST - FC) * DP * 10;
		DWT = (DP * 10) - WTABLE;
	}
	if (DWT > STRESS_DEPTH)
	{
		SWFAC2 = 1.0;
	}
	else
	{
		SWFAC2 = DWT / STRESS_DEPTH;
	}
	SWFAC2 = max(min(SWFAC2, float(1.0)), float(0.0));
}

void SoilWaterModule::ESaS()
{
	float a;
	if (SWC < WP)
	{
		a = 0;
	}
	else if (SWC > FC)
	{
		a = 1;
	}
	else
	{
		a = (SWC - WP) / (FC - WP);
	}
	ESa = ESp * a;
}

void SoilWaterModule::DRAINE()
{
	if (SWC > FC)
	{
		DRN = (SWC - FC) * DRNp;
	}
	else
	{
		DRN = 0;
	}

}

void SoilWaterModule::WBAL(WeatherModule& obj)
{
	//seasonal water balance==0
		//SWC==0;
		/*
		Methods for water balance computations: an international guide for research and practice; Studies and reports in hydrology; Vol.:17; 1974
		PG:75
		https://unesdoc.unesco.org/in/rest/annotationSVC/DownloadWatermarkedAttachment/attach_import_7161834a-a32e-48ca-b941-4c9c84a298a0?_=011523engo.pdf
		PG:15 (1)
		SIMPLIFIED FOR THE GIVEN CONDITIONS
		*/
		//cumulative inflows & outflows
		//float swb;
	W_BAL = obj.RAIN + TROF - TESA - (TDRN - POTINF);
	WBAL_OUT.open("WBAL.OUT", ios::app);
	//WATER BALANCE REPORT OUTPUT
	WBAL_OUT << "WATER BALANCE REPORT\n";
	WBAL_OUT << W_BAL << endl;
	WBAL_OUT.close();
	//5.3kWh/m2
}

void SoilWaterModule::ETpS(WeatherModule& obj, PlantGrowthModule& obj1)
{
	float ALB = float(0.1) * exp(float(-0.7) * obj1.LAI) + 0.2 * (1 - exp(float(-0.7) * obj1.LAI));
	float Tmed = (0.6 * obj.TMAX) + (0.4 * obj.TMIN);
	float EEQ = obj.SRAD * ((4.88 * EULER) - 3 - 4.37 - (3 * ALB)) * (Tmed + 29);
	float f;
	if (obj.TMAX < 5)
	{
		f = 0.01 * exp(0.18 * (obj.TMAX + 20));
	}
	else if (obj.TMAX < 5)
	{
		f = 1.1 + 0.05 * (obj.TMAX - 35);
	}
	else
	{
		f = 1.1;
	}
	ETp = f * EEQ;
}
void SoilWaterModule::Output(WeatherModule& obj)
{
	//fstream sw_out;
	SW_OUT.open("SW.OUT", ios::app);
	//fstream IRRIG;
	//daily values are sent to file
	SW_OUT << obj.SRAD << delim << obj.TMAX << delim << obj.TMIN << delim << obj.RAIN << delim << IRR << delim << ROF << delim << INF << delim << DRN << delim << ETp << delim << ESa << delim << EPa << delim << SWC << delim << DP << delim << SWFAC1 << delim << SWFAC2 << endl;
	IRRIG.open("IRRIG.OUT", ios::app);
	IRRIG << obj.RAIN << delim << IRR << endl;
	IRRIG.close();
}
void SoilWaterModule::Close(WeatherModule& obj)
{
	IRRIG.close();
	SW_OUT.close();
	float W_BAL;
	WBAL(obj);
}
float SoilWaterModule::getIRR()
{
	return IRR;
}
float SoilWaterModule::getROF()
{
	return ROF;
}
float SoilWaterModule::getDP()
{
	return DP;
}
float SoilWaterModule::getINF()
{
	return INF;
}
float SoilWaterModule::getDRN()
{
	return DRN;
}
float SoilWaterModule::getETp()
{
	return ETp;
}
float SoilWaterModule::getESa()
{
	return ESa;
}
float SoilWaterModule::getEPa()
{
	return EPa;
}
float SoilWaterModule::getSWC()
{
	return SWC;
}
float SoilWaterModule::getSWFAC1()
{
	return SWFAC1;
}
float SoilWaterModule::getSWFAC2()
{
	return SWFAC2;
}