#ifndef ApiClientUniBio_h
#define ApiClientUniBio_h

#include <Arduino.h>
#include <SD.h>
#include "debug.h"
#include "SDUniBio.h"
#include "EspBridge.h"
#include "CString.h"

class ApiClientUniBio
{
    private:
        Configuracoes* configuracoes;
        EspBridge* wifi_driver;
    public:
        ApiClientUniBio(EspBridge *wifi_driver);
        bool begin(Configuracoes* config);
        int enviar_valores(uint8_t & cod_biodigestor,char* leitura);
        int enviar_fila_fileStream(uint8_t & cod_biodigestor,File& file);
        int verificar_requisicao();
};


#endif
