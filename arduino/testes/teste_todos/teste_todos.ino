
#include "Biodigestor.h"

#define sensor 1
//1->dht_t
//2->dht_h
//3->ds18
//4->pressao
//5->mq136
//6->mq4
//7->mhz

Biodigestor bd1,bd2,bd3,bd4;

Pinos pn1,pn2,pn3,pn4;

Leitura leituras1[20],leituras2[20],leituras3[20],leituras4[20],media1,media2,media3,media4;


Calibragem cb1,cb2,cb3,cb4;


void setup()
{
    pn1.pin_dht=5;
    pn1.pin_ds18=40;
    pn1.pin_pressao=56;
    pn1.pin_mq136=55;
    pn1.pin_mq4=54;
    pn1.pin_mhz_rx=12;
    pn1.pin_mhz_tx=13;
    
    pn2.pin_dht=4;
    pn2.pin_ds18=41;
    pn2.pin_pressao=59;
    pn2.pin_mq136=58;
    pn2.pin_mq4=57;
    pn2.pin_mhz_rx=10;
    pn2.pin_mhz_tx=11;
    
    pn3.pin_dht=3;
    pn3.pin_ds18=42;
    pn3.pin_pressao=62;
    pn3.pin_mq136=61;
    pn3.pin_mq4=60;
    pn3.pin_mhz_rx=14;
    pn3.pin_mhz_tx=15;
    
    pn4.pin_dht=2;
    pn4.pin_ds18=43;
    pn4.pin_pressao=65;
    pn4.pin_mq136=64;
    pn4.pin_mq4=63;
    pn4.pin_mhz_rx=16; 
    pn4.pin_mhz_tx=17;

    cb2.temp_gas=1.37;
    cb3.temp_gas=0.27;
    
    bd1.begin(1,10,pn1,cb1);
    bd2.begin(2,10,pn2,cb2);
    bd3.begin(3,10,pn3,cb3);
    bd4.begin(4,10,pn4,cb4);
    
    Serial.begin(9600);
    
}
void loop()
{
    unsigned long soma=0;
    double soma_f=0;
    for(int i=0;i<19;i++)
        leituras1[i]=leituras1[i+1];
    leituras1[19]=bd1.get_leitura();
    for(int i=0;i<19;i++)
        leituras2[i]=leituras2[i+1];
    leituras2[19]=bd2.get_leitura();
    for(int i=0;i<19;i++)
        leituras3[i]=leituras3[i+1];
    leituras3[19]=bd3.get_leitura();
    for(int i=0;i<19;i++)
        leituras4[i]=leituras4[i+1];
    leituras4[19]=bd4.get_leitura();
    switch(sensor)
    {
        case 1:
            soma_f=0;
            for(int i=0;i<20;i++)
                soma_f+=leituras1[i].temp_gas;
            Serial.print("bd1:");
            Serial.print(soma_f/20);
            Serial.print(",");
            soma_f=0;
            for(int i=0;i<20;i++)
                soma_f+=leituras2[i].temp_gas;
            Serial.print("bd2:");
            Serial.print(soma_f/20);
            Serial.print(",");
            soma_f=0;
            for(int i=0;i<20;i++)
                soma_f+=leituras3[i].temp_gas;
            Serial.print("bd3:");
            Serial.print(soma_f/20);
            Serial.print(",");
            soma_f=0;
            for(int i=0;i<20;i++)
                soma_f+=leituras4[i].temp_gas;
            Serial.print("bd4:");
            Serial.println(soma_f/20);
        break;
        case 2:
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras1[i].umidade;
            Serial.print("bd1:");
            Serial.print(soma/20);
            Serial.print(",");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras2[i].umidade;
            Serial.print("bd2:");
            Serial.print(soma/20);
            Serial.print(",");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras3[i].umidade;
            Serial.print("bd3:");
            Serial.print(soma/20);
            Serial.print(",");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras4[i].umidade;
            Serial.print("bd4:");
            Serial.println(soma/20);
        break;
        case 3:
            soma_f=0;
            for(int i=0;i<20;i++)
                soma_f+=leituras1[i].temp_biomassa;
            Serial.print("bd1 = ");
            Serial.print(soma_f/20);
            Serial.print(" , ");
            soma_f=0;
            for(int i=0;i<20;i++)
                soma_f+=leituras2[i].temp_biomassa;
            Serial.print("bd2 = ");
            Serial.print(soma_f/20);
            Serial.print(" , ");
            soma_f=0;
            for(int i=0;i<20;i++)
                soma_f+=leituras3[i].temp_biomassa;
            Serial.print("bd3 = ");
            Serial.print(soma_f/20);
            Serial.print(" , ");
            soma_f=0;
            for(int i=0;i<20;i++)
                soma_f+=leituras4[i].temp_biomassa;
            Serial.print("bd4 = ");
            Serial.println(soma_f/20);

        break;
        case 4:
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras1[i].pressao;
            Serial.print("bd1 = ");
            Serial.print(soma/20);
            Serial.print(" , ");
           soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras2[i].pressao;
            Serial.print("bd2 = ");
            Serial.print(soma/20);
            Serial.print(" , ");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras3[i].pressao;
            Serial.print("bd3 = ");
            Serial.print(soma/20);
            Serial.print(" , ");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras4[i].pressao;
            Serial.print("bd4 = ");
            Serial.println(soma/20);
        break;
        case 5:
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras1[i].ppm_sulfidrico;
            Serial.print("bd1 = ");
            Serial.print(soma/20);
            Serial.print(" , ");
           soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras2[i].ppm_sulfidrico;
            Serial.print("bd2 = ");
            Serial.print(soma/20);
            Serial.print(" , ");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras3[i].ppm_sulfidrico;
            Serial.print("bd3 = ");
            Serial.print(soma/20);
            Serial.print(" , ");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras4[i].ppm_sulfidrico;
            Serial.print("bd4 = ");
            Serial.println(soma/20);
        break;
        case 6:
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras1[i].ppm_metano;
            Serial.print("bd1:");
            Serial.print(soma/20);
            Serial.print(",");
           soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras2[i].ppm_metano;
            Serial.print("bd2:");
            Serial.print(soma/20);
            Serial.print(",");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras3[i].ppm_metano;
            Serial.print("bd3:");
            Serial.print(soma/20);
            Serial.print(",");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras4[i].ppm_metano;
            Serial.print("bd4:");
            Serial.println(soma/20);
        break;
        case 7:
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras1[i].ppm_carbono;
            Serial.print("bd1 = ");
            Serial.print(soma/20);
            Serial.print(" , ");
           soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras2[i].ppm_carbono;
            Serial.print("bd2 = ");
            Serial.print(soma/20);
            Serial.print(" , ");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras3[i].ppm_carbono;
            Serial.print("bd3 = ");
            Serial.print(soma/20);
            Serial.print(" , ");
            soma=0;
            for(int i=0;i<20;i++)
                soma+=leituras4[i].ppm_carbono;
            Serial.print("bd4 = ");
            Serial.println(soma/20);
        break;
    }
}
