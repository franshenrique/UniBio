#include <DHT.h>
#include <RTClib.h>
#include <Ewma.h>

Ewma filterRtc(0.01);

DHT dht1(9,DHT11);
DHT dht2(7,DHT11);
DHT dht3(5,DHT11);
DHT dht4(3,DHT11);

RTC_DS3231 rtc;
void setup()
{
    Serial.begin(9600);
    dht1.begin();
        rtc.begin();
    dht2.begin();
    dht3.begin();
    dht4.begin();
}
void loop()
{
    Serial.print(filterRtc.filter(rtc.getTemperature())-4);Serial.print(" ");
    Serial.print(dht1.readTemperature()-2.5);Serial.print(" ");
    Serial.print(dht2.readTemperature()-1.3);Serial.print(" ");
    Serial.print(dht3.readTemperature()-1.9);Serial.print(" ");
    Serial.print(dht4.readTemperature()-2.3);Serial.print(" ");
    Serial.println();
    delay(200);
}
