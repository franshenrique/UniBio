#ifndef Biodigestor_h
#define Biodigestor_h


#include <Arduino.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>
#include "MHZ19.h"
#include "types.h"


class Biodigestor
{
    private:
        Pinos pinos;
        Calibragem calibragem;
        uint8_t cod_biodig;
        
        DHT* dht;
        OneWire* onewire;
        DallasTemperature* ds18;
        SoftwareSerial* s_mhz;
        MHZ19* mhz;

        uint16_t tempo_media_segundos;
    public:
        bool begin(int cod_biodig,uint16_t tempo_media_segundos,Pinos pinos,Calibragem calibragem);
        uint8_t get_cod_biodig();
        Leitura get_leitura();
        Leitura get_leitura_media();
 
        float ler_temp_biomassa();
        float ler_temp_gas();
        int ler_umidade();
        float ler_pressao();
        int ler_metano();
        int ler_sulfidrico();
        int ler_carbono();
};

#endif
