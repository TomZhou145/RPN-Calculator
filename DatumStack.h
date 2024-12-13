/*
*   Tom Zhou 10/12/24/ DatumStack header
*/
#ifndef __DATUMSTACK_H
#define __DATUMSTACK_H

#include "Datum.h"
#include <string>
#include <istream>
#include <list>
class DatumStack {
    public:
    DatumStack(); 
    DatumStack(Datum array[], int size); 

    bool isEmpty();
    void empty();
    int size();
    Datum top();
    void pop();
    void push(Datum data); 
    void clear(); 

    private:
    std::list<Datum> DataStack; 

};

#endif