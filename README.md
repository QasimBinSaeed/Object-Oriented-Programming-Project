# Object-Oriented-Programming-Project
Plant Growth Monitoring System
Modular Crop Growth Model and Simulation 
Suggested Language C++ 
Maximum Team Size 4 
Skill Set C++, GUI 
1. Introduction
Crop growth model is an excellent example of object 
oriented paradigm. Such a model is composed of a 
number of parts like plant, soil, weather, etc. Being 
able to handle all of these separately as well as 
together is the focus of this project. 
2. Problem Description
The model is intended to simulate the growth of a 
particular type of plant while interacting with soil and 
weather under various conditions. 
3. Solution Design (Tentative, Incomplete)
The suggested model has four main classes: the 
simulation class, plant class, soil water balance class 
and weather class. Figure 1 illustrates the classes; 
where each class has two or more of the following five 
functionalities: 
1. The initialization (constructor) section is used to 
input data and initialize variables at start of simulation 
2. The ‘rate calculation’ functionality computes 
process rates and rates of change of state variables 
based on conditions at the end of the previous day of 
simulation. This method is called once per time step 
(day) of simulation. 
3. The ‘integration’ method updates state variables 
using the rates previously calculated. 
4. The ‘output’ method is called once per day to 
generate daily output reports. 
5. The ‘close’ functionality is called once at the end 
of simulation to close output files and generate summary 
reports. 
The simulation object makes calls to methods 
inside each other object to accomplish the various 
components of processing. Each object (weather, soil 
water, plant) is called once at the beginning of 
simulation to initialize, resulting in execution of the 
initialization portion of the object. During the daily 
time loop, each object is called three times: for rate 
calculation, for integration calculations, and for output 
of daily computed data. A final call to each object is 
made to write summary output files and to close input 
and output files after the simulation is complete. 
Rate calculation, integration and output 
methods are within the time step loop and the soil 
water and plant objects are each called three times per 
time step within this loop. The weather object is also 
called from within the time step loop, but only once 
per day (i.e. in the rate calculation part.) 
Figure 1. Class/Message Structure
3.1Plant Class 
The plant class computes plant growth and development 
based on daily values of maximum and minimum 
temperatures, radiation and the daily value of two soil water 
stress factors, SWFAC1 and SWFAC2. This class also 
simulates leaf area index (LAI), which is used in the soil 
water class to compute evapotranspiration. Details of its 
functionality are as under: 
Initialization 
Input variables, as listed in Table 1, are read from file 
PLANT.INP. File PLANT.OUT is opened and a header is 
written to this output file. 
Rate calculations 
The plant object calls three methods: 
1. Method PTS to calculate the effect of temperature 
on daily plant growth rate and rate of leaf number increase. 
The growth rate reduction factor (PT) is calculated every 
day using the following equation: 
where TMIN and TMAX are the minimum and maximum 
daily temperatures, respectively. 
2. Method PGS() to calculate the daily plant weight 
increase; The method calculates PG, the potential daily total 
dry matter increase (g/plant) as: 
3.
where SRAD is the daily solar radiation (MJ/m2
) and PD 
the plant density (plant/m2
). Y1 is obtained by: 
where ROWSPC is the row spacing in (cm). 
4. Method LAIS() to calculate increase in leaf area 
index dLAI. 
The plant cycle is divided into vegetative and 
reproductive phases. The vegetative phase continues 
until the plant reaches a genetically determined 
maximum leaf number (Lfmax). During the vegetative 
phase, leaf number increase (dN) is calculated based on 
a maximum rate (rm) and a temperature based limiting 
factor (PT). During reproductive phase, di, the 
difference between daily mean temperature and a base 
temperature (tb), is used to calculate the rate of plant 
development. Total rate of development towards 
maturity is accumulated as an int. Method LAIS is 
called for both phases to compute the change in leaf 
area index (dLAI). 
During vegetative period, LAI increases as a function 
of the rate of leaf number increase. The potential rate is 
limited by soil water stress (both deficit and saturation) 
through SWFAC, and temperature, through PT. Its 
value is given by: 
where PD is the plant density (plants/m2
), EMP1 is the 
maximum leaf area expansion per leaf, (0.104 m2/leaf) 
and a is given by: 
where EMP2 and nb are coefficients in the expolinear 
equation and N is the development age of the plant (leaf 
number). 
After plant has reached the maximum number of leaves,i.e. 
during reproductive phase, LAI starts to decrease as a 
function of the daily thermal integral, di. The rate of 
decrease is given by: 
where p1 is the dry matter of leaves removed per plant per 
unit development after maximum number of leaves is 
reached and SLA is the specific leaf area. 
In the vegetative phase the assimilates are partitioned 
between canopy and roots (dwc and dwr) whereas in the 
reproductive phase all growth occurs in the grain (dwf). All 
whole plant weight increases (dw) are converted to area 
based values by multiplying by the plant density value (PD). 
Integration 
Changes to leaf area index (dLAI), plant weights (dw, dwc, 
dwr and dwf) and leaf number (dN) are integrated into the 
appropriate state variables (LAI, w, wc, wr, wf and N) at 
the beginning of the ‘integration’ section. 
When the accumulated value of the rate of 
development towards maturity (int) reaches a genetically 
determined value (intot), the plant is matured and the 
simulation is complete. 
Output 
Daily output is written to the PLANT.OUT file. 
Close 
The PLANT.OUT output file is closed. 
3.2 Soil Water Class 
A single, homogeneous soil layer underlain by a relatively 
impervious layer is assumed for the model. A simple water 
balance is used to update the soil water content on a daily 
basis using computed values of infiltration, evaporation, 
transpiration and drainage. 
The soil characteristics defined are soil water content 
at wilting point (WPp), field capacity (FCp) and saturation 
(STp) all in units of cm3
/cm3
; soil profile depth (DP in cm), 
daily drainage fraction (DRNp), curve number (CN) and 
initial soil water content (SWC_INIT in mm). 
The soil water class calculates two parameters 
(SWFAC1 and SWFAC2) which express the effects of 
drought and excess soil water respectively on crop growth 
rate. These factors vary from 1.0 (minimum stress) to 0.0 
(maximum stress). 
In addition to soil characteristics and weather data, this 
class requires the value of leaf area index (LAI), which is 
computed in the plant class, to calculate potential 
evapotranspiration. 
Details of functionality of the class are as under: 
Initialization 
In the ‘initialization’ portion of the code, input files 
SOIL.INP and IRRIG.INP and output file SW.OUT are 
opened. The required soil input data is read from file 
SOIL.INP and the file is closed. These input variables 
are listed in Table 2. Headers are written to output file 
SW.OUT. 
Units for the soil parameters are converted from 
volumetric fractions to mm of water as: 
WP = DP * WPp * 10.0 
FC = DP * FCp * 10.0 
ST = DP * STp * 10.0 where WP, FC and ST are the 
wilting point, field capacity and saturation content in mm 
of water, respectively. Other variables are as defined in 
Table 2. 
For initialization, method RUNOFF() is called to 
compute soil storage capacity (S) based on the Soil 
Conservation Service runoff curve number method: 
S = 254 * (100/CN - 1) 
Then, method STRESS() is called to calculate the 
threshold soil water content below which drought stress 
will occur (THE). This is approximated as: THE = WP 
+ 0.75 * (FC - WP) Initial stress factors (SWFAC1 and 
SWFAC2) are then calculated based on initial soil water 
content. This is discussed in more detail later. 
Cumulative values of rainfall (TRAIN), irrigation 
(TIRR), soil evaporation (TESA), plant transpiration 
(TEPA), runoff (TROF), vertical drainage (TDRN), and 
infiltration (TINF) are set to zero for the beginning of the 
simulation. 
Rate calculations 
Irrigation rates are read from file IRRIG.INP. 
Potential infiltration (POTINF) is calculated as the sum 
of rainfall (RAIN) and irrigation (IRR). Cumulative 
irrigation and rainfall depths are summed to TIRR and 
TRAIN, respectively. 
Method DRAINE() is called to compute vertical 
drainage of soil water (DRN in mm) based on a daily 
fraction of the soil water content above field capacity: 
DRN = (SWC - FC) * DRNp 
If potential infiltration (POTINF) is greater than zero, 
method RUNOFF() is called to compute daily surface water 
runoff rates (ROF) using the SCS curve number method: 
IF (POTINF > 0.2 * S) THEN 
ROF = ((POTINF - 0.2 * S)**2)/(POTINF + 0.8 * S) 
ELSE 
 ROF = 0 
