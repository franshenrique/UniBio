#include "SDUniBio.h"


SDUniBio::SDUniBio(SDClass* sd_driver){
    sd=sd_driver;
}

bool SDUniBio::begin(){
    if(!sd->exists("unibio/conf/unibio"))
    {   
        debug(21);
        // if(!criar_arq_conf())
        // {
            // Serial.println("Falha ao criar arquivo de configuracao");
            return false;
        // }
    }
    if(!ler_configuracoes())
    {
        debug(22);
        return false;
    }
    return true;
}

Configuracoes* SDUniBio::get_configuracoes()
{
    return &configuracoes;
}

bool SDUniBio::salvar_fila(uint8_t& cod_biodigestor,char* leitura_json)
{
    CString path("unibio/bd-");
    path.concat(cod_biodigestor);
    CString path_fila(path);
    path_fila.concat("/fila");
    CString path_controle(path);
    path_controle.concat("/controle");
    
    File file;
    
    if(!sd->exists(path.c_str()))
    {
        if(!sd->mkdir(path_fila.c_str()))
        {
            debug(23);
            return false;
        }
    }
    
    if(!sd->exists(path_controle.c_str()))
    {
        file=sd->open(path_controle.c_str(),FILE_WRITE);
        if(!file)
        {
            file.close();
            debug(24);
            return false;
        }
        file.print("1\n1\n0\n");
        file.close();
    }
    
    file=sd->open(path_controle.c_str());
    if(!file)
    {
        file.close();
        debug(25);
        return false;
    }
    int inicio=file.readStringUntil('\n').toInt();
    int fim=file.readStringUntil('\n').toInt();
    int tamanho=file.readStringUntil('\n').toInt();
    file.close();
    
    if(tamanho>=configuracoes.quant_dados_arq)
    {
        tamanho=0;
        fim+=1;
    }

    path_fila.concat('/');
    path_fila.concat(fim);
    file=sd->open(path_fila.c_str(),FILE_WRITE);
    if(!file)
    {
        file.close();
        debug(26);
        return false;
    }
    if(tamanho!=0)
        file.print(",");
    file.print(leitura_json);
    file.close();
    tamanho++;
    
    if(!sd->remove(path_controle.c_str()))
    {
        debug(27);
        return false;
    }
    file=sd->open(path_controle.c_str(),FILE_WRITE);
    if(!file)
    {
        file.close();
        debug(28);
        return false;
    }
    CString controle(inicio);
    controle.concat('\n');
    controle.concat(fim);
    controle.concat('\n');
    controle.concat(tamanho);
    controle.concat('\n');
    file.print(controle.c_str());
    file.close();
    return true;
}

bool SDUniBio::existe_fila(uint8_t & cod_biodigestor)
{
    CString path("unibio/bd-");
    path.concat(cod_biodigestor);
    path.concat("/controle");
    if(sd->exists(path.c_str()))
        return true;
    return false;
}

File SDUniBio::proxima_fila_fileStream(uint8_t & cod_biodigestor)
{
    CString path("unibio/bd-");
    path.concat(cod_biodigestor);
    CString path_fila(path);
    path_fila.concat("/fila");
    CString path_controle(path);
    path_controle.concat("/controle");
    
    File file=sd->open(path_controle.c_str());
    if(!file)
    {
        file.close();
        debug(29);
        return file;
    }
    int inicio=file.readStringUntil('\n').toInt();
    file.close();

    path_fila.concat('/');
    path_fila.concat(inicio);
    file=sd->open(path_fila.c_str());
    if(!file)
    {
        file.close();
        debug(30);
        return file;
    }
    return file;
}

bool SDUniBio::apagar_prox_fila(uint8_t & cod_biodigestor)
{
    CString path("unibio/bd-");
    path.concat(cod_biodigestor);
    CString path_fila(path);
    path_fila.concat("/fila/");
    CString path_controle(path);
    path_controle.concat("/controle");
    
    File file=sd->open(path_controle.c_str());
    if(!file)
    {
        file.close();
        debug(31);
        return false;
    }
    int inicio=file.readStringUntil('\n').toInt();
    int fim=file.readStringUntil('\n').toInt();
    int tamanho=file.readStringUntil('\n').toInt();
    file.close();
    
    if(!sd->remove(path_controle.c_str()))
    {
        debug(32);
        return false;
    }
    
    path_fila.concat(inicio);
    if(!sd->remove(path_fila.c_str()))
    {
        debug(33);
        return false;
    }
    
    inicio++;
    if(inicio<=fim)
    {
        file=sd->open(path_controle.c_str(),FILE_WRITE);
        if(!file)
        {
            file.close();
            debug(34);
            return false;
        }
        CString controle(inicio);
        controle.concat('\n');
        controle.concat(fim);
        controle.concat('\n');
        controle.concat(tamanho);
        controle.concat('\n');  
        file.print(controle.c_str());
        file.close();
    }
    return true;
}

