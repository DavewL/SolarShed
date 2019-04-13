#include "ModbusMaster.h"
#include "defines.h"
#include "Globals.h"


// instantiate ModbusMaster object as slave ID 1
ModbusMaster node(1);

  
void initTracer(void){
    node.begin(115200);
    node.disableTXpin();
    //node.enableDebug();
	delay(100);
	Serial1.begin(115200);
}

//read batt voltage
bool tracerBattVoltRead(void){
	uint8_t result;
	//uint16_t data[10];
	bool readSuccess = false;
	result = node.readInputRegisters(0x331A,1);
	if (result == node.ku8MBSuccess) {
		tracerBattVoltage = (double)node.getResponseBuffer(0) / 100.0f;
		Serial.print(tracerBattVoltage);
		Serial.println("");
		readSuccess = true;
	}
	else {
		readSuccess = false;
	}
	return readSuccess;
}

//read batt current
bool tracerBattCurrRead(void){
	uint8_t result;
	bool readSuccess = false;
	result = node.readInputRegisters(0x331B,2);
	if (result == node.ku8MBSuccess) {
		tracerBattCurrent = (double)(node.getResponseBuffer(1) << 16 | node.getResponseBuffer(0)) / 100.0f;
		Serial.print(tracerBattCurrent);
		Serial.println("");

		readSuccess = true;
	}
	else {
		readSuccess = false;
	}
	return readSuccess;
}

//read PV voltage
bool tracerPvVoltRead(void){
	uint8_t result;
	bool readSuccess = false;
	result = node.readInputRegisters(0x3100,1);
	if (result == node.ku8MBSuccess) {
		pVvoltage = (double)node.getResponseBuffer(0) / 100.0f;
		Serial.print(pVvoltage);
		Serial.println("");
		readSuccess = true;
	}
	else {
		readSuccess = false;
	}
	return readSuccess;
}

//read PV current
bool tracerPvCurrRead(void){
	uint8_t result;
	bool readSuccess = false;
	result = node.readInputRegisters(0x3101,1);
	if (result == node.ku8MBSuccess) {
		pVcurrent = (double)node.getResponseBuffer(0) / 100.0f;
		Serial.print(pVcurrent);
		Serial.println("");
		readSuccess = true;
	}
	else {
		readSuccess = false;
	}
	return readSuccess;
}

//read Load Current
bool tracerLoadCurrRead(void){
	uint8_t result;
	bool readSuccess = false;
	result = node.readInputRegisters(0x310D,1);
	if (result == node.ku8MBSuccess) {
		heaterCurrent = (double)node.getResponseBuffer(0) / 100.0f;
		Serial.print(heaterCurrent);
		Serial.println("");
		readSuccess = true;
	}
	else {
		readSuccess = false;
	}
	return readSuccess;
}

//read Temperature
bool tracerInsideTemp(void){
	uint8_t result;
	bool readSuccess = false;
	result = node.readInputRegisters(0x3110,1);
	if (result == node.ku8MBSuccess) {
		insideAmbientTemp = (double)(int16_t)node.getResponseBuffer(0) / 100.0f;
		Serial.print(insideAmbientTemp);
		Serial.println("");
		readSuccess = true;
	}
	else {
		readSuccess = false;
	}
	return readSuccess;
}

bool tracerBattSOC(void){
	uint8_t result;
	bool readSuccess = false;
	result = node.readInputRegisters(0x311A,1);
	if (result == node.ku8MBSuccess) {
		battPackSOC = (double)node.getResponseBuffer(0) / 100.0f;
		Serial.print(battPackSOC);
		Serial.println("");
		readSuccess = true;
	}
	else {
		readSuccess = false;
	}
	return readSuccess;
}

bool tracerSetLoadState(int state){
	int result;
	result = node.writeSingleCoil(0x2,(uint8_t)state);
	if (result == 0) {
		return true;
	}
	else{
		return false;
	}
}

	// do something with data if read is successful
	/*
	if (result == node.ku8MBSuccess) {
		Serial.print("Success, Received data: ");
		for (j = 0; j < 1; j++) {
			data[j] = node.getResponseBuffer(j);
			
			Serial.print(data[j], HEX);
			Serial.print(" ");
		}
		Serial.println("");
	} else {
		Serial.print("Failed, Response Code: ");
		Serial.print(result, HEX); 
		Serial.println("");
		delay(5000); //if failed, wait for bit longer, before retrying!
	}
	*/

