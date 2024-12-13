/*
*   Tom Zhou 10/12/24/ Parser implementation
*/

#include <string>
#include <iostream>
#include <sstream>
#include "parser.h"

using namespace std;

/* 
*  parseRString
*  read user input and save it as r string
*  input: istream user input
*  output: string (rstring)
*/
string parseRString(istream &input) {
    string a; 
    string fullstring = "{ "; 
    int isBalanced = 1; 
    input >> a;
    if (a == "}")
    {
        return fullstring + "}";  
    } 
    while  (isBalanced > 0) 
    { 
        if (a == "{")
        {
            isBalanced++;
        }
        else if ( a== "}")
        {
            isBalanced--; 
            if (isBalanced == 0) 
            {
                return fullstring + "}";  
            }
        }
        
        fullstring += a + " "; 
        input >> a;
        
    }
    return "ERROR, INCORRECT FORMAT\n"; 
}




