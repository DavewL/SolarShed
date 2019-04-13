//#include "defines.h"
//#include "application.h"

//----------Externed Globals-----------------------------
extern double battPackSOC;
extern double battVoltage;
extern double battCurrent;
extern double maxDischargeCurrent;
extern double maxRegenCurrent;
extern int chargeStatus;
extern int BMSstatus;
extern int critDischAlarm;
extern int warningFlags;
extern double battMinTemp;
extern double battMaxTemp;
extern double batt1Cell2V;
extern double batt1Cell3V;
extern double batt1Cell4V;
extern double batt2Cell1V;
extern double batt2Cell2V;
extern double batt2Cell3V;
extern double batt1Cell1V;
extern double batt2Cell4V;
extern double batt3Cell1V;
extern double batt3Cell2V;
extern double batt3Cell3V;
extern double batt3Cell4V;
extern double batt4Cell1V;
extern double batt4Cell2V;
extern double batt4Cell3V;
extern double batt4Cell4V;
extern int moduleMaxMvolts;
extern int moduleMinMvolts;
extern int cellsDeltaV;
extern int battSN;
extern int underTempChargeStatus;
extern int underTempDischargeStatus;
extern int overTemperatureStatus;
extern int PCBAoverTempStatus;
extern int battTerminalOverTempStatus;
extern int overVoltageStatus;
extern int underVoltageStatus;
extern int overCurrentCharge;
extern int overCurrentDischarge;
extern int cellDeltaTempStatus;
extern int ModuleLostState;
extern int contactorMain;
extern int contactorCharge;

extern int heaterStatus;

extern int keySignalStatus;
extern int rechargeState;


extern int SparkNetOk;

extern int onceThrough;   //init tasks in periodic scheduler

extern float BMSchargeCurrSetpoint;
extern float BMSchargeVoltSetpoint;

extern unsigned int BMSstatusWord;

extern int module1MaxMvolts;
extern int module1MinMvolts;
extern int module2MaxMvolts;
extern int module2MinMvolts;
extern int module3MaxMvolts;
extern int module3MinMvolts;
extern int module4MaxMvolts;
extern int module4MinMvolts;

extern double pVvoltage;
extern double pVcurrent;
extern double pVpower;

extern double insideAmbientTemp;
extern double heaterCurrent;
extern double tracerBattVoltage;
extern double tracerBattCurrent;
extern double tracerBattPower;
extern double heaterPower;
