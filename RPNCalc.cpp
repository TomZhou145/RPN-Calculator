/*
*   Tom Zhou 10/12/24/ RPNCalc implementation
*/

#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <iostream>


#include "RPNCalc.h"
#include "DatumStack.h"
#include "Datum.h"
#include "parser.h"
using namespace std;

/*
 * Name: got_int
 * Purpose: determines if a string contains an integer and loads said
 *           integer into an integer variable whose address has been
 *           passed to this function
 * Parameters: a string to check if it contains an integer as well as
 *              a pointer to an integer to load in the event an
 *              integer can be parsed from said string
 * Returns: a boolean where true indicates an integer was successfully
 *           parsed from the provided string (and therefore the
 *           addressed integer has been loaded) and false indicates
 *           an integer could not be read
 * Effects: the integer pointed to by the passed pointer will be updated
 *           with the integer parsed from the string in the event true
 *           is returned (otherwise nothing happens)
 * Author: Mark A. Sheldon, Tufts University, Fall 2016
 * Note to students: you do not have to modify this comment!
 */
bool RPNCalc::got_int(string s, int *resultp)
{
    /* Holds the first non-whitespace character after the integer */
    char extra;
    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}


/* RPNCalc
* Constructor
*/
RPNCalc::RPNCalc()
{
    DatumStack CalcStack;
}
/* RPNCalc
* Destructor
*/
RPNCalc::~RPNCalc(){}

/* Run
* Run function that activates the calculator
* input : none
* output : none 
*/
void RPNCalc::run() 
{
    user_command(cin); 
    cerr << "Thank you for using CalcYouLater.\n";
    return;
}

/* User Command
* Takes in user command repeatedly that keeps the calculator running
* input : istream input
* output : none 
*/
void RPNCalc::user_command(istream &input)
{
    string in = "";
    int num;
    
    while (input >> in and in != "quit" )
    { 
        if (got_int(in, &num))
        {
            Datum int_datum(num);
            DS.push(int_datum);
        }
        else if (in == "#f" or in == "#t" or in == "not" or in == "print")
        {
            exec_command1(in);
        }
        else if (in == "{")
        {
            Datum rstring_datum(parseRString(input));
            DS.push(rstring_datum);
        }
        else if (in == "clear" or in == "dup" or in == "drop" or in == "swap")
        {
            exec_command2(in);
        }
        else if (in== "+" or in== "-" or in== "*" or in== "/" or in == "mod")
        {
            math(in);
        }
        else if (in=="<" or in==">" or in=="<=" or in==">=" or in == "==") 
        {
            Bool(in); 
        }
        else if (in == "exec")
        {
            exec();
        }
        else if (in == "file")
        {
            file(); 
        }
        else if (in == "if")
        {
            If(); 
        }
        else
        {
            cerr << in << ": unimplemented\n";
        }
    }
}

/*push_bool
 * A helper function that pushes boolean input into the DatumStack
 * input: the user input true/false string
 * output: \
 */
void RPNCalc::push_bool(string in)
{
    if (in == "#t")
    {
        Datum bool_datum(true);
        DS.push(bool_datum);
    }
    if (in == "#f")
    {
        Datum bool_datum(false);
        DS.push(bool_datum);
    }
    return;
}

/* push_not
* runs the functionality for the not option
* input : none
* output : none 
*/
void RPNCalc::push_not()
{
    // true -> false
    if (DS.isEmpty())
    {
        cerr << "Error: empty_stack\n";
        return;  
    }
    if (DS.top().isBool())
    {
        if (DS.top().getBool())
        {
            DS.pop();
            Datum bool_datum(false);
            DS.push(bool_datum);
        }
        // false -> true
        else
        {
            DS.pop();
            Datum bool_datum(true);
            DS.push(bool_datum);
        }
    }
    else 
    {
        cerr << "Error: datum_not_bool\n"; 
        return; 
    }
    return;
}

/* print
* prints the top of the stack
* input : none
* output : none 
*/
void RPNCalc::print()
{
    if (DS.isEmpty())
    {
        cerr << "Error: empty_stack\n";
        return;
    }
    else {
        if (DS.top().isInt())
        {
            cout << DS.top().getInt() << endl;
        }
        else if (DS.top().isBool())
        {
            if (DS.top().getBool())
            {
                cout << "#t\n";
            }
            else if (not DS.top().getBool())
            {
                cout << "#f\n";
            }
        }
        else if (DS.top().isRString())
        {
            cout << DS.top().getRString() << endl;
        }
    }
}

