/*
 * Photoresistor
 */
const int pResistor = A2;
int lum_value;

void setup() {
  Serial.begin(9600);
  pinMode(pResistor, INPUT);
  Serial.println("READY");
}

void loop() {}

/*************************************************************************************************************
 * IR light control
 *************************************************************************************************************/
#include <boarddefs.h>
#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremote.h>
#include <IRremoteInt.h>

int TRANS_PIN =  3; 
IRsend irsend;

const int freq = 38;

//These are the data for my particular led strip
const unsigned int OnOff[67] = {8900,4550, 500,600, 550,550, 550,600, 550,600, 500,600, 550,550, 550,600, 550,600, 500,1700, 550,1700, 500,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,600, 550,1700, 500,600, 500,600, 550,600, 500,1700, 550,600, 500,600, 500,1750, 500,600, 550,1700, 500,1700, 550,1700, 500,600, 500,1700, 550};
const unsigned int  White[67] = {9000,4500, 550,550, 550,600, 550,550, 550,600, 550,550, 550,600, 550,550, 550,600, 550,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,1700, 550,550, 550,1700, 550,1700, 500,600, 550,550, 550,600, 550,1700, 500,600, 550,1700, 500,550, 550,600, 550,1700, 500,1700, 550,1700, 500,600, 550,1700, 500};  // NEC FF629D
const unsigned int  BrightPlus[67] = {9000,4500, 600,550, 550,600, 500,600, 550,600, 500,600, 550,600, 500,600, 550,600, 500,1700, 550,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,1700, 550,600, 500,600, 550,600, 550,600, 500,600, 550,600, 500,600, 550,600, 500,1700, 550,1700, 500,1700, 550,1700, 550,1650, 550};  // NEC FFE01F
const unsigned int colorChange[67] = {8950,4500, 550,600, 500,600, 550,600, 500,600, 550,600, 500,600, 550,600, 500,600, 550,1700, 500,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,1700, 500,1700, 550,1700, 500,600, 550,600, 500,1700, 550,600, 500,600, 550,600, 500,600, 550,600, 500,1700, 500,1700, 550,600, 500,1700, 550,1700, 500,1700, 500,1700, 550};  // NEC FF906F
const unsigned int  B_MINUS[67] = {8950,4500, 550,600, 500,600, 550,550, 550,600, 550,550, 550,600, 550,550, 550,600, 550,1700, 500,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,1700, 500,1700, 550,550, 550,600, 550,550, 550,600, 550,1700, 500,600, 550,550, 550,600, 550,1700, 500,1700, 550,1700, 500,1700, 500,600, 550,1700, 500};  // NEC FFC23D
//const unsigned int  hell[67] ={8950,4250,750,350,750,350,700,400,750,350,750,350,700,400,700,400,700,450,600,1600,600,1600,600,1650,550,1650,600,1600,600,1650,500,1700,550,1650,550,550,550,550,550,550,550,1700,500,600,500,550,550,600,500,600,500,1700,500,1700,550,1650,550,550,550,1700,500,1700,500,1700,550,1650,550};
//const unsigned int  end_d[67] = {8950,4500, 550,600, 500,600, 550,600, 500,600, 550,600, 500,600, 550,600, 500,600, 550,1650, 550,1700, 500,1700, 550,1700, 500,1700, 500,1700, 550,1700, 500,1700, 550,1700, 500,600, 550,1700, 500,1700, 500,600, 550,600, 500,600, 550,600, 500,600, 550,1700, 500,600, 550,600, 500,1700, 500,1700, 550,1700, 500,1700, 550};  // NEC FFB04F

//void sendNether(){ irsend.sendRaw(hell, sizeof(OnOff),freq ); }
//void sendEnd(){ irsend.sendRaw(end_d, sizeof(OnOff),freq ); }
void toggleLights(){ irsend.sendRaw(OnOff, sizeof(OnOff), freq); }
void sendBrightPlus(){ irsend.sendRaw(BrightPlus, sizeof(BrightPlus),freq); }
void sendBrightMinus(){ irsend.sendRaw(B_MINUS, sizeof(B_MINUS),freq); }
void sendWhite(){ irsend.sendRaw(White, sizeof(White),freq); }
void sendColorChange(){ irsend.sendRaw(colorChange, sizeof(colorChange),freq); }

/*************************************************************************************************************
 * Temperature sensor
 *************************************************************************************************************/
int val;
int tempPin = A1;

/*
 * Return the value from `tempPin` converted to degree C
 */
float getAnalogTemp() {
  // Reading twice provides a more accurate reading
  val = analogRead(tempPin);
  return (analogRead(tempPin)*4.9)/10;
}


int getLightLevel() {
  lum_value = analogRead(pResistor);
  return analogRead(pResistor);
}

void printAllSensorData() {
  Serial.println(String(getLightLevel()) + ";"  + String(getAnalogTemp()) + ";");
}


/**
 * Handle serial input
 */
void serialEvent() {
  while (Serial.available()) {
    const char inChar = (char)Serial.read();

    switch (inChar)
    {
      case 'O':
        toggleLights();
        break;
      case 'I':
        sendBrightPlus();
        break;
      case 'D':
        sendBrightMinus();
        break;
      case 'W':
        sendWhite();
        break;
      case 'C':
        sendColorChange();
        break;
      case 'T':
        Serial.println(getAnalogTemp());
        break;
      case 'L':
        Serial.println(getLightLevel());
        break;
      case 'A':
        printAllSensorData();
        break;
      default:
        break;
    }
  }
}