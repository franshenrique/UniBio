#ifndef types_h
#define types_h

#include <Arduino.h>


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
    String data_hora="01/01/2000 01:01:01";
    float temp_ambiente=0;
    float temp_biomassa=0;
    float temp_gas=0;
    int umidade=0;
    float pressao=0;
    int ppm_metano=0;
    int ppm_sulfidrico=0;
    int ppm_carbono=0;
}Leitura;


typedef struct{
    String wifi_ssid;
    String wifi_password;
    String api_host;
    uint16_t api_port;
    int cod_central;
    String api_key;
    uint16_t tempo_media_segundos;
    uint16_t tempo_envio_segundos;
    uint16_t tempo_verificar_segundos;
    uint8_t quant_dados_arq;
    uint8_t quant_biodigestores;
    uint8_t* cod_biodigestores;
}Configuracoes;


#endif
