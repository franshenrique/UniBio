#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define FW_VERSION "1.1"



WiFiClient client;
HTTPClient http;

void setup()
{
  Serial.begin(115200);
}
void loop()
{
  if(Serial.available())
  {
    String command=Serial.readStringUntil('\n');
    String body=Serial.readStringUntil('\n');
    if(command=="firmware")
    {
      Serial.print(FW_VERSION);
      Serial.print('\n');
      return;
    }
    if(command=="teste")
    {
      Serial.print("ok\n");
      return;
    }
    if(command=="wifi_status")
    {
      Serial.print(WiFi.status());
      Serial.print('\n');
      return;
    }
    if(command=="wifi_begin")
    {
      char * ssid;
      char * password;
      ssid=strtok(body.c_str(),"\r");
      password=strtok(NULL,"\r");
      WiFi.begin(ssid,password);
      Serial.print("ok\n");
      return;
    }
    if(command=="http_begin")
    {
      String host;
      int port;
      String uri;
      bool https;
      bool reuse;
      host.concat(String(strtok(body.c_str(),"\n")));
      port=String(strtok(NULL,"\n")).toInt();
      uri.concat(String(strtok(NULL,"\n")).toInt());
      https=String(strtok(NULL,"\n")).toInt();
      reuse=String(strtok(NULL,"\n")).toInt();
      if(http.begin(client,host,port,uri,https))
      {
        http.setReuse(reuse);
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
      String key,value;
      key.concat(String(strtok(body.c_str(),"\r")));
      value.concat(String(strtok(NULL,"\r")));
      http.addHeader(key,value);
      Serial.print("ok\n");
      return;
    }
    if(command=="http_set_reuse")
    {
      bool reuse=body.toInt();
      http.setReuse(reuse);
      Serial.print("ok\n");
      return;
    }
    if(command=="http_post")
    {
      int http_status;
      http_status=http.POST(body);
      Serial.print(String(http_status)+"\n");
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