ENDIF 
Infiltration (INF) is calculated as the difference 
between potential infiltration and runoff, i.e. 
INF=POTINF-ROF 
Method ETpS() calculates the daily 
potential evapotranspiration rate (ETp) based on the 
Priestly-Taylor method. The surface albedo (ALB) is 
estimated as a weighted average (based on LAI) of the 
albedo of the soil (0.1) and crop (0.2). 
ALB = 0.1 * EXP(-0.7 * LAI) + 0.2 * (1 - EXP(-0.7 * LAI)) 
The average temperature during the day (Tmed) and the 
equilibrium evaporation (EEQ) are calculated as: Tmed = 
0.6 * TMAX + 0.4 * TMIN 
EEQ = SRAD * (4.88E-03 - 4.37E-03 * ALB) * (Tmed + 
29) 
The equilibrium evaporation rate is adjusted by a coefficient 
(f) resulting in the final value of ETp. 
Next, the potential soil evaporation (ESp) and plant 
transpiration (EPp) rates are calculated using the same 
weighting coefficient used for albedo: ESp = ETp * EXP(-
0.7 * LAI) 
EPp = ETp * (1 - EXP(-0.7 * LAI)) 
Method ESaS() calculates the actual daily soil evaporation 
rate (ESa) based on current soil water availability. No 
evaporation occurs if the soil water content is less than the 
wilting point, and the potential evaporation is met if soil 
water content is greater than field capacity. Between the 
wilting point and field capacity, the 
actual evapotranspiration varies linearly between 0.0 and 
the potential evapotranspiration rate: 
IF (SWC < WP) THEN a 
= 0 
ELSEIF (SWC > FC) THEN 
 a = 1 
