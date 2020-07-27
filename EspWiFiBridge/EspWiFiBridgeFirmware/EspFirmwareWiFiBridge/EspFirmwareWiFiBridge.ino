#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define FW_VERSION "1.0.0"



WiFiClient client;
HTTPClient http;

void setup()
{
  Serial.begin(115200);
}
void loop()
{
  String command;
  String body;
  String s_params;
  String params[10];
  int quant;
  if(Serial.available())
  {
    command=Serial.readStringUntil('\n');
    s_params=Serial.readStringUntil('\n');
    if(s_params!="") quant=split(s_params,params);

    if(command=="firmware")
    {
      Serial.print(FW_VERSION);
      Serial.print("\n");
      return;
    }
    if(command=="teste")
    {
      Serial.print("ok\n");
      return;
    }
    if(command=="wifi_status")
    {
      Serial.print(String(WiFi.status())+"\n");
      return;
    }
    if(command=="wifi_begin")
    {
      WiFi.begin(params[0],params[1]);
      Serial.print("ok\n");
      return;
    }
    if(command=="http_begin")
    {
      if(http.begin(client,params[0],params[1].toInt(),params[2]))
      {
        http.addHeader("Content-Type","application/json");
        Serial.print("ok\n");
      }
      else
        Serial.print("error\n");
      return;
    }
    if(command=="http_end")
    {
      http.end();
      Serial.print("ok\n");
      return;
    }
    if(command=="http_add_header")
    {
      http.addHeader(params[0],params[1]);
      Serial.print("ok\n");
      return;
    }
    if(command=="http_set_auth")
    {
      if(quant==1)
        http.setAuthorization(params[0].c_str());  
      else
        http.setAuthorization(params[0].c_str(),params[1].c_str());
      Serial.print("ok\n"); 
      return;
    }
    if(command=="http_set_reuse")
    {
      http.setReuse(params[0].toInt());
      Serial.print("ok\n");
      return;
    }
    if(command=="http_post")
    {
      Serial.print("ack\n");
      body=Serial.readStringUntil('\n');
      int http_status;
      http_status=http.POST(body);
      Serial.print(String(http_status)+"\n");
      return;
    }
    Serial.print("nc-"+command+"\n");
  }
}
int split(String params,String* s_params)
{
  int quant=1,ind=0,next_ind=0;
  next_ind=params.indexOf("\\",ind);
  while(next_ind!=-1)
  {
    quant++;
    ind=next_ind+1;
    next_ind=params.indexOf("\\",ind);
  }
  ind=0;
  next_ind=0;
  
  for(int i=0;i<quant;i++)
  {
    next_ind=params.indexOf("\\",ind);
    if(next_ind==-1)
    {
      s_params[i]=params.substring(ind);
      break;
    }
    s_params[i]=params.substring(ind,next_ind);
    ind=next_ind+1;
  }
  return quant;
}
