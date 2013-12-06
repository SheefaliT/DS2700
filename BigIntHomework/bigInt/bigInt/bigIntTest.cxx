/*
 This is a simple testing framework for the bigInt class as part of HW3.
 
 Please be sure to set the variables to suit your needs - if you are on
 Windows or you see some weird characters in the output, please set the
 COLORS variable to false. If you want extended output (to see exactly
 what tests are being run), set VERBOSE to true.
 
 In order to compile and run this script, please put this file in the
 same directory as your bigInt.cpp and  run these commands:
 
 g++ -c bigInt.cpp -o bigInt.o
 g++ bigIntTest.cpp bigInt.o -o bigIntTest
 ./bigIntTest
 
 Or you can do it all in one line:
 
 g++ -c bigInt.cpp -o bigInt.o && g++ bigIntTest.cpp bigInt.o -o bigIntTest && ./bigIntTest
 
 That's all there is to it! Please give it a test and let me know if you
 find any bugs. Keep in mind that strange output may be the result of a
 bug in your bigInt class and NOT a bug in this testing framework!
 
 written by Jay Hendren james.hendren@colorado.edu 7/26/2013
 */

#include "bigInt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <iostream>
using namespace std;

// USER-EDITABLE VALUES; CHANGE THESE TO AFFECT OUTPUT
bool COLORS       = true; // CHANGE THIS TO FALSE IF YOU ARE USING WINDOWS
bool VERBOSE      = false;
int WIDTH         = 50; // number of characters wide for the output

// GLOBAL VARIABLES; DO NOT EDIT THESE
string OK         = " OK ";
string FAIL       = "FAIL";
string TRIED      = "Tried:     ";
string EXPECT     = "Expected:  ";
string GOT        = "Got:       ";

// colors!
string DCOLOR     = "\033[0m";
string GREEN      = "\033[0;32m";
string RED        = "\033[0;31m";

// variable declarations
int num_success   = 0;
int num_failure   = 0;

// a function for printing headers at the start of a suite of tests
void HEADER(string suite_name) {
    // cout << string(WIDTH, '*') << endl;
    cout << suite_name << endl;
    cout << string(WIDTH, '*') << endl;
    cout << endl;
}

// a function for printing tried-expected-got messages
void LOG(string tried, string expect, string got) {
    if (!VERBOSE) { return; }
    cout << TRIED << tried << endl;
    cout << EXPECT << expect << endl;
    cout << GOT << got << endl;
    cout << endl;
}

// a function for printing success/failure messages to the screen
void LOG_MSG(string msg, bool ok) {
    string status;
    if (ok) { status = OK; num_success++; }
    else { status = FAIL; num_failure++; }
    // yay c strings and printf for nice formatting!
    printf("%-*s[%s]\n\n", WIDTH, msg.c_str(), status.c_str());
}

// a function for turning things into strings (useful for doubles)
template<typename T>
string toString(T val)
{
    stringstream ss("");
    ss << val;
    return ss.str();
}

// a structure for storing our favorite numbers
class number {
public:
    int integer;
    double dub;
    string str;
    const char* charray;
    bigInt* bint;
    number() {};
    number(double input) {
        dub = input;
        integer = input;
        str = toString(integer);
        charray = str.c_str();
        bint = new bigInt(charray);
        // bint = new bigInt();
    }
};


// Here is the meaty part!

// a structure for automatically constructing and testing bigInts
template <typename T>
bool test_constructor(T input, string compare, string try_msg) {
    // construct a bint using the input
    bigInt* bint = new bigInt(input);
    // compare our bint to how it is expected to look
    char* charray = bint->getBigIntArray();
    bool ok = (strcmp(compare.c_str(), charray) == 0);
    // get rid of that stuff in memory
    bint->~bigInt();
    
    // now we can print the output
    LOG(try_msg, compare, charray);
    
    // and give the result
    return ok;
}

// representatives of our favorite operators...

