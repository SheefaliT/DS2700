//
//  bigInt.cxx
//  bigInt
//
//  Created by Sheefali Tewari on 7/23/13.
//  Copyright (c) 2013 Sheefali Tewari. All rights reserved.
//  
#include<cassert>//provides assert
#include "bigInt.h" //big int class
#include <iostream> //we are adding ostream and istream
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;

//Default constructor
bigInt::bigInt()
{
	bigIntArray = new char[2];
	bigIntArray[0] ='0';
	bigIntArray[1] = '\0';
    
	//a 2 element array with an initial value of zero and a NULL
	//character  ie: 0th element is 0 and 1st element is NULL
}

//"c_str" constructor
bigInt::bigInt(const char initialValue [])
{
	bigIntArray = new char[strlen(initialValue + 1)];
	strcpy(bigIntArray, initialValue);
    
	//make your bigInt array equal to this c_str
	//being passed in  (i.e. use strlen to allocate
	//memory (remember to add +1 to it though for the null character...
	// and strcpy to copy the stuff over (strcpy adds the null automatically)
}

//"integer" constructor
bigInt::bigInt(int initialValue)
{
	int number = initialValue;
	int digits = 0;
	if (number < 0) digits = 1;
	while(number){
		number /=10;
		digits++;
	}
    
	bigIntArray = new char[digits+1];
	sprintf(bigIntArray, "%d", initialValue);
	//use a loop to count the numberOfDigits in initial value
	//Allocate that memory and copy it over (that good ol divide
	//by 10 and modulo 10 thing)
}

//"double" constructor
bigInt::bigInt (double initialValue)
{
	int number = int(initialValue);
	int digits = 0;
	if (number < 0 && number > -1) digits = 1;
	while(number){
		number /=10;
		digits++;
	}
    
	bigIntArray = new char[digits+1];
	sprintf(bigIntArray, "%d", int(initialValue));
    
	//very similar to the integer constructor strategy above
	//in fact you get this into an int and you can use the same
	//code...
}

//Copy Constructor
bigInt::bigInt (const bigInt& toCopyFrom)
{
	bigIntArray = toCopyFrom.getBigIntArray();
    
	//use the getBigIntArray on toCopyFrom to set bigIntArray of you object
	//remember to delete bigIntArray of your object BEFORE setting it
	//or else you'll get a memory leak
}

bigInt::~bigInt()
{
	delete [] bigIntArray;
	//delete your bigIntArray
}


//Returns a dynamically allocated copy tot he bigIntArray
char* bigInt::getBigIntArray() const
{
	//Implemented to help you.
    //RETURNS A POINTER TO A COPY of our bigIntArray
    //with memory already allocated. You can set this
    //to another char * etc.
	char *toReturn;
	toReturn=new char[strlen(bigIntArray)+1];
	strcpy(toReturn, bigIntArray);
	return toReturn;
}

//operator "="
void bigInt::operator = (const bigInt& toEqual)
{
	char *equal = toEqual.getBigIntArray();
    
	bigIntArray = new char[strlen(equal)+1];
	strcpy(bigIntArray, equal);
    
	//use getBigIntArray on toEqual to set your int array to
	//the intArray of toEqual
}

//operator "=="
bool operator ==(const bigInt &firstInt, const bigInt &secondInt)
{
	
	if (strlen(firstInt.getBigIntArray()) == strlen(secondInt.getBigIntArray()) &&
		strcmp(secondInt.getBigIntArray(), firstInt.getBigIntArray()) == 0){
		return true;
	}
	return false;
    
	//check to see if the bigIntArray's are equal
	//you can use strcmp for this
}

//operator !=
bool operator !=(const bigInt &firstInt, const bigInt &secondInt)
{
	char *intOne = firstInt.getBigIntArray();
	char *intTwo = secondInt.getBigIntArray();
	bool test = (strcmp(intTwo, intOne)!= 0);
	delete intOne;
	delete intTwo;
	return test;
	//easy once you've done ==
}

//operator <
bool operator <(const bigInt &firstInt, const bigInt &secondInt)
{
	if (strlen(firstInt.getBigIntArray()) > strlen(secondInt.getBigIntArray()))
	{
		return false;
	}
    
	else if (strlen(firstInt.getBigIntArray()) < strlen(secondInt.getBigIntArray()))
	{
		return true;
	}
    
	else if(strlen(firstInt.getBigIntArray()) == strlen(secondInt.getBigIntArray()) &&
            strcmp(firstInt.getBigIntArray(), secondInt.getBigIntArray()) < 0){
		return true;
	}
    
	else{
		return false;
	}
    
	//Not too bad, think about it...
}

