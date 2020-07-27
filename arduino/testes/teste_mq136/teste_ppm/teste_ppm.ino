#include <Ewma.h>

const float  alpha=0.01;
Ewma filter1(alpha),filter2(alpha),filter3(alpha),filter4(alpha);
const int pin1=55,pin2=58,pin3=61,pin4=64;
const float R0_1=45.50,R0_2=41.63,R0_3=38.35,R0_4=41.63;
const float m=-0.2715,b=-0.22915;

void setup() { 
    Serial.begin(9600); 
} 
  
void loop() {
    float sensor_volt=0;  
    float RS=0; 
    float ratio=0;  
    long sensorValue=0;
    float sensorValueAvg=0;
    float ppm=0; 
  
  //---------------------------------------------------
  //                        Sensor 1
    sensor_volt=0;  
    RS=0; 
    ratio=0;  
    sensorValue=0;
    sensorValueAvg=0;
    ppm=0 ;
    
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin1); //leitura sensor
    sensorValueAvg = sensorValue/1000.0;              //media simples
    sensorValueAvg = filter1.filter(sensorValueAvg);     //media movel
    sensor_volt = sensorValueAvg*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;
//    Serial.print(RS);Serial.print(" ");
    ratio=RS/R0_1;
    if(ratio<0)ratio=0;
    ppm=pow(10,(log10(ratio) - b) / m);
    //ppm=constrain(ppm,2,10000);
    Serial.print(ppm);Serial.print(" ");

//  //---------------------------------------------------
//  //                        Sensor 2
//
//
//    sensor_volt=0;  
    RS=0; 
    ratio=0;  
    sensorValue=0;
    sensorValueAvg=0;
    ppm=0 ;
    
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin2); //leitura sensor
    sensorValueAvg = sensorValue/1000.0;              //media simples
    sensorValueAvg = filter2.filter(sensorValueAvg);     //media movel
    sensor_volt = sensorValueAvg*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;
//    Serial.print(RS);Serial.print(" ");
    ratio=RS/R0_2;
    if(ratio<0)ratio=0;
    ppm=pow(10,(log10(ratio) - b) / m);
    //ppm=constrain(ppm,2,10000);
    Serial.print(ppm);Serial.print(" ");
//
//  //---------------------------------------------------
//  //                        Sensor 3
    
    sensor_volt=0;  
    RS=0; 
    ratio=0;  
    sensorValue=0;
    sensorValueAvg=0;
    ppm=0 ;
    
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin3); //leitura sensor
    sensorValueAvg = sensorValue/1000.0;              //media simples
    sensorValueAvg = filter3.filter(sensorValueAvg);     //media movel
    sensor_volt = sensorValueAvg*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;
//    Serial.print(RS);Serial.print(" ");
    ratio=RS/R0_3;
    if(ratio<0)ratio=0;
    ppm=pow(10,(log10(ratio) - b) / m);
    //ppm=constrain(ppm,2,10000);
    Serial.print(ppm);Serial.print(" ");
//
//  //---------------------------------------------------
//  //                        Sensor 4
//
    sensor_volt=0;  
    RS=0; 
    ratio=0;  
    sensorValue=0;
    sensorValueAvg=0;
    ppm=0 ;
    
    for(int x = 0 ; x < 1000 ; x++) 
        sensorValue = sensorValue + analogRead(pin4); //leitura sensor
    sensorValueAvg = sensorValue/1000.0;              //media simples
    sensorValueAvg = filter4.filter(sensorValueAvg);     //media movel
    sensor_volt = sensorValueAvg*(5.0/1023.0); 
    RS = (5.0-sensor_volt)/sensor_volt;
//    Serial.print(RS);Serial.print(" ");
    ratio=RS/R0_4;
    if(ratio<0)ratio=0;
    ppm=pow(10,(log10(ratio) - b) / m);
    //ppm=constrain(ppm,2,10000);
    Serial.print(ppm);Serial.print(" ");

    
//  //---------------------------------------------------

  Serial.println();
 
}
