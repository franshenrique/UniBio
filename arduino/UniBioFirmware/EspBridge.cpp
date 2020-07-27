#include "EspBridge.h"



bool EspBridge::begin(Stream* serial_esp)
{
    this->serial_esp=serial_esp;
    serial_esp->setTimeout(4000);
    delay(2000);
    flush_serial();
    serial_esp->print("teste\n\n");
    CString resposta;
    resposta.concat(serial_esp->readStringUntil('\n'));
    if(!resposta.equals("ok"))
    {
        Serial.println(F("Falha na comunicação esp teste"));
        return false;
    }
    return true;
}

bool EspBridge::wifi_begin(CString& ssid,CString& password)
{
    flush_serial();
    serial_esp->print("wifi_begin\n");
    serial_esp->print(ssid.c_str());
    serial_esp->print("\\");
    serial_esp->print(password.c_str());
    serial_esp->print("\n");
    CString resposta;
    resposta.concat(serial_esp->readStringUntil('\n'));
    if(!resposta.equals("ok"))
    {
        Serial.println(F("Falha na comunicação esp http_begin"));
        return false;
    }
    return true;
}
bool EspBridge::http_begin(CString& api_host,uint16_t & api_port,CString& uri)
{
    flush_serial();
    serial_esp->print("http_begin\n");
    serial_esp->print(api_host.c_str());
    serial_esp->print("\\");
    serial_esp->print(api_port);
    serial_esp->print("\\");
    serial_esp->print(uri.c_str());
    serial_esp->print("\n");
    CString resposta;
    resposta.concat(serial_esp->readStringUntil('\n'));
    if(!resposta.equals("ok"))
    {
        Serial.println(F("Falha na comunicação esp http_begin"));
        return false;
    }
    return true;
}
bool EspBridge::http_setAuth(CString& auth)
{
    flush_serial();
    serial_esp->print("http_set_auth\n");
    serial_esp->print(auth.c_str());
    serial_esp->print('\n');
    CString resposta;
    resposta.concat(serial_esp->readStringUntil('\n'));
    if(!resposta.equals("ok"))
    {
        Serial.println(F("Falha na comunicação esp http_set_auth"));
        return false;
    }
    return true;
}
int EspBridge::http_post(char* dados,char* bracket_start,char* bracket_end)
{
    flush_serial();
    serial_esp->print(F("http_post\n\n"));
    CString resposta;
    resposta.concat(serial_esp->readStringUntil('\n'));
    if(!resposta.equals("ack"))
    {
        Serial.println(F("Falha na comunicação esp http_post"));
        return 0;
    }
    int position=0;
    serial_esp->print(bracket_start);
    serial_esp->print(dados);
    serial_esp->print(bracket_end);
    serial_esp->print('\n');
    serial_esp->setTimeout(15000);
    resposta.erase();
    resposta.concat(serial_esp->readStringUntil('\n'));
    serial_esp->setTimeout(4000);
    return resposta.toInt();
}

int EspBridge::http_post_file(File& file,char* bracket_start,char* bracket_end)
{
    flush_serial();
    serial_esp->print("http_post\n\n");
    CString resposta;
    resposta.concat(serial_esp->readStringUntil('\n'));
    if(!resposta.equals("ack"))
    {
        Serial.println(F("Falha comunicação esp http_post"));
        return false;
    }
    serial_esp->print(bracket_start);
    while(file.available())
        serial_esp->write(file.read());
    serial_esp->print(bracket_end);
    serial_esp->print('\n');
    serial_esp->setTimeout(15000);
    resposta.erase();
    resposta.concat(serial_esp->readStringUntil('\n'));
    serial_esp->setTimeout(4000);
    return resposta.toInt();
}
bool EspBridge::http_end()
{
    flush_serial();
    serial_esp->print("http_end\n\n");
    CString resposta;
    resposta.concat(serial_esp->readStringUntil('\n'));
    if(!resposta.equals("ok"))
    {
        Serial.println(F("Falha na comunicacao esp hhtp_end"));
        return false;
    }
    return true;
}
void EspBridge::flush_serial()
{
    while(serial_esp->available())
        serial_esp->read();
}
