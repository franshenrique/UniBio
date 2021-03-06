#include <Ewma.h>
const int pin1=55,pin2=58,pin3=61,pin4=64;
const float alpha=0.01;
Ewma filter1(alpha),filter2(alpha),filter3(alpha),filter4(alpha);
void setup() { 
    Serial.begin(9600); 
} 
  
void loop() {
    float sensor_volt=0;  
    float RS=0; 
    float R0=0;  
    long sensorValue=0; 
  
  //---------------------------------------------------
  //                        Sensor 1
    sensor_volt=0;  
    RS=0; 
    R0=0;  
    sensorValue=0; 
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin1);//leitura sensor
    sensorValue = int(filter1.filter(sensorValue/1000)); //media simples e media movel
   
    sensor_volt = float(sensorValue)*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;  
    R0 = RS/3.6; // Razão descrita no gráfico do data_sheet
   
    Serial.print(R0);Serial.print(" ");

  //---------------------------------------------------
  //                        Sensor 2


    sensor_volt=0;  
    RS=0; 
    R0=0;  
    sensorValue=0;
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin2);//leitura sensor
    sensorValue = int(filter2.filter(sensorValue/1000)); //media simples e media movel
   
    sensor_volt = float(sensorValue)*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;  
    R0 = RS/3.6; // Razão descrita no gráfico do data_sheet
   
    Serial.print(R0);Serial.print(" ");

  //---------------------------------------------------
  //                        Sensor 3

    sensor_volt=0;  
    RS=0; 
    R0=0;  
    sensorValue=0;
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin3);//leitura sensor
    sensorValue = int(filter3.filter(sensorValue/1000)); //media simples e media movel
   
    sensor_volt = float(sensorValue)*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;  
    R0 = RS/3.6; // Razão descrita no gráfico do data_sheet
   
    Serial.print(R0);Serial.print(" ");

  //---------------------------------------------------
  //                        Sensor 4

    sensor_volt=0;  
    RS=0; 
    R0=0;  
    sensorValue=0; 
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin4);//leitura sensor
    sensorValue = int(filter4.filter(sensorValue/1000)); //media simples e media movel
   
    sensor_volt = float(sensorValue)*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;  
    R0 = RS/3.6; // Razão descrita no gráfico do data_sheet
   
    Serial.print(R0);Serial.print(" ");

  //---------------------------------------------------

  Serial.println();
 
}
