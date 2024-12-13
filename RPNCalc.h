/*
*   Tom Zhou 10/12/24/ RPNCalc Header
*/

#ifndef __RPNCALC_H
#define __RPNCALC_H

#include "DatumStack.h"

#include <string>
#include <istream>
#include <list>
#include <iostream>
#include <fstream>

using namespace std; 

class RPNCalc { 

    public:
        RPNCalc(); 
        ~RPNCalc();
        void run(); 
        void user_command(istream &input); 
        bool got_int(string s, int *resultp); 

    private: 
        void push_bool(string in);
        void push_not(); 
        void print(); 

        void exec_command1(string in); 
        void exec_command2(string in); 

        void math(string in); 
        void operation(int fir,int sec, string in); 
        void Bool(string in); 
        void bool_operation(Datum fir,Datum sec, string in);

        void exec(); 

        void file(); 

        void If();
        void if_execute(Datum falseCase,Datum trueCase,Datum Bool);
        string clean_rString(istream &input); 
        
        DatumStack DS; 
};

#endif