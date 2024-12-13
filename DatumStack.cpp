/*
*   Tom Zhou 10/12/24/ DatumStack implementation
*/
#include <string>
#include <istream>
#include <list>
#include "DatumStack.h"

using namespace std; 

/* 
*  default constructor
*  creates an instance of DatumStack class
*  input: /
*  output:/
*/
DatumStack::DatumStack() {}

/* 
*  constructor
*  creates an instance of DatumStack class
*  input: Datum Array, and size of array
*  output:/
*/
DatumStack::DatumStack(Datum array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        DataStack.push_back(array[i]); 
    }
}

/* 
*  isEmpty
*  check if DatumStack is empty
*  input: /
*  output: true/false
*/
bool DatumStack::isEmpty()
{
    return DataStack.empty(); 
}

void DatumStack::clear()
{
    return DataStack.clear(); 
}

/* 
*  Size
*  check DatumStack's'
*  input: /
*  output: number of size of DatumStack
*/
int DatumStack::size()
{
    return DataStack.size(); 
}

/* 
*  top
*  check the top of DatumStack
*  input: /
*  output: the top datum of the datum struct
*/
Datum DatumStack::top()
{
    if (isEmpty())
    {
        throw runtime_error ("empty_stack"); 
    }
    return DataStack.back(); 
}

/* 
*  pop
*  deletes the top datum of the stack
*  input: /
*  output:/
*/
void DatumStack::pop()
{
    if (isEmpty())
    {
        throw runtime_error ("empty_stack"); 
    }
    DataStack.pop_back(); 
}

/* 
*  push
*  adds a datum to the top of the stack
*  input: a datum
*  output: /
*/
void DatumStack::push(Datum data)
{
    DataStack.push_back(data); 
}