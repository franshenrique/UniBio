#include "Biodigestor.h"


bool Biodigestor::begin(int cod_biodig,uint16_t tempo_media_segundos,Pinos pinos,Calibragem calibragem)
{   
    this->cod_biodig=cod_biodig;
    this->pinos=pinos;    
    this->calibragem=calibragem;
    this->tempo_media_segundos=tempo_media_segundos;
    if(pinos.pin_dht!=-1)
    {
        dht=new DHT(pinos.pin_dht,DHT11);
        dht->begin();
    }
    if(pinos.pin_ds18!=-1)
    {
        onewire=new OneWire(pinos.pin_ds18);
        ds18=new DallasTemperature(onewire);
        ds18->begin();   
    }
    if(pinos.pin_mhz_rx!=-1&&pinos.pin_mhz_tx!=-1)
    {
        s_mhz=new SoftwareSerial(pinos.pin_mhz_tx,pinos.pin_mhz_rx);
        s_mhz->begin(9600);
        s_mhz->listen();
        mhz=new MHZ19();
        mhz->begin(*s_mhz);
        delay(1000);
        mhz->autoCalibration(false);
//        if(!mhz->getCO2())
//          return false;
    }   
    return true;
}

uint8_t Biodigestor::get_cod_biodig()
{
    return cod_biodig;
}

Leitura Biodigestor::get_leitura()
{
  Leitura leitura;
  if(pinos.pin_ds18!=-1)
      leitura.temp_biomassa=ler_temp_biomassa();
  if(pinos.pin_dht!=-1)
      leitura.temp_gas=ler_temp_gas();
  if(pinos.pin_dht!=-1)
      leitura.umidade=ler_umidade();
  if(pinos.pin_pressao!=-1)
      leitura.pressao=ler_pressao();
  if(pinos.pin_mq4!=-1)
      leitura.ppm_metano=ler_metano();
  if(pinos.pin_mq136!=-1)
      leitura.ppm_sulfidrico=ler_sulfidrico();
  if(pinos.pin_mhz_rx!=-1&&pinos.pin_mhz_tx!=-1)
      leitura.ppm_carbono=ler_carbono();
  return leitura;
}
Leitura Biodigestor::get_leitura_media()
{
    Leitura leitura,media[20];
    for(int i=0;i<20;i++)
    {
        if(pinos.pin_ds18!=-1)
            media[i].temp_biomassa=ler_temp_biomassa();
        if(pinos.pin_dht!=-1)
            media[i].temp_gas=ler_temp_gas();
        if(pinos.pin_dht!=-1)
            media[i].umidade=ler_umidade();
        if(pinos.pin_pressao!=-1)
            media[i].pressao=ler_pressao();
        if(pinos.pin_mq4!=-1)
            media[i].ppm_metano=ler_metano();
        if(pinos.pin_mq136!=-1)
            media[i].ppm_sulfidrico=ler_sulfidrico();
        if(pinos.pin_mhz_rx!=-1&&pinos.pin_mhz_tx!=-1)
            media[i].ppm_carbono=ler_carbono();
        delay((tempo_media_segundos*1000)/20);
    }
    unsigned long soma1=0;
    double soma2=0;
    for(int i=0;i<20;i++)
      soma2+=media[i].temp_biomassa;
    leitura.temp_biomassa=soma2/20;
    soma2=0;
    for(int i=0;i<20;i++)
      soma2+=media[i].temp_gas;
    leitura.temp_gas=soma2/20;
    soma2=0;
    for(int i=0;i<20;i++)
      soma1+=media[i].umidade;
    leitura.umidade=soma1/20;
    soma1=0;
    for(int i=0;i<20;i++)
      soma2+=media[i].pressao;
    leitura.pressao=soma2/20;
    soma2=0;
    for(int i=0;i<20;i++)
      soma1+=media[i].ppm_metano;
    leitura.ppm_metano=soma1/20;
    soma1=0;
    for(int i=0;i<20;i++)
      soma1+=media[i].ppm_sulfidrico;
    leitura.ppm_sulfidrico=soma1/20;
    soma1=0;
    for(int i=0;i<20;i++)
      soma1+=media[i].ppm_carbono;
    leitura.ppm_carbono=soma1/20;
    return leitura;
}


float Biodigestor::ler_pressao()
{
    if(pinos.pin_pressao==-1)
        return 0;
    unsigned long soma=0;
    for(int i=0;i<1000;i++)
        soma+=analogRead(pinos.pin_pressao);
    soma=(soma/1000);
    return soma;
}

int Biodigestor::ler_umidade ()
{
    if(pinos.pin_dht==-1)
        return 0;
    int umid= dht->readHumidity();
    if(umid<0) return 0;
    return umid;
}

float Biodigestor::ler_temp_gas()
{
    if(pinos.pin_dht==-1)
        return 0;
    float temp= dht->readTemperature();
    if(isnan(temp)) return 0;
    if(temp<0) return 0;
    return temp+calibragem.temp_gas;
}

float Biodigestor::ler_temp_biomassa()
{
    if(pinos.pin_ds18==-1)
        return 0; 
    ds18->requestTemperatures();
    if(ds18->getTempCByIndex(0)<0) return 0;
    return ds18->getTempCByIndex(0);
}

int Biodigestor::ler_metano()
{
    if(pinos.pin_mq4==-1)
        return 0;
    unsigned long soma=0;
    for(uint16_t i=0;i<1000;i++)
        soma+=analogRead(pinos.pin_mq4);
    return (soma/1000);
}

int Biodigestor::ler_sulfidrico()
{
    if(pinos.pin_mq136==-1)
        return 0;
    unsigned long soma=0;
    for(uint16_t i=0;i<1000;i++)
        soma+=analogRead(pinos.pin_mq136);
    soma= soma/1000;
    return soma;
}

int Biodigestor::ler_carbono()
{
    if(pinos.pin_mhz_rx==-1||pinos.pin_mhz_tx==-1)
        return;
    s_mhz->listen();
    return mhz->getCO2();
}