//bool SDUniBio::criar_arq_conf()
//{
//    if(!sd->exists(F("unibio/conf")))
//    {
//        if(!sd->mkdir(F("UniBio/conf")))
//        {
//            debug(35);
//            return false;
//        }
//    }
//    sd->remove(F("UniBio/conf/unibio"));
//    File file=sd->open(F("UniBio/conf/unibio"),FILE_WRITE);
//    if(!file) 
//    {
//        file.close();
//        debug(36);
//        return false;
//    }
//    file.println("wifi_ssid:exemplo;");
//    file.println("wifi_password:exemplo;");
//    file.println("api_host:exemplo.com;");
//    file.println("api_port:80;");
//    file.println("cod_central:123;");
//    file.println("api_key:key-exemplo-123;");
//    file.println("tempo_envio:600;");
//    file.println("tempo_verificar_req:10;");
//    file.println("quant_dados_arq:10;");
//    file.println("quant_biodigestores:3;");
//    file.println("cod_biodigestor:1;"); 
//    file.println("cod_biodigestor:2;");
//    file.print("cod_biodigestor:3;");
//    file.close();
//    for(uint8_t i=1;i<=3;i++)
//    {
//        sd->remove("UniBio/conf/bd-"+String(i));
//        File file=sd->open("UniBio/conf/bd-"+String(i),FILE_WRITE);
//        if(!file)
//        {
//            file.close();
//            debug(37);
//            return false;
//        }
//        file.println("pin_dht:-1;");
//        file.println("pin_ds18b20:-1;");
//        file.println("pin_pressao:-1;");
//        file.println("pin_mq4:-1;");
//        file.println("pin_mq136:-1;");
//        file.println("pin_mhz19b_rx:-1;");
//        file.println("pin_mhz19b_tx:-1;");
//        file.println("calib_temp_biomassa:0;");
//        file.println("calib_temp_gas:0;");
//        file.println("calib_umidade:0;");
//        file.println("calib_pressao:0;");
//        file.println("calib_metano:0;");
//        file.println("calib_sulfidrico:0;");
//        file.print("calib_carbono:0;");
//        file.close();
//    }
//    return true;
//}

