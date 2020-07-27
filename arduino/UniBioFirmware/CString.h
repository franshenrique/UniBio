#ifndef CString_h
#define CString_h
#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
class CString
{
    private:
        char* string;
        unsigned int len;
    public:
    
        CString();//
        CString(char* string);//
        CString(const char* string);//
        CString(int & s_int);//
        CString(float & s_float);//
        CString(CString & cstring);//
        ~CString();//
        
        void erase();
        
        void concat(char * cat_string);//
        void concat(const char * cat_string);//
        void concat(int num);//
        void concat(char c);//
        void concat(float num);//
        void concat(CString & cstring);//
        void concat(const CString & cstring);//
        void concat(String  & string);//
        void concat(const String  & string);//
        
        int toInt();
        float toFloat();

        int equals(char * str);
        int equals(const char * str);
        int equals(String& str);
        int equals(CString& str);
        
        
        char* split(char* tok,bool first);//
        char* split(char tok,bool first);//
        
        char* c_str();   //
        unsigned int length();//
};


#endif
