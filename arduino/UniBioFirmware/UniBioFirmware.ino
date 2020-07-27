#include <Arduino.h>
#include "CString.h"
#include "Debug.h"
#include <Ewma.h>
#include <RTClib.h>
#include "Biodigestor.h"
#include "EspBridge.h"
#include "ApiClientUnibio.h"
#include "SDUniBio.h"

#define buzzer 16

RTC_DS3231 rtc;
EspBridge esp8266;
SDUniBio sdunibio(&SD);
ApiClientUniBio apiclient(&esp8266);
Biodigestor *biodigestores;
Configuracoes *configuracoes;
Ewma filter_temp_amb(0.01);

unsigned long tempoCorrente,ultTempoEnvio;

void get_data_hora(char* data_hora)
{
    DateTime now=rtc.now();
    sprintf(data_hora,"%04d-%02d-%02d %02d:%02d:%02d",now.year(),now.month(),now.day(),now.hour(),now.minute(),now.second());
}

void prep_leitura_json(CString& leitura_json,Leitura& leitura)
{
  const char data_hora[] PROGMEM="{\"data_hora\":\"";
  const char temp_amb[] PROGMEM="\",\"temp_amb\":";
  const char temp_bm[] PROGMEM=",\"temp_bm\":";
  const char temp_gas[] PROGMEM=",\"temp_gas\":";
  const char umidade[] PROGMEM=",\"umidade\":";
  const char pressao[] PROGMEM=",\"pressao\":";
  const char metano[] PROGMEM=",\"metano\":";
  const char sulfidrico[] PROGMEM=",\"sulfidrico\":";
  const char carbono[] PROGMEM=",\"carbono\":";
  const char fim[] PROGMEM="}";
  leitura_json.concat(data_hora);
  leitura_json.concat(leitura.data_hora);
  leitura_json.concat(temp_amb);
  leitura_json.concat(float(leitura.temp_ambiente));
  leitura_json.concat(temp_bm);
  leitura_json.concat(float(leitura.temp_biomassa));
  leitura_json.concat(temp_gas);
  leitura_json.concat(float(leitura.temp_gas));
  leitura_json.concat(umidade);
  leitura_json.concat(int(leitura.umidade));
  leitura_json.concat(pressao);
  leitura_json.concat(float(leitura.pressao));
  leitura_json.concat(metano);
  leitura_json.concat(int(leitura.ppm_metano));
  leitura_json.concat(sulfidrico);
  leitura_json.concat(float(leitura.ppm_sulfidrico));
  leitura_json.concat(carbono);
  leitura_json.concat(int(leitura.ppm_carbono));
  leitura_json.concat('}');
}

void beep(int times, int time_delay=800)
{
  for (int i = 0; i < times; i++)
  {
    tone(buzzer, 700, time_delay);
    delay(time_delay * 2);
  }
  delay(time_delay < 1000 ? 1000 : time_delay);
}

float get_temp_ambiente()
{
  return rtc.getTemperature()+configuracoes->calib_temp_amb;
}

void setup()
{
  delay(10000);
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);

  if (!rtc.begin())
  {
    Serial.println(F("RTC não conectado"));
    while (1) beep(2);
  }
  if (rtc.lostPower())
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

  if (!SD.begin())
  {
    Serial.println(F("SD não conectado"));
    while (1) beep(3);
  }
  if (!sdunibio.begin())
  {
    Serial.println(F("Falha ao carregar dados do SD"));
    while (1) beep(4);
  }
  configuracoes = sdunibio.get_configuracoes();
  biodigestores = sdunibio.get_biodigestores();
  if(!biodigestores)
  {
    Serial.println(F("Falha ao carregar biodigestores"));
    while (1) beep(5);
  }
  Serial1.begin(115200);
  if (!esp8266.begin(&Serial1))
  {
    Serial.println(F("Dispositivo WiFi não conectado"));
    beep(6);
  }
  else if (!apiclient.begin(configuracoes))
  {
    Serial.println(F("Falha ao configurar WiFi"));
    beep(7);
  }
  beep(1, 500);
  ultTempoEnvio=0;
  tempoCorrente=configuracoes->tempo_envio_segundos * 1000;
  Serial.println(F("\r\n\r\nIniciando...\r\n"));
}

void loop()
{
  for(uint8_t i=0;i<configuracoes->quant_biodigestores;i++)
    biodigestores[i].loop();
  filter_temp_amb.filter(get_temp_ambiente());
  if (tempoCorrente - ultTempoEnvio >= configuracoes->tempo_envio_segundos * 1000)
  {
    for (int i = 0; i < configuracoes->quant_biodigestores; i++)
    {
      uint8_t cod_biodigestor = biodigestores[i].get_cod_biodig();
      
      Leitura leitura = biodigestores[i].get_leitura();
      leitura.temp_ambiente = filter_temp_amb.filter(get_temp_ambiente());
      get_data_hora(leitura.data_hora);
      CString leitura_json;
      prep_leitura_json(leitura_json,leitura);
      Serial.println(leitura_json.c_str());
      if (sdunibio.existe_fila(cod_biodigestor))
      {
        if (!sdunibio.salvar_fila(cod_biodigestor, leitura_json.c_str()))
        {
          Serial.print(F("Falha ao salvar na fila, biodigestor : "));
          Serial.println(cod_biodigestor);
          continue;
        }
        int tentativa=0;
        while (sdunibio.existe_fila(cod_biodigestor))
        {
          File file = sdunibio.proxima_fila_fileStream(cod_biodigestor);
          if (!file)
          {
            Serial.print(F("Falha ao ler arquivo da fila, biodigestor : "));
            Serial.println(cod_biodigestor);
            break;
          }
          int cod_envio = apiclient.enviar_fila_fileStream(cod_biodigestor, file);
          file.close();
          if (cod_envio==200||tentativa==3)
          {
            if(tentativa==3&&cod_envio!=200)
            {
              Serial.println(F("Falha na formatação do arquivo, apagando..."));
            }
            if (!sdunibio.apagar_prox_fila(cod_biodigestor))
            {
              Serial.print(F("Falha ao apagar arquivo, biodigestor : "));
              Serial.println(cod_biodigestor);
            }
            tentativa=0;
          }
          else if(cod_envio==400)
          {
            tentativa++;
            Serial.println(F("Falha na formatação do arquivo, cod:400"));
          }
          else
          {
            Serial.print(F("Falha ao enviar arquivo, cod:"));
            Serial.println(cod_envio);
            break;
          }
        }
      }
      else
      {
        int cod_envio = apiclient.enviar_valores(cod_biodigestor, leitura_json.c_str());
        if (cod_envio!=200)
        {
          Serial.print(F("Falha ao enviar leitura, cod:"));
          Serial.println(cod_envio);
          if (!sdunibio.salvar_fila(cod_biodigestor, leitura_json.c_str()))
          {
            beep(1);
            Serial.print(F("Falha ao salvar arquivo, biodigestor : "));
            Serial.println(cod_biodigestor);
          }  
        }
      }
    }
    ultTempoEnvio = millis();
  }
  tempoCorrente = millis();
}
