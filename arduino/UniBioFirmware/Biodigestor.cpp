#include "Biodigestor.h"

Biodigestor::Biodigestor():
    filter_pressao(0.01),
    filter_metano(0.01),
    filter_sulfidrico(0.01)
{
    return;
}

bool Biodigestor::begin(int cod_biodig,Pinos pinos,Calibragem calibragem)
{   
    this->cod_biodig=cod_biodig;
    this->pinos=pinos;    
    this->calibragem=calibragem;
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
//    if(pinos.pin_mhz_rx!=-1&&pinos.pin_mhz_tx!=-1)
//    {
//        s_mhz=new SoftwareSerial(pinos.pin_mhz_tx,pinos.pin_mhz_rx);
//        s_mhz->begin(9600);
//        s_mhz->listen();
//        mhz=new MHZ19();
//        mhz->begin(*s_mhz);
//    }   
    return true;
}

uint8_t Biodigestor::get_cod_biodig()
{
    return cod_biodig;
}
void Biodigestor::set_cod_biodig(uint8_t cod_biodig)
{
    this->cod_biodig=cod_biodig;
}

void Biodigestor::loop()
{
    ler_pressao();
    ler_metano();
    ler_sulfidrico();
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


float Biodigestor::ler_pressao()
{
    unsigned long soma=0;
    float sensor_value;
    if(pinos.pin_pressao==-1)
        return 0;
    for(int i=0;i<1000;i++)
        soma+=analogRead(pinos.pin_pressao);
    soma=soma/1000;
    sensor_value=filter_pressao.filter(soma);
    sensor_value=sensor_value+calibragem.pressao;
    sensor_value=(sensor_value - 122) * (1200 - 0) / (922 - 122) + 0;
    //sensor_value=(sensor_value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    sensor_value=constrain(sensor_value,0,1200);
    return sensor_value;
}

int Biodigestor::ler_umidade ()
{
    if(pinos.pin_dht==-1)
        return 0;
    int umid= dht->readHumidity();
    if(isnan(umid)) return 0;
    if(umid<=0) return 0;
    umid+=calibragem.umidade;
    umid=constrain(umid,0,100);
    return umid;
}

float Biodigestor::ler_temp_gas()
{
    if(pinos.pin_dht==-1)
        return 0;
    float temp= dht->readTemperature();
    if(isnan(temp)) return 0;
    if(temp<=0) return 0;
    temp=temp+calibragem.temp_gas;
    temp=constrain(temp,0,100);
    return temp;
}

float Biodigestor::ler_temp_biomassa()
{
    if(pinos.pin_ds18==-1)
        return 0; 
    ds18->requestTemperatures();
    float temp=ds18->getTempCByIndex(0);
    if(temp<=0) return 0;
    temp=temp+calibragem.temp_biomassa;
    temp=constrain(temp,0,100);
    return temp;
}

int Biodigestor::ler_metano()
{
    if(pinos.pin_mq4==-1)
        return 0;
    unsigned long soma=0;
    for(uint16_t i=0;i<1000;i++)
        soma+=analogRead(pinos.pin_mq4);
    soma = soma/1000;
    float sensor_value= filter_metano.filter(soma);
    sensor_value = sensor_value*(5.0/1023.0); 
    sensor_value = (5.0-sensor_value)/sensor_value;
    float ratio=sensor_value/calibragem.metano;
    if(ratio<0)ratio=0;
    int ppm=int(pow(10,(log10(ratio) - 1.0696) / (-0.3565))+0.5);
    ppm=constrain(ppm,2,10000);
    return ppm;
}

float Biodigestor::ler_sulfidrico()
{
    if(pinos.pin_mq136==-1)
        return 0;
    unsigned long soma=0;
    for(uint16_t i=0;i<1000;i++)
        soma+=analogRead(pinos.pin_mq136);
    soma = soma/1000;
    float sensor_value= filter_sulfidrico.filter(soma);
    sensor_value = sensor_value*(5.0/1023.0); 
    sensor_value = (5.0-sensor_value)/sensor_value;
    float ratio=sensor_value/calibragem.sulfidrico;
    if(ratio<0)ratio=0;
    //int ppm=int(pow(10,(log10(ratio) - (b)) / (m))+0.5);
    float ppm=pow(10,(log10(ratio) - (-0.22915)) / (-0.2715));
    ppm=constrain(ppm,0,400);    
    return ppm;
}

int Biodigestor::ler_carbono()
{ 
    if(pinos.pin_mhz_rx==-1||pinos.pin_mhz_tx==-1)
        return 0;
    SoftwareSerial s_mhz(pinos.pin_mhz_tx,pinos.pin_mhz_rx);
    MHZ19 mhz;
    s_mhz.begin(9600);
    s_mhz.listen();
    mhz.begin(s_mhz);
    return mhz.getCO2()+calibragem.carbono;
}
