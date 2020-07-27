#include <Ewma.h>
const int pin1=54,pin2=57,pin3=60,pin4=63;
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
    float sensorValueAvg=0;
  
  //---------------------------------------------------
  //                        Sensor 1
    sensor_volt=0;  
    RS=0; 
    R0=0;  
    sensorValue=0;
    sensorValueAvg=0;
    
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin1); //leitura sensor
    sensorValueAvg = sensorValue/1000.0;              //media simples
    sensorValueAvg = int(filter1.filter(sensorValueAvg)+0.5);     //media movel
    sensor_volt = sensorValueAvg*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;
    R0 = RS/4.4; // Razão descrita no gráfico do data_sheet
   
    Serial.print(R0);Serial.print(" ");

  //---------------------------------------------------
  //                        Sensor 2


    sensor_volt=0;  
    RS=0; 
    R0=0;  
    sensorValue=0;
    sensorValueAvg=0;
    
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin2); //leitura sensor
    sensorValueAvg = sensorValue/1000.0;              //media simples
    sensorValueAvg = int(filter2.filter(sensorValueAvg)+0.5);     //media movel
    sensor_volt = sensorValueAvg*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;
    R0 = RS/4.4; // Razão descrita no gráfico do data_sheet
   
    Serial.print(R0);Serial.print(" ");

  //---------------------------------------------------
  //                        Sensor 3

    sensor_volt=0;  
    RS=0; 
    R0=0;  
    sensorValue=0;
    sensorValueAvg=0;
    
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin3); //leitura sensor
    sensorValueAvg = sensorValue/1000.0;              //media simples
    sensorValueAvg = int(filter3.filter(sensorValueAvg)+0.5);     //media movel
    sensor_volt = sensorValueAvg*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;
    R0 = RS/4.4; // Razão descrita no gráfico do data_sheet
   
    Serial.print(R0);Serial.print(" ");

  //---------------------------------------------------
  //                        Sensor 4

    sensor_volt=0;  
    RS=0; 
    R0=0;  
    sensorValue=0;
    sensorValueAvg=0;
    
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin4); //leitura sensor
    sensorValueAvg = sensorValue/1000.0;              //media simples
    sensorValueAvg = int(filter4.filter(sensorValueAvg)+0.5);     //media movel
    sensor_volt = sensorValueAvg*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;
    R0 = RS/4.4; // Razão descrita no gráfico do data_sheet
   
    Serial.print(R0);Serial.print(" ");

  //---------------------------------------------------

  Serial.println();
 
}