/* exec_command1
* runs the functionality for #t,#f,not,and print
* input : user command in string form
* output : none 
*/
void RPNCalc::exec_command1(string in)
{
    if (in == "#t" or in == "#f")
    {
        push_bool(in);
    }
    else if (in == "not")
    {
        push_not();
    }
    else if (in == "print")
    {
        print();
    }
}

/* exec_command1
* runs the functionality for clear dup drop and swap
* input : user command in string form
* output : none 
*/
void RPNCalc::exec_command2(string in)
{
    if (in == "clear")
    {
        DS.clear();
    }
    if (in == "dup")
    {
        if (DS.isEmpty())
        {
            cerr << "Error: empty_stack\n";
            return;
        }
        Datum dup = DS.top();
        DS.push(dup);
    }
    if (in == "drop")
    {
        if (DS.isEmpty())
        {
            cerr << "Error: empty_stack\n";
            return;
        }
        DS.pop();
    }
    if (in == "swap")
    {
        if (DS.size() < 2)
        {
            cerr << "Error: empty_stack\n";
            if (DS.size() == 1)
            {
                DS.pop(); 
            }
            return;
        }
        Datum temp_top = DS.top();
        DS.pop();
        Datum temp_next = DS.top();
        DS.pop(); 
        DS.push(temp_top); 
        DS.push(temp_next);
    }
}

/* math
* helper function that process user input for math operations 
* and comparing operations
* input : user command in string form
* output : none 
*/
void RPNCalc::math(string in)
{
    if (DS.size() >= 2) {
        int sec, fir; 
        Datum second = DS.top();
        DS.pop();
        Datum first = DS.top();
        DS.pop(); 
        if (second.isInt() and first.isInt()){
            sec = second.getInt();
            fir = first.getInt(); 
            operation(fir,sec,in);  
        }  
        else {
            cerr << "Error: datum_not_int\n";
        }
    }
    else {
        cerr << "Error: empty_stack\n";
        if(DS.size()==1)
        {
        DS.pop(); 
        }
    }
}

/* operation
* function that process +, -, /, and % 
* and comparing operations
* input : user command in string form, and the first and second integer
* output : none 
*/
void RPNCalc::operation(int fir,int sec, string in) {
    int result; 
    if (in == "+") {
        result = fir + sec; 
    }
    else if (in == "-") {
        result = fir - sec; 
    }
    else if (in == "*") {
        result = fir * sec; 
    }
    else if (in == "/") {
        if (sec == 0)
        {
            cerr << "Error: division by 0.\n"; 
            return;
        }
        result = fir / sec; 
    }
    else if (in == "mod") {
        if (sec == 0)
        {
            cerr << "Error: division by 0.\n"; 
            return; 
        }
        result = fir % sec;  
    }
    else{
        return; 
    }
    Datum int_datum(result);
    DS.push(int_datum);
}

/* bool]
* function that process < =< > => == operations and 
* and comparing operations
* input :user command in string form, and the first and second integer
* output : none 
*/
void RPNCalc::Bool(string in)
{
    if (DS.size() >= 2) {
        
        Datum sec = DS.top();
        DS.pop();
        Datum fir = DS.top();
        DS.pop(); 
        bool_operation(fir,sec,in);  
    }
    else {
        cerr << "Error: empty_stack\n";
        if(DS.size()==1)
        {
        DS.pop(); 
        }
    }
}
/* bool_operation
* function that process < =< > => == operations
* and comparing operations
* input :user command in string form, and the first and second integer
* output : none 
*/
void RPNCalc::bool_operation(Datum fir,Datum sec,string in)
{
    bool result = false;
    if (in == "<" or in == ">" or in == ">=" or in == "<=") {
        if (fir.isInt() and sec.isInt()) {
            int fir_int = fir.getInt(); 
            int sec_int = sec.getInt(); 
            if (in == "<") { 
                result = (fir < sec);
            }
            else if (in == "<=") {
                result = (fir_int <= sec_int);
            }
            else if (in == ">") {
                result = (fir_int > sec_int);
            }
            else if (in == ">=") {
                result = (fir_int >= sec_int);
            }
            else if (in == "==") {
                result = (fir == sec);
            }
        }
        else {
            cerr << "Error: datum_not_int\n"; 
            return; 
        }
    }
    if (in == "==") {
        if (fir.isInt() and sec.isInt()) {
            result = (fir == sec); 
        }
        else if (fir.isInt() or sec.isInt()) {
            result = false; 
        }
        else {
            result = (fir == sec); 
        }
    }
    Datum bool_datum(result);
    DS.push(bool_datum);
    return; 
}

