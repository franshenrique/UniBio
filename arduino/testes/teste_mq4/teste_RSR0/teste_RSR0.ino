#include <Ewma.h>
const int PROGMEM pin1=54,pin2=57,pin3=60,pin4=63;
const float PROGMEM alpha=0.01;
const float PROGMEM R0_1=9.07,R0_2=13.45,R0_3=9.07,R0_4=12.69;
Ewma filter1(alpha),filter2(alpha),filter3(alpha),filter4(alpha);
void setup() { 
    Serial.begin(9600); 
} 
  
void loop() {
    float sensor_volt=0;  
    float RS=0; 
    float RSR0=0;  
    int sensorValue=0; 
  
  //---------------------------------------------------
  //                        Sensor 1
    sensor_volt=0;  
    RS=0; 
    RSR0=0;  
    sensorValue=0; 
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin1);//leitura sensor
    sensorValue = int(filter1.filter(sensorValue/1000)); //media simples e media movel
   
    sensor_volt = float(sensorValue)*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;  
    RSR0=RS/R0_1;
    Serial.print(RSR0);Serial.print(" ");

  //---------------------------------------------------
  //                        Sensor 2


    sensor_volt=0;  
    RS=0; 
    RSR0=0;  
    sensorValue=0;
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin2);//leitura sensor
    sensorValue = int(filter2.filter(sensorValue/1000)); //media simples e media movel
   
    sensor_volt = float(sensorValue)*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;  
    RSR0=RS/R0_2;
    Serial.print(RSR0);Serial.print(" ");

  //---------------------------------------------------
  //                        Sensor 3

    sensor_volt=0;  
    RS=0; 
    RSR0=0;  
    sensorValue=0;
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin3);//leitura sensor
    sensorValue = int(filter3.filter(sensorValue/1000)); //media simples e media movel
   
    sensor_volt = float(sensorValue)*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;  
    RSR0=RS/R0_3;
    Serial.print(RSR0);Serial.print(" ");;

  //---------------------------------------------------
  //                        Sensor 4

    sensor_volt=0;  
    RS=0; 
    RSR0=0;  
    sensorValue=0; 
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin4);//leitura sensor
    sensorValue = int(filter4.filter(sensorValue/1000)); //media simples e media movel
   
    sensor_volt = float(sensorValue)*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;  
    RSR0=RS/R0_4;
    Serial.print(RSR0);Serial.print(" ");

  //---------------------------------------------------

  Serial.println();
 
}
