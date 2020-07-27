#include <Ewma.h>

const int pin1=56,pin2=59,pin3=62,pin4=65;
Ewma filter1(0.01),filter2(0.01),filter3(0.01),filter4(0.01);
void setup()
{
    Serial.begin(9600);
    
}

void loop()
{
    long soma=0;
    float sensorValueAvg=0;
    int sensorValue;
    int kpa=0;
    
//------------------------------------------
//                Sensor 1

    for(int i=0;i<1000;i++)
        soma+=analogRead(pin1);
    soma=soma/1000;
    sensorValueAvg=filter1.filter(soma);
    sensorValueAvg=(sensorValueAvg - 122) * (1200- 0) / (922- 122) + 0;
    Serial.print(sensorValueAvg);
    Serial.print(" ");

//------------------------------------------
//                Sensor 2

    soma=0;
    sensorValueAvg=0;
    kpa=0;
    for(int i=0;i<1000;i++)
        soma+=analogRead(pin2);
    sensorValueAvg=soma/1000.0;
    sensorValue=int(filter2.filter(sensorValueAvg)+0.5);
    kpa=map(sensorValue,122,922,0,1200);
    kpa=constrain(kpa,0,1200);
    Serial.print(kpa);
    Serial.print(" ");

//------------------------------------------
//                Sensor 3

    soma=0;
    sensorValueAvg=0;
    kpa=0;
    for(int i=0;i<1000;i++)
        soma+=analogRead(pin3);
    sensorValueAvg=soma/1000.0;
    sensorValue=int(filter3.filter(sensorValueAvg)+0.5);
    kpa=map(sensorValue,122,922,0,1200);
    kpa=constrain(kpa,0,1200);
    Serial.print(kpa);
    Serial.print(" ");

//------------------------------------------
//                Sensor 4

    soma=0;
    sensorValueAvg=0;
    kpa=0;
    for(int i=0;i<1000;i++)
        soma+=analogRead(pin4);
    sensorValueAvg=soma/1000.0;
    sensorValue=int(filter4.filter(sensorValueAvg)+0.5);
    kpa=map(sensorValue,122,922,0,1200);
    kpa=constrain(kpa,0,1200);
    Serial.print(kpa);
    Serial.print(" ");


    
    Serial.println();

    
    delay(200);
}