bool SDUniBio::ler_configuracoes()
{
    const char dir[] PROGMEM="unibio/conf/unibio";
    if(!sd->exists(dir)) 
    {
        debug(35);
        return false;
    }
    File file=sd->open(dir);
    if(!file)
    {
        debug(36);
        file.close();
        return false;
    }
    while(file.available())
    {
        CString sconfig;
        while(file.available())
        {
            char c=file.read();
            if(c==' '||c=='\r'||c=='\n') continue;
            if(c==';') break;
            sconfig.concat(c);
        }
        if(!strchr(sconfig.c_str(),':'))
        {
            file.close();
            debug(37);
            return false;
        }
        CString chave(sconfig.split(':',true));
        CString valor(sconfig.split(':',false));
        Serial.print(chave.c_str());Serial.print(':');Serial.println(valor.c_str());
        bool ok=set_config(chave,valor);
        if(!ok)
        {
            debug(38);
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

bool SDUniBio::set_config(CString& chave,CString& valor)
{
    if(chave.equals(("wifi_ssid")))
    {
        configuracoes.wifi_ssid=(char*) malloc(valor.length()+1);
        strcpy(configuracoes.wifi_ssid,valor.c_str());
        return true;
    }
    if(chave.equals(("wifi_password")))
    {
        configuracoes.wifi_password=(char*) malloc(valor.length()+1);
        strcpy(configuracoes.wifi_password,valor.c_str());
        return true;
    }
    if(chave.equals(("api_host")))
    {
        configuracoes.api_host=(char*) malloc(valor.length()+1);
        strcpy(configuracoes.api_host,valor.c_str());
        return true;
    }
    if(chave.equals(("api_port")))
    {
        configuracoes.api_port=valor.toInt();
        if(configuracoes.api_port==0)
            return false;
        return true;
    }
    if(chave.equals(("api_key")))
    {
        configuracoes.api_key=(char*) malloc(valor.length()+1);
        strcpy(configuracoes.api_key,valor.c_str());
        return true;
    }
    if(chave.equals(("cod_central")))
    {
        configuracoes.cod_central=valor.toInt();
        if(configuracoes.cod_central==0)
            return false;
        return true;
    }
    // if(chave.equals("tempo_media_segundos"))
    // {
    //     configuracoes.tempo_media_segundos=valor.toInt();
    //     if(configuracoes.tempo_media_segundos==0)
    //         return false;
    //     return true;
    // }
    if(chave.equals(("tempo_envio_segundos")))
    {
        configuracoes.tempo_envio_segundos=valor.toInt();
        if(configuracoes.tempo_envio_segundos==0)
            return false;
        return true;
    }
    if(chave.equals(("tempo_verificar_segundos")))
    {
        configuracoes.tempo_verificar_segundos=valor.toInt();
        if(configuracoes.tempo_verificar_segundos==0)
            return false;
        return true;
    }
    if(chave.equals(("quant_dados_arq")))
    {
        configuracoes.quant_dados_arq=valor.toInt();
        if(configuracoes.quant_dados_arq==0)
            return false;
        return true;
    }
    if(chave.equals(("calib_temp_amb")))
    {
        configuracoes.calib_temp_amb=valor.toFloat();
        return true;
    }
    if(chave.equals(("cod_biodigestor")))
    {
        int8_t valor_int=valor.toInt();
        if(valor_int==0)
            return false;
        configuracoes.quant_biodigestores++;
        int8_t quant=configuracoes.quant_biodigestores;
        configuracoes.biodigestores=(Biodigestor*)realloc(configuracoes.biodigestores,quant*sizeof(Biodigestor));
        configuracoes.biodigestores[quant-1]=Biodigestor();
        configuracoes.biodigestores[quant-1].set_cod_biodig(valor_int);
        return true;
    }
    debug(39);
    return false;
}

Biodigestor* SDUniBio::get_biodigestores()
{
    uint8_t & quant=configuracoes.quant_biodigestores;
    Biodigestor* aux=configuracoes.biodigestores;
    for(uint8_t i=0;i<quant;i++)
    {
        Pinos pinos;
        Calibragem calibragem;
        uint8_t cod_biodigestor=aux[i].get_cod_biodig();
        CString path(("unibio/conf/bd-"));
        path.concat((int)cod_biodigestor);
        File file=SD.open(path.c_str());
        if(!file)
        {
            file.close();
            debug(40);
            return NULL;
        }
        while(file.available())
        {
            CString sconfig;
            while(file.available())
            {
                char c=file.read();
                if(c==' '||c=='\r'||c=='\n') continue;
                if(c==';') break;
                sconfig.concat(c);
            }
            if(!strchr(sconfig.c_str(),':'))
            {
                file.close();
                debug(41);
                return NULL;
            }
            CString chave(sconfig.split(':',true));
            CString valor(sconfig.split(':',false));
            Serial.print(chave.c_str());Serial.print(':');Serial.println(valor.c_str());
            if(!set_config_biodigestor(pinos,calibragem,chave,valor))
            {
                file.close();
                debug(42);
                return NULL;
            }
        }
        file.close();
        if(!aux[i].begin(cod_biodigestor,pinos,calibragem))
        {
            debug(43);
            return NULL;
        }
    }
    return aux;
}

bool SDUniBio::set_config_biodigestor(Pinos& pinos,Calibragem& calibragem,CString& chave,CString& valor)
{
    if(chave.equals(("pin_dht")))
    {
        pinos.pin_dht=valor.toInt();
        return true;
    }
    if(chave.equals(("pin_ds18b20")))
    {
        pinos.pin_ds18=valor.toInt();
        return true;
    }
    if(chave.equals(("pin_pressao")))
    {
        pinos.pin_pressao=valor.toInt();
        return true;
    }
    if(chave.equals(("pin_mq4")))
    {
        pinos.pin_mq4=valor.toInt();
        return true;
    }
    if(chave.equals(("pin_mq136")))
    {
        pinos.pin_mq136=valor.toInt();
        return true;
    }
    if(chave.equals(("pin_mhz19b_rx")))
    {
        pinos.pin_mhz_rx=valor.toInt();
        return true;
    }
    if(chave.equals(("pin_mhz19b_tx")))
    {
        pinos.pin_mhz_tx=valor.toInt();
        return true;
    }
    if(chave.equals(("calib_temp_biomassa")))
    {
        calibragem.temp_biomassa=valor.toFloat();
        return true;
    }
    if(chave.equals(("calib_temp_gas")))
    {
        calibragem.temp_gas=valor.toFloat();
        return true;
    }
    if(chave.equals(("calib_umidade")))
    {
        calibragem.umidade=valor.toInt();
        return true;
    }
    if(chave.equals(("calib_pressao")))
    {
        calibragem.pressao=valor.toFloat();
        return true;
    }
    if(chave.equals(("calib_metano")))
    {
        calibragem.metano=valor.toFloat();
        return true;
    }
    if(chave.equals(("calib_sulfidrico")))
    {
        calibragem.sulfidrico=valor.toFloat();
        return true;
    }
    if(chave.equals(("calib_carbono")))
    {
        calibragem.carbono=valor.toInt();
        return true;
    }
    debug(44);
    return false;
}
