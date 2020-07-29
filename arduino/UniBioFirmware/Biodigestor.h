#ifndef Biodigestor_h
#define Biodigestor_h


#include <Arduino.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include "MHZ19.h"
#include <Ewma.h>

typedef struct{
    int8_t pin_dht=-1;
    int8_t pin_mhz_rx=-1;
    int8_t pin_mhz_tx=-1;
    int8_t pin_ds18=-1;
    int8_t pin_pressao=-1;
    int8_t pin_mq4=-1;
    int8_t pin_mq136=-1;
}Pinos;

typedef struct{
    float temp_biomassa=0;
    float temp_gas=0;
    int8_t umidade=0;
    float pressao=0;
    float metano=12;
    float sulfidrico=23.5;
    int8_t carbono=0;
}Calibragem;

typedef struct{
    char * data_hora;
    float temp_ambiente=0;
    float temp_biomassa=0;
    float temp_gas=0;
    uint8_t umidade=0;
    float pressao=0;
    uint16_t ppm_metano=0;
    float ppm_sulfidrico=0;
    uint16_t ppm_carbono=0;
}Leitura;


class Biodigestor
{
    private:
        Pinos pinos;
        Calibragem calibragem;
        uint8_t cod_biodig;
        
        DHT* dht;
        OneWire* onewire;
        DallasTemperature* ds18;
//        SoftwareSerial* s_mhz;
//        MHZ19* mhz;
        
        Ewma filter_pressao,filter_metano,filter_sulfidrico;
    public:
        Biodigestor();
        bool begin(int cod_biodig,Pinos pinos,Calibragem calibragem);
        void loop();
        void set_cod_biodig(uint8_t cod_biodig);
        uint8_t get_cod_biodig();
        Leitura get_leitura();
 
        float ler_temp_biomassa();
        float ler_temp_gas();
        int ler_umidade();
        float ler_pressao();
        int ler_metano();
        float ler_sulfidrico();
        int ler_carbono();
};

#endif
