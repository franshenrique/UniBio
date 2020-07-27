#include "ApiClientUniBio.h"


ApiClientUniBio::ApiClientUniBio(EspBridge *wifi_driver)
{
    this->wifi_driver=wifi_driver;
}



bool ApiClientUniBio::begin(Configuracoes* config)
{
    configuracoes=config;
    CString ssid(configuracoes->wifi_ssid);
    CString pass(configuracoes->wifi_password);
    if(!wifi_driver->wifi_begin(ssid,pass))
    {
        Serial.println(F("Falha ao iniciar wifi"));
        return false;
    }
    return true;
}
int ApiClientUniBio::enviar_valores(uint8_t & cod_biodig,char* leitura)
{
    CString api_host(configuracoes->api_host);
    CString api_key(configuracoes->api_key);
    uint16_t & api_port=configuracoes->api_port;
    int & cod_central=configuracoes->cod_central;
    CString uri;
    uri.concat("/central/");
    uri.concat(cod_central);
    uri.concat("/biodigestor/");
    uri.concat(cod_biodig);
    if(!wifi_driver->http_begin(api_host,api_port,uri))
    {
        Serial.println(F("Falha ao iniciar http"));  
        return false;
    }
    if(!wifi_driver->http_setAuth(api_key))
    {
        Serial.println(F("Falha ao setar api_key"));
        return false;
    }
    int resposta=wifi_driver->http_post(leitura,"[","]");
    wifi_driver->http_end();
    return resposta;
}

int ApiClientUniBio::enviar_fila_fileStream(uint8_t & cod_biodig,File& file)
{
    CString api_host(configuracoes->api_host);
    CString api_key(configuracoes->api_key);
    uint16_t & api_port=configuracoes->api_port;
    int & cod_central=configuracoes->cod_central;
    CString uri;
    uri.concat("/central/");
    uri.concat(cod_central);
    uri.concat("/biodigestor/");
    uri.concat(cod_biodig);
    if(!wifi_driver->http_begin(api_host,api_port,uri))
    {
        Serial.println(F("Falha ao iniciar http"));
        return false;
    }
    if(!wifi_driver->http_setAuth(api_key))
    {
        Serial.println(F("Falha ao setar api_key"));
        return false;
    }
    int resposta=wifi_driver->http_post_file(file,"[","]");
    wifi_driver->http_end();
    return resposta;
}