/* exec
* function that process exec operation
* 
* input :none
* output : none 
*/
void RPNCalc::exec() {
    if (DS.size() > 0) {
        if (DS.top().isRString())
        {
            istringstream rstring_command(DS.top().getRString());
            string clean = clean_rString(rstring_command); 
            istringstream rstring_cleaned(clean);
            user_command(rstring_cleaned);
        }
        else
        {
            cerr << "Error: cannot execute non rstring\n"; 
            DS.pop(); 
        }
    }
    else
    {
        cerr << "Error: empty_stack\n"; 
    }
}

/* clean_rsString
* helper function that cleans rString into readable string
* 
* input :rstring converted to istream
* output : the content of rstring in string form. 
*/
string RPNCalc::clean_rString(istream &input)
{
    string bracket; 
    string cleaned_string; 
    int isBalanced = 1;
    input >> bracket;
    while (isBalanced > 0)
    {
    string in;
    input >> in; 
    if (in == "{")
    {
        isBalanced++; 
    }
    if (in == "}")
    {
        isBalanced--; 
        if (isBalanced == 0)
        {
        return cleaned_string; 
        }
    }
    cleaned_string = cleaned_string + in + " "; 
    }
    return cleaned_string; 
}

/* file
* execute the user's file operation
* 
* input : none
* output : none
*/
void RPNCalc::file()
{
    if (DS.size() > 0) 
    {
        if (DS.top().isRString())
        {
            istringstream rstring_command(DS.top().getRString());   
            string clean = clean_rString(rstring_command); 
            clean = clean.substr(0, clean.size() - 1); 
            ifstream rstring_file(clean);
            if (not rstring_file) {
                cerr << "Unable to read " << clean << endl;
                DS.pop(); 
                return;
            }
            DS.pop(); 
            user_command(rstring_file); 
        }
        else
        {
            cerr << "Error: file operand not rstring\n"; 
            DS.pop(); 
            return; 
        }
    }
    else
    {
        cerr << "Error: empty_stack\n"; 
        return; 
    }
}

/* if
* execute the user's if operation
* 
* input : none
* output : none
*/
void RPNCalc::If()
{
    if (DS.size() > 2) {
        if (DS.top().isRString()) 
        {
        Datum falseCase = DS.top(); 
        Datum trueCase = falseCase; 
        Datum testCondition = falseCase;
        DS.pop();
            if (DS.top().isRString()) {
                trueCase = DS.top(); 
                DS.pop(); 
                    if (DS.top().isBool()) {
                        testCondition = DS.top();
                        DS.pop(); 
                        if_execute(falseCase,trueCase,testCondition); 
                    }
                    else {
                        cerr << "Error: expected boolean in if test\n"; 
                        DS.pop();
                        
                        
                        return;
                    }
            }
            else {
                cerr << "Error: expected rstring in if branch\n"; 
                DS.pop();
                DS.pop();  
                return; 
            }
        }
        else {
            cerr << "Error: expected rstring in if branch\n";
            DS.pop();
                DS.pop(); 
                DS.pop(); 
            return; 
        }
    }
    else {
        cerr << "Error: empty_stack\n"; 
        return; 
    }
}

/* if_execute
* helper function that execute 
*the selective cased R string based on the if function
* 
* input : true case rString, false case rString, and bool result
* output : none
*/
void RPNCalc::if_execute(Datum falseCase,Datum trueCase,Datum Bool){
    if (Bool.getBool())
    {
        istringstream rstring_command(trueCase.getRString());
        string clean = clean_rString(rstring_command); 
        istringstream rstring_cleaned(clean);
        user_command(rstring_cleaned);
        return; 
    }
    else if (not Bool.getBool())
    {   
        istringstream rstring_command(falseCase.getRString());
        string clean = clean_rString(rstring_command); 
        istringstream rstring_cleaned(clean);
        user_command(rstring_cleaned);
        return; 
    }
}