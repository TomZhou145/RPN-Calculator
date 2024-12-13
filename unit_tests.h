#include "DatumStack.h"
#include "Datum.h"
#include "parser.h"
#include <sstream>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>

using namespace std;

//Default constructor empty test
void Default_DatumStack_EMPTY_SIZE() {
    DatumStack Empty; 
    assert(Empty.isEmpty()); 

    assert(Empty.size() == 0); 
}

//push test
void Default_PUSH_TEST() {
    Datum int3(3); 
    Datum intTest3(3); 
    DatumStack Empty; 
    Empty.push(int3); 

    assert(not Empty.isEmpty()); 
    assert(Empty.size() == 1); 

    assert(Empty.top() == intTest3);

    Empty.pop();
    assert(Empty.isEmpty()); 

    assert(Empty.size() == 0); 
}

//pop test
void DEFAULT_POP_TEST() {
    Datum int3(3); 
    Datum intTest3(3); 
    DatumStack Empty; 
    Empty.push(int3); 
    Empty.pop();
    assert(Empty.isEmpty()); 

    assert(Empty.size() == 0); 
}

//pop error test
void Default_DatumStack_POP_ERROR() {
    DatumStack Empty; 
    string error_message; 
    bool error = false; 

    try
    {
        Empty.pop();
    }

    catch (runtime_error &e)
    {
        error = true;
        error_message = e.what();
    }
    assert(error_message == "empty_stack");
}

//top error test
void Default_DatumStack_TOP_ERROR() {
    DatumStack Empty; 
    string error_message; 
    bool error = false; 

    try
    {
        Empty.top();
    }

    catch (runtime_error &e)
    {
        error = true;
        error_message = e.what();
    }
    assert(error_message == "empty_stack");
}   

//a full cycle of operations test
void PARA_CONSTRUCTOR_EMPTY_POP_SIZE_PUSH_CYCLE() {
    Datum int4(4);
    Datum int5(5);
    Datum boolT(true);
    Datum boolF(false);
    Datum STR("string"); 
    Datum array[5] = {int4,int5,boolT,boolF,STR}; 
    DatumStack DS(array, 5); 
    assert(not DS.isEmpty()); 
    assert(DS.size() == 5); 
    assert(DS.top() == STR); 
    DS.pop();
    assert(not DS.isEmpty()); 
    assert(DS.size() == 4); 
    assert(DS.top() == boolF); 
    DS.pop();
    assert(not DS.isEmpty()); 
    assert(DS.size() == 3); 
    assert(DS.top() == boolT); 
    DS.pop();
    DS.pop();
    DS.pop();
    assert(DS.isEmpty()); 
    DS.push(int4);
    assert(not DS.isEmpty()); 
    assert(DS.top() == int4);
    }
    
//clear test
void CLEAR_TEST() {
    Datum int4(4);
    Datum int5(5);
    Datum boolT(true);
    Datum boolF(false);
    Datum STR("string"); 
    Datum array[5] = {int4,int5,boolT,boolF,STR}; 
    DatumStack DS(array, 5); 
    DS.clear(); 
    assert(DS.isEmpty()); 
}

//clear empty datastack test
void CLEAR_EMPTY_TEST() {
    DatumStack DS; 
    DS.clear();
    assert(DS.isEmpty());
} 

//regular parceRstring test
void parce() {
    ifstream infile("parce_test.txt"); 
    if (not infile.is_open()) { 
        cerr << "Error: Unable to open file\n"; 
        return;  
    }
    string test = parseRString(infile); 
    cerr << test << endl; 
    assert(test == "{ abcd }"); 
    infile.close(); 
}

//irregular formatted rstring test
void parce_stretched() {
    ifstream infile("parce_weird.txt"); 
    if (not infile.is_open()) { 
        cerr << "Error: Unable to open file\n"; 
        return;  
    }
    string test = parseRString(infile); 
    cerr << test << endl; 
    assert(test == "{ dj 12442 rt 451 + - + }"); 
    infile.close(); 
}

//empty rstring test
void parce_empty() {
    ifstream infile("empty.txt"); 
    if (not infile.is_open()) { 
        cerr << "Error: Unable to open file\n"; 
        return;  
    }
    string test = parseRString(infile); 
    cerr << test << endl; 
    assert(test == "{ }"); 
    infile.close(); 
}

void nested_parce() { 
    ifstream infile("nested.txt"); 
    if (not infile.is_open()) { 
        cerr << "Error: Unable to open file\n"; 
        return;  
    }
    string test = parseRString(infile); 
    cerr << test << endl; 
    assert(test == "{ one two { 1 + 2 } { cha cha cha } }"); 
    infile.close(); 
}


void isInt() {
    Datum boolT(true);
    boolT.getInt(); 
}