class Plus {
public:
    string sym;
    Plus() { sym = "+"; }
    template <typename T>
    T operator()(T lv, T rv) {
        return lv + rv;
    }
};

class Minus {
public:
    string sym;
    Minus() { sym = "-"; }
    template <typename T>
    T operator()(T lv, T rv) {
        return lv - rv;
    }
};

template <typename T>
bool test_math_oper(const number& op1, const number& op2, T oper) {
    // run the calculation
    bigInt result = oper(*(op1.bint), *(op2.bint));
    
    // test to see if everything went well
    const char* actual = result.getBigIntArray();
    string actualstr = string(actual);
    const char* expect = toString(oper(op1.integer, op2.integer)).c_str();
    string expectstr = string(expect);
    bool ok = (strcmp(expect, actual) == 0);
    
    // print the results
    LOG(op1.str + " " + oper.sym + " " + op2.str, expectstr, actualstr);
    return ok;
}

class PlusEquals {
public:
    string sym;
    PlusEquals() { sym = "+="; }
    template <typename T>
    T operator()(T lv, T rv) {
        lv += rv;
        return lv;
    }
};

class MinusEquals {
public:
    string sym;
    MinusEquals() { sym = "-="; }
    template <typename T>
    T operator()(T lv, T rv) {
        lv -= rv;
        return lv;
    }
};

template <typename T>
bool test_mod_oper(const number& op1, const number& op2, T oper) {
    // run the calculation
    bigInt result = bigInt(op1.charray);
    result = oper(result, *(op2.bint));
    
    // test to see if everything went well
    const char* actual = result.getBigIntArray();
    string actualstr = string(actual);
    const char* expect = toString(oper(op1.integer, op2.integer)).c_str();
    string expectstr = string(expect);
    bool ok = (strcmp(expect, actual) == 0);
    
    // print the results
    LOG(op1.str + " " + oper.sym + " " + op2.str, expectstr, actualstr);
    return ok;
}

// a function for testing assignment
bool test_assign(const number& op1) {
    // assign the value
    bigInt bint1 = *(op1.bint);
    
    // did it go as expected?
    const char* actual = bint1.getBigIntArray();
    string actualstr = string(actual);
    const char* expect = op1.charray;
    string expectstr = string(expect);
    bool ok = (strcmp(expect, actual) == 0);
    
    // print the results
    LOG("bigInt = bigInt(" + op1.str + ")", expectstr, actualstr);
    return ok;
}

// operator tests...

class Equals {
public:
    string sym;
    Equals() { sym = "=="; }
    template <typename T>
    bool operator()(T lv, T rv) {
        return lv == rv;
    }
};

class NotEquals {
public:
    string sym;
    NotEquals() { sym = "!="; }
    template <typename T>
    bool operator()(T lv, T rv) {
        return lv != rv;
    }
};

class GreaterThan {
public:
    string sym;
    GreaterThan() { sym = ">"; }
    template <typename T>
    bool operator()(T lv, T rv) {
        return lv > rv;
    }
};

class GreaterThanEqual {
public:
    string sym;
    GreaterThanEqual() { sym = ">="; }
    template <typename T>
    bool operator()(T lv, T rv) {
        return lv >= rv;
    }
};

class LessThan {
public:
    string sym;
    LessThan() { sym = "<"; }
    template <typename T>
    bool operator()(T lv, T rv) {
        return lv < rv;
    }
};

class LessThanEqual {
public:
    string sym;
    LessThanEqual() { sym = "<="; }
    template <typename T>
    bool operator()(T lv, T rv) {
        return lv <= rv;
    }
};

template <typename T>
bool test_oper(const number& op1, const number& op2, T oper) {
    bool result = oper(*(op1.bint), *(op2.bint));
    string actual;
    string expect;
    (result) ? actual = "true" : actual = "false";
    (oper(op1.integer, op2.integer)) ? expect = "true" : expect = "false";
    LOG(op1.str + " " + oper.sym + " " + op2.str, expect, actual);
    return expect == actual;
}

