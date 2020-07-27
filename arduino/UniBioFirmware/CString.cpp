#include "CString.h"

CString::CString()
{
    string=(char*)malloc(1);
    string[0]='\0';
    len=0;
}

CString::CString(int& num)
{
    this->string=(char*)malloc(1);
    this->string[0]='\0';
    len=0;
    concat(num);
}
CString::CString(float& num)
{
    this->string=(char*)malloc(1);
    this->string[0]='\0';
    len=0;
    concat(num);
}
CString::CString(char* string)
{
    this->string=(char*)malloc(1);
    this->string[0]='\0';
    len=0;
    concat(string);
}
CString::CString(const char* string)
{
    this->string=(char*)malloc(1);
    this->string[0]='\0';
    len=0;
    concat(string);
}
CString::CString(CString& cstring){
    this->string=(char*)malloc(1);
    this->string[0]='\0';
    len=0;
    this->concat(cstring);
}
CString::~CString()
{
    free(string);
}

void CString::erase()
{
    free(string);
    string=(char*)malloc(1);
    string[0]='\0';
    len=0;
}

void CString::concat(char* cat_string)
{
    len+=strlen(cat_string);
    string=(char*)realloc(string,len+1);
    strcat(string,cat_string);
}
void CString::concat(const char* cat_string)
{
    len+=strlen(cat_string);
    string=(char*)realloc(string,len+1);
    strcat(string,cat_string);
}
void CString::concat(int num)
{
    char s_int[6];
    sprintf(s_int,"%d",num);
    concat(s_int);
}
void CString::concat(char c)
{
    char s_char[2]=" ";
    s_char[0]=c;
    concat(s_char);
}
void CString::concat(float num)
{
    char s_float[15];
    long i_num=num*100;
    sprintf(s_float,"%ld.%.2ld",i_num/100,i_num%100);
    concat(s_float);
}
void CString::concat(const CString& cstring)
{
    this->concat(cstring.c_str());
}
void CString::concat(CString& cstring)
{
    this->concat(cstring.c_str());
}
void CString::concat(String& string)
{
    concat(string.c_str());
}
void CString::concat(const String& string)
{
    concat(string.c_str());
}
int CString::toInt()
{
    return atoi(string);
}
float CString::toFloat()
{
    return atof(string);
}
int CString::equals(const char* str)
{
  if(!strcmp(string,str))
    return 1;
  else
    return 0;
}
int CString::equals(char* str)
{
  if(!strcmp(string,str))
    return 1;
  else
    return 0;
}
int CString::equals(CString & str)
{
  if(!strcmp(string,str.c_str()))
    return 1;
  else
    return 0;
}
int CString::equals(String & str)
{
  if(!strcmp(string,str.c_str()))
    return 1;
  else
    return 0;
}
char* CString::split(char* tok,bool first)
{
    if(first)
        return strtok(string,tok);
    else
        return strtok(NULL,tok);
}
char* CString::split(char tok,bool first)
{
    char s_tok[2]=" ";
    s_tok[0]=tok;
    if(first)
        return strtok(string,s_tok);
    else
        return strtok(NULL,s_tok);
}
char* CString::c_str()
{
    return string;
}

unsigned int CString::length()
{
    return len;
}
