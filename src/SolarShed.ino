/*
 * Project SolarShed
 * Description:
 * Author:
 * Date:
 */
#include "Particle.h"
#include <carloop.h>
//#include <ITEADLIB_Nextion.h>
#include "CANrec.h"
#include "CANinit.h"
#include "Rev3Messages.h"
#include "Tracer_Modbus.h"

SYSTEM_MODE(AUTOMATIC);

int chargeStatus;
int BMSstatus;
int critDischAlarm;
int warningFlags;
int cellsDeltaV;
int underTempChargeStatus;
int underTempDischargeStatus;
int overTemperatureStatus;
int PCBAoverTempStatus;
int battTerminalOverTempStatus;
int overVoltageStatus;
int underVoltageStatus;
int overCurrentCharge;
int overCurrentDischarge;
int cellDeltaTempStatus;
int ModuleLostState;
int contactorMain;
int contactorCharge;
int module1MaxMvolts;
int module1MinMvolts;
int module2MaxMvolts;
int module2MinMvolts;
int module3MaxMvolts;
int module3MinMvolts;
int module4MaxMvolts;
int module4MinMvolts;

int heaterStatus;

int keySignalStatus;
int rechargeState;

int SparkNetOk;

int onceThrough;   //init tasks in periodic scheduler

double BMSchargeCurrSetpoint;
double BMSchargeVoltSetpoint;

unsigned int BMSstatusWord;


double pVvoltage = 0;
double pVcurrent = 0;
double pVpower = 0;
int iD = 1;
double insideAmbientTemp = 0.0;
double heaterCurrent = 0;
int heaterRelay = 0;
double tracerBattVoltage;
double tracerBattCurrent;
double tracerBattPower;
double heaterPower;

double outsideAmbientTemp = 0;
double battVoltage = 0;
double battCurrent = 0;
double battMaxTemp = 0;
double battMinTemp = 0;
double batt1Cell1V = 0;
double batt1Cell2V = 0;
double batt1Cell3V = 0;
double batt1Cell4V = 0;
double batt2Cell1V = 0;
double batt2Cell2V = 0;
double batt2Cell3V = 0;
double batt2Cell4V = 0;
double batt3Cell1V = 0;
double batt3Cell2V = 0;
double batt3Cell3V = 0;
double batt3Cell4V = 0;
double batt4Cell1V = 0;
double batt4Cell2V = 0;
double batt4Cell3V = 0;
double batt4Cell4V = 0;
double battPackSOC = 0.0;
double batt1SOC = 0.0;
double batt2SOC = 0.0;
double batt3SOC = 0.0;
double batt4SOC = 0.0;
double highCellV = 0.0;
double lowCellV = 0.0;

int heaterControl(String);

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  initCAN();
  initTracer();
  
  Particle.function("Heater_Control_on_off",heaterControl);

  Particle.variable("PV_Voltage", pVvoltage);
  Particle.variable("PV_Current", pVcurrent);
  Particle.variable("PV_Power", pVpower);
  Particle.variable("PV_ID", iD);
  Particle.variable("Inside_Temperature", insideAmbientTemp);
  Particle.variable("Outside_Temperature", outsideAmbientTemp);
  Particle.variable("Heater_Current", heaterCurrent);
  Particle.variable("Heater_Power",heaterPower);
  Particle.variable("Battery_Voltage",tracerBattVoltage);
  Particle.variable("Battery_Current",tracerBattCurrent);
  Particle.variable("Battery_Charge_Power",tracerBattPower);
  Particle.variable("Battery_SOC",battPackSOC);
  Particle.variable("Battery1SOC",batt1SOC);
  Particle.variable("Battery2SOC",batt2SOC);
  Particle.variable("Battery3SOC",batt3SOC);
  Particle.variable("Battery4SOC",batt4SOC);
  Particle.variable("Battery_Max_Temp",battMaxTemp);
  Particle.variable("Battery_Min_Temp",battMinTemp);
}

void loop() {
  static unsigned long millisPrev = 0;
  static unsigned int readState = 0;
  unsigned long millisNow = millis();
  unsigned long deltaMillis = millisNow-millisPrev;
  
  canReceiveMessage();

  if (deltaMillis > 2000) {
    switch (readState){
      case 0:
        if (tracerBattVoltRead() == false){
          Serial.println("batt volt read failed");
          delay(3000);
        }
        readState++;
        break;

      case 1:
        if (tracerBattCurrRead() == false){
          Serial.println("batt cur read failed");
          delay(3000);
        }
        readState++;
        break;

      case 2:
        if (tracerPvVoltRead() == false){
          Serial.println("PV volt read failed");
          delay(3000);
        }
        readState++;
        break;
      case 3:
        if (tracerPvCurrRead() == false){
          Serial.println("PV curr read failed");
          delay(3000);
        }
        readState++;
        break;
      case 4:
        if (tracerLoadCurrRead() == false){
          Serial.println("load read failed");
          delay(3000);
        }
        readState++;
        break;
      case 5:
        if (tracerInsideTemp() == false){
          Serial.println("temperature read failed");
          delay(3000);
        }
        readState++;
        break;

      case 6:
        if (tracerBattSOC() == false){
          Serial.println("SOC read failed");
          delay(3000);
        }
        readState = 0;
        break;

      default:
        readState = 0;
        break;
    }
    pVpower = pVcurrent * pVvoltage;
    tracerBattPower = tracerBattCurrent * tracerBattVoltage;
    heaterPower = tracerBattVoltage * heaterCurrent;
    millisPrev = millisNow;
  }
}

int heaterControl(String loadState){
  static int setState = 0;
  if (loadState == "on"){
    setState = 1;
  }
  else if (loadState == "off"){
    setState = 0;
  }
  else return -1;

  if (tracerSetLoadState(setState) == true){
    return 1;
  }
  else return -1;

}