int main() {
    // let's get those colors going!
    if (COLORS) { OK = GREEN + OK + DCOLOR; FAIL = RED + FAIL + DCOLOR; }
    
    // now let's get some variables declared that we'll use for the test
    number none;
    none.str = "";
    none.charray = none.str.c_str();
    
    number zero(0.0);
    number some(140.0);
    number alot(21046.346);
    number many(13487.1234);
    number afew(3.0);
    
    // finally let's start running tests
    
    cout << string(WIDTH, '*') << endl;
    HEADER("BEGIN TEST");
    
    // constructors
    
    HEADER("Constructors");
    
    // default constructor
    
    bigInt* bint0 = new bigInt();
    char* out = bint0->getBigIntArray();
    bint0->~bigInt();
    
    LOG("bigInt();", "0", out);
    LOG_MSG("Testing the default constructor...", strcmp(out, zero.str.c_str()) == 0);
    
    // char array constructor
    
    LOG_MSG("Testing the char array constructor...",
            test_constructor(none.charray, none.charray, "bigInt(\"" + none.str + "\")") &&
            test_constructor(zero.charray, zero.charray, "bigInt(\"" + zero.str + "\")") &&
            test_constructor(afew.charray, afew.charray, "bigInt(\"" + afew.str + "\")") &&
            test_constructor(alot.charray, alot.charray, "bigInt(\"" + alot.str + "\")")
            );
    
    // int constructor
    
    LOG_MSG("Testing the int constructor...",
            test_constructor(zero.integer, zero.charray, "bigInt(" + zero.str + ")") &&
            test_constructor(afew.integer, afew.charray, "bigInt(" + afew.str + ")") &&
            test_constructor(many.integer, many.charray, "bigInt(" + many.str + ")")
            );
    
    // double constructor
    
    LOG_MSG("Testing the double constructor...",
            test_constructor(zero.dub, zero.charray, "bigInt(" + zero.str + ".0)") &&
            test_constructor(afew.dub, afew.charray, "bigInt(" + afew.str + ".0)") &&
            test_constructor(some.dub, some.charray, "bigInt(" + some.str + ".0)")
            );
    
    // copy constructor
    
    LOG_MSG("Testing the copy constructor...",
            test_constructor(*(zero.bint), zero.charray, "bigInt( bigInt(" + zero.str + ") )") &&
            test_constructor(*(afew.bint), afew.charray, "bigInt( bigInt(" + afew.str + ") )") &&
            test_constructor(*(alot.bint), alot.charray, "bigInt( bigInt(" + alot.str + ") )")
            );
    
    
    
    
    // // destructor
    
    // HEADER("Destructor");
    
    
    
    // operators
    
    // HEADER("Operators");
    
    // addition
    
    HEADER("Addition");
    
    LOG_MSG("Testing the + operator...",
            test_math_oper(zero, zero, Plus()) &&
            test_math_oper(afew, zero, Plus()) &&
            test_math_oper(zero, some, Plus()) &&
            test_math_oper(many, alot, Plus()) &&
            test_math_oper(number(rand() % 10000000), number(rand() % 10000000), Plus())
            );
    
    LOG_MSG("Testing the += operator...",
            test_mod_oper(zero, zero, PlusEquals()) &&
            test_mod_oper(afew, zero, PlusEquals()) &&
            test_mod_oper(zero, many, PlusEquals()) &&
            test_mod_oper(some, alot, PlusEquals()) &&
            test_mod_oper(number(rand() % 10000000), number(rand() % 10000000), PlusEquals())
            );
    
    
    
    // subtraction
    
    HEADER("Subtraction");
    
    LOG_MSG("Testing the - operator...",
            test_math_oper(zero, zero, Minus()) &&
            test_math_oper(afew, zero, Minus()) &&
            test_math_oper(some, afew, Minus()) &&
            test_math_oper(some, some, Minus()) &&
            test_math_oper(alot, many, Minus()) &&
            test_math_oper(number(rand() % 10000 + 1000), number(rand() % 1000), Minus())
            );
    
    LOG_MSG("Testing the -= operator...",
            test_mod_oper(zero, zero, MinusEquals()) &&
            test_mod_oper(afew, zero, MinusEquals()) &&
            test_mod_oper(some, afew, MinusEquals()) &&
            test_mod_oper(some, some, MinusEquals()) &&
            test_mod_oper(alot, many, MinusEquals()) &&
            test_mod_oper(number(rand() % 10000 + 1000), number(rand() % 1000), MinusEquals())
            );
    
    
    
    
    // assignment
    
    HEADER("Assignment");
    
    LOG_MSG("Testing the = operator...",
            test_assign(zero) &&
            test_assign(afew) &&
            test_assign(some) &&
            test_assign(many) &&
            test_assign(number(rand()))
            );
    
    
    
    
    // comparison
    
    HEADER("Comparison");
    
    // equals
    
    LOG_MSG("Testing the == operator...",
            test_oper(zero, zero, Equals()) &&
            test_oper(zero, some, Equals()) &&
            test_oper(alot, afew, Equals()) &&
            test_oper(many, many, Equals()) &&
            test_oper(afew, afew, Equals()) &&
            test_oper(number(rand()), number(rand()), Equals())
            );
    
    // not equal to
    
    LOG_MSG("Testing the != operator...",
            test_oper(zero, zero, NotEquals()) &&
            test_oper(zero, some, NotEquals()) &&
            test_oper(alot, afew, NotEquals()) &&
            test_oper(many, many, NotEquals()) &&
            test_oper(afew, afew, NotEquals()) &&
            test_oper(number(rand()), number(rand()), NotEquals())
            );
    
    // less than/equal to
    
    LOG_MSG("Testing the < operator...",
            test_oper(zero, zero, LessThan()) &&
            test_oper(zero, some, LessThan()) &&
            test_oper(alot, afew, LessThan()) &&
            test_oper(many, many, LessThan()) &&
            test_oper(afew, afew, LessThan()) &&
            test_oper(number(rand()), number(rand()), LessThan())
            );
    
    // less than
    
    LOG_MSG("Testing the <= operator...",
            test_oper(zero, zero, LessThanEqual()) &&
            test_oper(zero, some, LessThanEqual()) &&
            test_oper(alot, afew, LessThanEqual()) &&
            test_oper(many, many, LessThanEqual()) &&
            test_oper(afew, afew, LessThanEqual()) &&
            test_oper(number(rand()), number(rand()), LessThanEqual())
            );
    
    // greater than/equal to
    
    LOG_MSG("Testing the > operator...",
            test_oper(zero, zero, GreaterThan()) &&
            test_oper(zero, some, GreaterThan()) &&
            test_oper(alot, afew, GreaterThan()) &&
            test_oper(many, many, GreaterThan()) &&
            test_oper(afew, afew, GreaterThan()) &&
            test_oper(number(rand()), number(rand()), GreaterThan())
            );
    
    // greater than
    
    LOG_MSG("Testing the >= operator...",
            test_oper(zero, zero, GreaterThanEqual()) &&
            test_oper(zero, some, GreaterThanEqual()) &&
            test_oper(alot, afew, GreaterThanEqual()) &&
            test_oper(many, many, GreaterThanEqual()) &&
            test_oper(afew, afew, GreaterThanEqual()) &&
            test_oper(number(rand()), number(rand()), GreaterThanEqual())
            );
    
    
    
    cout << "Number of tests passed: " << num_success << endl;
    cout << "Number of tests failed: " << num_failure << endl;
    cout << "Total number of tests:  " << num_success + num_failure << endl;
    
    return num_failure;
}