//operator >
bool operator >(const bigInt &firstInt, const bigInt &secondInt)
{
	if (strlen(firstInt.getBigIntArray()) < strlen(secondInt.getBigIntArray()))
	{
		return false;
	}
    
	else if (strlen(firstInt.getBigIntArray()) > strlen(secondInt.getBigIntArray()))
	{
		return true;
	}
    
	else if(strlen(firstInt.getBigIntArray()) == strlen(secondInt.getBigIntArray()) &&
            strcmp(firstInt.getBigIntArray(), secondInt.getBigIntArray()) > 0){
		return true;
	}
    
	else{
		return false;
	}
	//you've done equals and <, so this should be easy
}

//operator <=
bool operator <=(const bigInt &firstInt, const bigInt &secondInt)
{
	if(operator > (firstInt, secondInt) == true){
		return false;
	}
	else{
		return true;
	}
	//if it's not greater than..
}

//operator >=
bool operator >=(const bigInt &firstInt, const bigInt &secondInt)
{
	if(operator < (firstInt, secondInt) == true){
		return false;
	}
	else{
		return true;
	}
	//if it's not less than...
}

bigInt operator +(const bigInt &firstInt, const bigInt &secondInt)
{
	//there are many strategies to this I'll outline the one that we
	//did in class here you can use it
	//or feel free to devise your own way...
	
	//make two temporary char* to hold the bigIntArray of firstInt and secondInt
    //you can use getBigIntArray (temp1 and temp2)
    
    //find out which one of these bigInts is bigger and make a third char*
    //array of that size to hold the result of our add (result)
    
    //start at the final index of temp1 and temp2 and start adding them
    //index by index, placing them in result and decrementing their indexes (I
    //had two index variables)
    //Remember to add a carry if the last sum was greater or equal to 10
    
    //When the shorter numbers index is negative, then you only add
    //the bigger ones index to the carry and place this in the result
    
    //when you're done (ie index1 and index2 are negative) - if you have a
    //carry you resize the result array and put a 1 in the front
    
    //finally you create a bigInt with that array and return it
    //before you do remember to deallocate any dynamic memory before the
    //ptr disappears
    
    bigInt longInt;
    bigInt shortInt;
    if( firstInt >= secondInt ){
    	longInt = firstInt;
    	shortInt = secondInt;
    }
    
    else if ( firstInt < secondInt ){
    	longInt = secondInt;
    	shortInt = firstInt;
    }
    
    int longLength = strlen(longInt.getBigIntArray());
    int shortLength = strlen(shortInt.getBigIntArray());
    int resultLength = longLength;
    
    int longIndex = longLength-1;
    int shortIndex = shortLength-1;
    int resultIndex = resultLength-1;
    int carry = 0;
    
    char* longTempArray = longInt.getBigIntArray();
    char* shortTempArray = shortInt.getBigIntArray();
    char longTempChar;
    char shortTempChar;
    char resultTempChar;
    char* resultArray = new char[resultLength];
    resultArray[resultLength] = NULL;
    
    while ((resultIndex >= 0) || (longIndex >= 0) || (shortIndex >= 0) ){
    	if ((longIndex >= 0) && (shortIndex >= 0))
    	{
    		longTempChar = longTempArray[longIndex];
    		shortTempChar = shortTempArray[shortIndex];
            longTempChar = longTempChar - '0';
            shortTempChar = shortTempChar - '0';
            resultTempChar = longTempChar + shortTempChar + carry;
            carry = 0;
            
            if (resultTempChar >= 10){
                carry = 1;
                resultTempChar = resultTempChar % 10;
            }
            
            resultTempChar = resultTempChar + '0';
            resultArray[resultIndex] = resultTempChar;
        }
        
        else if ( (longIndex >= 0) && (shortIndex < 0) ){
            longTempChar = longTempArray[longIndex];
            longTempChar = longTempChar - '0';
            resultTempChar = longTempChar + carry;
            carry = 0;
            
            if (resultTempChar >= 10){
                carry = 1;
                resultTempChar = resultTempChar % 10;
            }
            
            resultTempChar = resultTempChar + '0';
            resultArray[resultIndex] = resultTempChar;
        }
        
        if ((longIndex <= 0) && (shortIndex <= 0) && (carry > 0)){
        	resultTempChar = carry;
            carry = '1';
            
            if (resultTempChar >= 10){
                carry = 1;
                resultTempChar = resultTempChar % 10;
            }
            
            char* tempResultArray;
            tempResultArray = resultArray;
            delete []resultArray;
            
            char* resultArray = new char[resultLength+1];
            
            for (int i = resultLength; i >= 0; i--){
                resultTempChar = tempResultArray[i];
                resultArray[i + 1] = resultTempChar;
            }
            
            resultArray[0] = '1';
        }
        
        resultIndex--;
        longIndex--;
        shortIndex--;
    }
    
    return resultArray;
}


