#include <OneWire.h>
#include <DallasTemperature.h>
#include <RTClib.h>
#include <EwmaT.h>

RTC_DS3231 rtc;

OneWire onewire1(8);
OneWire onewire2(6);
OneWire onewire3(4);
OneWire onewire4(2);
DallasTemperature s1(&onewire1);
DallasTemperature s2(&onewire2);
DallasTemperature s3(&onewire3);
DallasTemperature s4(&onewire4);
EwmaT <float> filter1(0.01,100);
EwmaT <float> filter2(0.01,100);
EwmaT <float> filter3(0.01,100);
EwmaT <float> adcFilter4(0.01,100);
void setup()
{
    Serial.begin(9600);
    rtc.begin();
    s1.begin();
    s2.begin();
    s3.begin();
    s4.begin();
    
}

void loop()
{
    s1.requestTemperatures();
    s2.requestTemperatures();
    s3.requestTemperatures();
    s4.requestTemperatures();
    Serial.print(rtc.getTemperature()-3);
    Serial.print(" ");
    Serial.print(filter1.filter(s1.getTempCByIndex(0)-0));
    Serial.print(" ");
    Serial.print(s2.getTempCByIndex(0)-0.2);
    Serial.print(" ");
    Serial.print(s3.getTempCByIndex(0)+1.3);
    Serial.print(" ");
    Serial.print(s4.getTempCByIndex(0)-0.4);
    Serial.println(" ");
    delay(2000);
    
}
