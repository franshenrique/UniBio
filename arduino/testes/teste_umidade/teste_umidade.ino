#include <DHT.h>

DHT dht1(9,DHT11);
DHT dht2(7,DHT11);
DHT dht3(5,DHT11);
DHT dht4(3,DHT11);

void setup()
{
    Serial.begin(9600);
    dht1.begin();
    dht2.begin();
    dht3.begin();
    dht4.begin();
}
void loop()
{
    Serial.print(dht1.readHumidity());Serial.print(" ");
    Serial.print(dht2.readHumidity()+6);Serial.print(" ");
    Serial.print(dht3.readHumidity()-2);Serial.print(" ");
    Serial.print(dht4.readHumidity()+4);Serial.println(" ");
    delay(200);
}