ELSE 
 a = (SWC - WP)/(FC - WP) 
ENDIF 
ESa = ESp * a 
The potential plant transpiration rate (EPp) is reduced by 
the minimum soil water stress factor (SWFAC1 or 
SWFAC2) to obtain the actual plant transpiration rate 
(EPa) 
Integration 
The integration portion of the soil water class updates the 
value of the soil water content based on the computed 
values of infiltration (INF), soil evaporation (ESa), plant 
transpiration (EPa), and vertical drainage (DRN): SWC = 
SWC + (INF - ESa - EPa - DRN) 
The computed value is limited to a maximum of the 
saturation content (ST) and a minimum of zero. If the 
computed soil water content exceeds saturation, runoff 
rates and soil water content are adjusted. 
IF (SWC>ST) ROF=ROF+(SWCST) 
SWC=ST 
END IF 
An additional adjustment factor 
(SWC_ADJ) is introduced if the computed soil water 
content is less than zero. 
IF (SWC<0) 
SWC_ADJ=SWC_ADJ-SWC 
SWC=0 
END IF 
Cumulative infiltration (TINF), 
evaporation (TESA), transpiration (TEPA), drainage 
(TDRN) and runoff (TROF) are then updated. 
Method STRESS() is then called to compute soil 
water stress factors based on the updated soil water content 
values. The drought stress factor (SWFAC1) is 1.0 
(minimum stress) if the soil water content (SWC) is greater 
than the threshold value computed in the ‘initialization’ 
section (THE). Below the wilting point, maximum stress 
occurs (SWFAC1 = 0.0). Between these ranges, the stress 
factor is linearly distributed. 
IF (SWC < WP) THEN 
 SWFAC1 = 0.0 
ELSEIF (SWC > THE) THEN 
 SWFAC1 = 1.0 
ELSE 
 SWFAC1 = (SWC - WP) / (THE - WP) 
 SWFAC1 = MAX(MIN(SWFAC1, 1.0), 0.0) 
ENDIF 
The thickness of the water table measured from 
the bottom of the soil profile (WTABLE in mm) is 
calculated using the excess water available after field 
capacity is met. The depth to the water table (DWT in mm) 
is then computed. 
WTABLE = (SWC - FC) / (ST - FC) * DP * 10. 
DWT = DP * 10. - WTABLE 
Minimum excess soil water stress (SWFAC2 = 
1.0) occurs when the water table thickness is zero. 
Maximum stress (SWFAC2 = 0.0) occurs when the depth 
to the water table (DWT) is greater than 250 mm 
(STRESS_DEPTH = 250 mm). The excess water stress 
factor is linearly interpolated between these water table 
conditions. 
IF (DWT > STRESS_DEPTH) THEN 
 SWFAC2 = 1.0 
ELSE 
 SWFAC2 = DWT / STRESS_DEPTH 
ENDIF
Output 
Daily values are written to output file SW.OUT. 
Close 
At the end of simulation, method WBAL()is called to check 
that the seasonal water balance is zero, i.e., that changes in 
soil water content are equal to cumulative inflows and 
outflows. A water balance report is written (WBAL.OUT). 
Files SW.OUT and IRRIG.INP are closed. 
3.3 Weather class 
Upon initialization, the weather file (WEATHER.INP) is 
opened. In the rate calculations section, weather values are 
read into the model on a daily basis from WEATHER.INP. 
Table 3 lists the weather input data read. 
The close section is invoked to close the weather input file.