void bigInt::operator += (const bigInt& intToAdd)
{
    bigInt temporary;
    temporary = this->bigIntArray;
    temporary = temporary + intToAdd;
    this->bigIntArray = temporary.getBigIntArray();
    
	//now that you've done add,  you can use a temporary bigInt
	//and the "this" pointer to add your current object to
	//intToAdd. then you can use getbigIntArray on the temp
	//to set "this" big int array, possibly cleaning up
	//memory along the way...
    
}


bigInt operator - (const bigInt &firstInt, const bigInt &secondInt)
{
	//Think about this....
    
    bigInt longInt;
    bigInt shortInt;
    
    if(firstInt >= secondInt){
        longInt = firstInt;
        shortInt = secondInt;
    }
    
    else if (firstInt < secondInt){
        longInt = secondInt;
        shortInt = firstInt;
    }
    
    int longLength = strlen(longInt.getBigIntArray());
    int shortLength = strlen(shortInt.getBigIntArray());
    int resultLength = longLength;
    
    int longIndex = longLength-1;
    int shortIndex = shortLength-1;
    int resultIndex = resultLength-1;
    int carry = 0;
    
    char* longTempArray = longInt.getBigIntArray();
    char* shortTempArray = shortInt.getBigIntArray();
    
    char longTempChar;
    char shortTempChar;
    char resultTempChar;
    
    char* resultArray = new char[resultLength];
    resultArray[resultLength] = NULL;
    
    while ((resultIndex >= 0) || (longIndex >= 0) || (shortIndex >= 0)){
        if ((longIndex >= 0) && (shortIndex >= 0)){
            longTempChar = longTempArray[longIndex];
            shortTempChar = shortTempArray[shortIndex];
            longTempChar = longTempChar - '0';
            shortTempChar = shortTempChar - '0';
            resultTempChar = longTempChar - shortTempChar - carry;
            carry = 0;
            
            if (resultTempChar < 0){
                carry = 1;
                resultTempChar = resultTempChar + 10;
                resultTempChar = resultTempChar % 10;
            }
            
            resultTempChar = resultTempChar + '0';
            resultArray[resultIndex] = resultTempChar;
        }
        
        else if ( (longIndex >= 0) && (shortIndex < 0)){
            longTempChar = longTempArray[longIndex];
            longTempChar = longTempChar - '0';
            resultTempChar = longTempChar - carry;
            carry = 0;
            
            if (resultTempChar < 0){
                carry = 1;
                resultTempChar = resultTempChar + 10;
                resultTempChar = resultTempChar % 10;
            }
            
            resultTempChar = resultTempChar + '0';
            resultArray[resultIndex] = resultTempChar;
        }
        
        while ((longIndex <= 0) && (shortIndex <= 0) && (resultArray[0] == '0')  && (strlen(resultArray) >= 2)){
            char* tempResultArray = new char[resultLength];
            tempResultArray = resultArray;
            
            delete[] resultArray;
            char* resultArray = new char[resultLength - 1];
            
            for (int i = 0; i <= resultLength -1; i++){
                resultTempChar = tempResultArray[i+1];
                resultArray[i] = resultTempChar;
            }
        }
        
        resultIndex--;
        longIndex--;
        shortIndex--;
    }
    return resultArray;
}


void bigInt::operator -= (const bigInt& intToSubtract)
{
	bigInt temporary;
    temporary = this->bigIntArray;
    temporary = temporary - intToSubtract;
    this->bigIntArray = temporary.getBigIntArray();
    
    //If you've done minus, this should be easy
	//you can even use the this ptr.
}


// void bigInt::operator * (const bigInt& intToSubtract)
// {
//     bigInt total;

// }


// void bigInt::operator / (const bigInt& intToSubtract)
// {
//     bigInt total;

// }

//ostream is implemented for you
ostream& operator <<(ostream& outs, const bigInt& source)
{
	outs<<source.bigIntArray;
	return outs;
}

//istream is implemented for you in a cheating manner
std::istream& operator >>(std::istream& ins, bigInt& target)
{
	delete [] target.bigIntArray;
	string hello;
	ins>>hello;
	bigInt temp(hello.c_str());
	target.bigIntArray=temp.getBigIntArray();
    return ins;
}

