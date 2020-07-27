#ifndef SDUniBio_h
#define SDUniBio_h

#include <Arduino.h>
#include <SD.h>
#include "Biodigestor.h"
#include "CString.h"
#include "Debug.h"

typedef struct{
    char * wifi_ssid;
    char * wifi_password;
    char * api_host;
    uint16_t api_port;
    int cod_central;
    char * api_key;
    // uint16_t tempo_media_segundos;
    uint16_t tempo_envio_segundos;
    uint16_t tempo_verificar_segundos;
    uint8_t quant_dados_arq;
    float calib_temp_amb=0;
    uint8_t quant_biodigestores=0;
    Biodigestor * biodigestores;
}Configuracoes;

class SDUniBio
{
    private:
        SDClass* sd;
        uint8_t dados_por_arq;
        Configuracoes configuracoes;
    public:
        SDUniBio(SDClass* sd_driver);
        bool begin();
        Configuracoes* get_configuracoes();
        Biodigestor* get_biodigestores(); 
        bool salvar_fila(uint8_t & cod_biodigestor,char* leitura_json);
        bool existe_fila(uint8_t & cod_biodigestor);
        File proxima_fila_fileStream(uint8_t & cod_biodigestor);
        bool apagar_prox_fila(uint8_t & cod_biodigestor);
    private:
        bool criar_arq_conf();
        bool ler_configuracoes();
        bool set_config(CString& chave,CString& valor);
        bool set_config_biodigestor(Pinos& pinos,Calibragem& calibragem,CString& chave,CString & valor);
};


#endif // !Uni
