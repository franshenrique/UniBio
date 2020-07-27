#ifndef EspBridge_h
#define EspBridge_h

#include <Arduino.h>
#include <SD.h>
#include "CString.h"

class EspBridge
{
    private:
        Stream* serial_esp;
    public:
        bool begin(Stream* serial_esp);
        bool wifi_begin(CString& ssid,CString& password);
        bool http_begin(CString& api_host,uint16_t & api_port,CString& uri);
        bool http_setAuth(CString& auth);
        int http_post(char* dados,char* bracket_start,char* bracket_end);
        int http_post_file(File& file,char* bracket_start,char* bracket_end);
        bool http_end();
        void flush_serial();
};

#endif // !EspBridge_h
