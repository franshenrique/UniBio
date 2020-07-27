#include "MHZ19.h"
#include <SoftwareSerial.h>

SoftwareSerial s1(13,12),s2(11,10),s3(67,66),s4(69,68);
MHZ19 m1,m2,m3,m4;
char version[20];
void setup() 
{
    Serial.begin(9600);
    s1.begin(9600);
    s2.begin(9600);
    s3.begin(9600);
    s4.begin(9600);
    s1.listen();
    m1.begin(s1);
//    m1.calibrateZero();
//    Serial.println(m1.getABC());
    s2.listen();
    m2.begin(s2);
//    m2.calibrateZero();
    s3.listen();
    m3.begin(s3);
//    m3.calibrateZero();
    s4.listen();
    m4.begin(s4);
//    m4.calibrateZero();
    

}

void loop() {
    s1.listen();
    Serial.print(m1.getCO2());
    Serial.print(" ");
    s2.listen();
    Serial.print(m2.getCO2());
    Serial.print(" ");
    s3.listen();
    Serial.print(m3.getCO2());
    Serial.print(" ");
    s4.listen();
    Serial.println(m4.getCO2());
    delay(2000);
}
