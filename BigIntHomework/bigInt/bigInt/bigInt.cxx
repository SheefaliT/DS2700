//
//  bigInt.cxx
//  bigInt
//
//  Created by Sheefali Tewari on 7/23/13.
//  Copyright (c) 2013 Sheefali Tewari. All rights reserved.
//  Collaborated with Paul
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
	//a 2 element array with an initial value of zero and a NULL
	//character  ie: 0th element is 0 and 1st element is NULL
    bigIntArray = new char[2];
    bigIntArray[0] = '0';
    bigIntArray[1] = NULL;
}

//"c_str" constructor
bigInt::bigInt(const char initialValue [])
{
	//make your bigInt array equal to this c_str
	//being passed in  (i.e. use strlen to allocate
	//memory (remember to add +1 to it though for the null character...
	// and strcpy to copy the stuff over (strcpy adds the null automatically)
    int length;
    length = strlen(initialValue);
    bigIntArray = new char[length + 1];
    strcpy(bigIntArray,initialValue);
    bigIntArray[length + 1] = NULL;
}

//"integer" constructor
bigInt::bigInt(int initialValue)
{
	//use a loop to count the numberOfDigits in initial value
	//Allocate that memory and copy it over (that good ol divide
	//by 10 and modulo 10 thing
    int count;
    int countValue;
    countValue = initialValue;
    count = 0;
    
    while (countValue > 10)
    {
        countValue = countValue / 10;
        count++;
    }
    bigIntArray = new char[count + 1];
    sprintf(bigIntArray, "%i", initialValue);
}

//"double" constructor
bigInt::bigInt (double initialValue)
{
	//very similar to the integer constructor strategy above
	//in fact you get this into an int and you can use the same
	//code...
    
    int tempInt = (int) initialValue;
    bigInt temp_2 (tempInt); // bigInt temp_2 = bigInt(initialValue);
    bigIntArray = temp_2.getBigIntArray();
}

//Copy Constructor
bigInt::bigInt (const bigInt& toCopyFrom)
{
	//use the getBigIntArray on toCopyFrom to set bigIntArray of your object
	//remember to delete bigIntArray of your object BEFORE setting it
	//or else you'll get a memory leak
    // IGNORE THE ADVICE TO DELETE WHATEVER
    bigIntArray = toCopyFrom.getBigIntArray();
}

bigInt::~bigInt()
{
	//delete your bigIntArray
    //cout << "Destructor function called" << endl;
    delete [] bigIntArray;
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
	//use getBigIntArray on toEqual to set your int array to
	//the intArray of toEqual
    delete [] bigIntArray;
    bigIntArray = toEqual.getBigIntArray();
    
}

//operator "=="
bool operator ==(const bigInt &firstInt, const bigInt &secondInt)
{
	//check to see if the bigIntArray's are equal
	//you can use strcmp for this
    if(strcmp(firstInt.getBigIntArray(), secondInt.getBigIntArray())==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//operator !=
bool operator !=(const bigInt &firstInt, const bigInt &secondInt)
{
	//easy once you've done ==
    if(strcmp(firstInt.getBigIntArray(), secondInt.getBigIntArray())==0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//operator <
bool operator <(const bigInt &firstInt, const bigInt &secondInt)
{
	//Not too bad, think about it...
    int firstLen = strlen(firstInt.getBigIntArray());
    int secondLen = strlen(secondInt.getBigIntArray());
    char* firstTemp = firstInt.getBigIntArray();
    char* secondTemp = secondInt.getBigIntArray();
    
    if ( firstLen < secondLen )
    {
        return true;
    }
    if ( firstLen > secondLen)
    {
        return false;
    }
    if ( firstLen == secondLen)
    {
        for (int i = 0; i < firstLen; i++)
        {
            if (firstTemp[i] < secondTemp[i])
            {
                return true;
            }
            else if ( firstTemp[i] > secondTemp[i])
            {
                return false;
            }
        }
    }
    return false;
}

//operator >
bool operator >(const bigInt &firstInt, const bigInt &secondInt)
{
	//you've done equals and <, so this should be easy
    int firstLen = strlen(firstInt.getBigIntArray());
    int secondLen = strlen(secondInt.getBigIntArray());
    char* firstTemp = firstInt.getBigIntArray();
    char* secondTemp = secondInt.getBigIntArray();
    
    if ( firstLen > secondLen )
    {
        return true;
    }
    if ( firstLen < secondLen)
    {
        return false;
    }
    if ( firstLen == secondLen)
    {
        for (int i = 0; i < firstLen; i++)
        {
            if (firstTemp[i] > secondTemp[i])
            {
                return true;
            }
            else if ( firstTemp[i] < secondTemp[i])
            {
                return false;
            }
        }
    }
    return false;
}

//operator <=
bool operator <=(const bigInt &firstInt, const bigInt &secondInt)
{
	//if it's not greater than..
    //    if ((firstInt == secondInt) || (firstInt < secondInt) )
    //        {
    //            return true;
    //        }
    //    return false;
    return ( !(firstInt > secondInt) );
}

//operator >=
bool operator >=(const bigInt &firstInt, const bigInt &secondInt)
{
	//if it's not less than...
    //    if ((firstInt == secondInt) || (firstInt > secondInt) )
    //        {
    //            return true;
    //        }
    //    return false;
    return (!(firstInt < secondInt));
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
    
    //When the smaller numbers index is negative, then you only add
    //the bigger ones index to the carry and place this in the result
    
    //when you're done (ie index1 and index2 are negative) - if you have a
    //carry you resize the result array and put a 1 in the front
    
    //finally you create a bigInt with that array and return it
    //before you do remember to deallocate any dynamic memory before the
    //ptr disappears
    
    //used variables
    //cout << "+++++Addition operator called+++++" << endl;
    bigInt largeInt;
    bigInt smallInt;
    //cout << "Created largeInt and smallInt" << endl;
    //Figure out which int is bigger.
    if( firstInt >= secondInt )
    {
        largeInt = firstInt;
        smallInt = secondInt;
    }
    else if ( firstInt < secondInt )
    {
        largeInt = secondInt;
        smallInt = firstInt;
    }
    //cout << "Found largeInt and smallInt" << endl;
    //cout << "LargeInt is: " << largeInt << " " << "smallInt is: " << smallInt << endl;
    //makes copies to hold the two big int arrays
    int largeLen = strlen(largeInt.getBigIntArray()); // length of the first BigInt
    int smallLen = strlen(smallInt.getBigIntArray()); // length of the second BigInt
    int resultLen = largeLen;      // length of the resulting int
    //cout << "largeLen = " << largeLen << " smallLen = " << smallLen << " resultLen = " << resultLen << endl;
    int largeIndex = largeLen-1; // set the large index
    int smallIndex = smallLen-1; // set the small index
    int resultIndex = resultLen-1; // set the result index
    int carry = 0; // set the carry additive to 0.
    //cout << "largeIndex, smallIndex, resultIndex, carry iniialized" << endl;
    // get the two indexes
    char* largeTempArray = largeInt.getBigIntArray();
    char* smallTempArray = smallInt.getBigIntArray();
    //cout << "largeTempArray = " << largeTempArray << " smallTempArray = " << smallTempArray << endl;
    //cout << "largeTempArray and smallTempArray initialized" << endl;
    char largeTempChar;
    char smallTempChar;
    char resultTempChar;
    //cout << "largeTempChar, smallTempChar and resultTempChar initialized" << endl;
    //initialize the length of the new array
    char* resultArray = new char[resultLen];
    resultArray[resultLen] = NULL;
    //cout << "resultArray initialized" << endl;
    while ( (resultIndex >= 0) || (largeIndex >= 0) || (smallIndex >= 0) )
    {
        //cout << "START OF A NEW LOOP!" << endl;
        //cout << "resultIndex = " << resultIndex << " largeIndex = " << largeIndex << " smallIndex = " << smallIndex << " carry = " << carry << " " << endl;
        if ( (largeIndex >= 0) && (smallIndex >= 0) )
        {//if we have characters left
            // get the characters and put them into temp vars
            largeTempChar = largeTempArray[largeIndex];
            smallTempChar = smallTempArray[smallIndex];
            //cout << "largeTempChar is: " << largeTempChar << " smallTempChar is: " << smallTempChar << endl;
            //convert the temp vars from char to int
            largeTempChar = largeTempChar - '0';
            smallTempChar = smallTempChar - '0';
            // add the two integers
            resultTempChar = largeTempChar + smallTempChar + carry;
            // set carry to 0 now that we used it
            carry = 0;
            // check to see if the result is equal or larger than 10
            if (resultTempChar >= 10)
            {
                carry = 1;
                resultTempChar = resultTempChar % 10;
            }
            // convert result from an int back to a char
            resultTempChar = resultTempChar + '0';
            // put the result temp char back into the array in the right place
            //cout << "resultTempChar is: " << resultTempChar << endl;
            resultArray[resultIndex] = resultTempChar;
            //cout << "resultArray[resultIndex] value is: " << resultArray[resultIndex] << endl;
        }
        else if ( (largeIndex >= 0) && (smallIndex < 0) )
        { // if we have characters left on only
            // get the characters and put them into temp vars
            largeTempChar = largeTempArray[largeIndex];
            //cout << "largeTempChar is: " << largeTempChar << endl;
            //convert the temp vars from char to int
            largeTempChar = largeTempChar - '0';
            // add the two integers
            resultTempChar = largeTempChar + carry;
            // set carry to 0 now that we used it
            carry = 0;
            // check to see if the result is equal or larger than 10
            if (resultTempChar >= 10)
            {
                carry = 1;
                resultTempChar = resultTempChar % 10;
            }
            // convert result from an int back to a char
            resultTempChar = resultTempChar + '0';
            // put the result temp char back into the array in the right place
            //cout << "resultTempChar is: " << resultTempChar << endl;
            resultArray[resultIndex] = resultTempChar;
            //cout << "resultArray[resultIndex] value is: " << resultArray[resultIndex] << endl;
        }
        if ( (largeIndex <= 0) && (smallIndex <= 0) && (carry > 0) )   // both largeIndex and smallIndex are less than 0
        {
            //cout << "we are out of large and small indexes.  carry is: " <<carry << endl;
            //cout << resultArray << endl;
            resultTempChar = carry;
            // set carry to 0 now that we used it
            carry = '1';
            // check to see if the result is equal or larger than 10
            if (resultTempChar >= 10)
            {
                carry = 1;
                resultTempChar = resultTempChar % 10;
            }
            // convert result from an int back to a char
            // resultTempChar = resultTempChar + '0';
            // put the result temp char back into the array in the right place
            //now our problem is that our array is not big enough, so we have to copy it, and then stick all the old values in a new array.
            char* tempResultArray;
            tempResultArray = resultArray;
            delete []resultArray;
            char* resultArray = new char[resultLen+1];
            for (int i = resultLen; i >= 0; i--)
            {
                resultTempChar = tempResultArray[i];
                resultArray[i + 1] = resultTempChar;
                //cout << "result index: " << i+1 <<  " resultArray " << resultArray[i + 1] << " index = " << i <<  " tempResultArray " <<tempResultArray[i] << endl;
            }
            resultArray[0] = '1';
            
        }
        //            cout << "resultArray[resultIndex] value is: " << resultArray[resultIndex] << endl;
        resultIndex--;
        largeIndex--;
        smallIndex--;
    }
    return resultArray;
    //cout << "Addition Function Ended" << endl;
}



void bigInt::operator += (const bigInt& intToAdd)
{
	//now that you've done add,  you can use a temporary bigInt
	//and the "this" pointer to add your current object to
	//intToAdd. then you can use getbigIntArray on the temp
	//to set "this" big int array, possibly cleaning up
	//memory along the way...
    
    bigInt temp;
    temp = this->bigIntArray;
    temp = temp + intToAdd;
    this->bigIntArray = temp.getBigIntArray();
}

bigInt operator -(const bigInt &firstInt, const bigInt &secondInt)
{
    //NOTE... WE HAVE TO FEED THE LARGER INEGER AS firstInt, AND SUBTRACT secondInt FROM firstInt
    //cout << "-----Subtraction operator called-----" << endl;
    bigInt largeInt;
    bigInt smallInt;
    //cout << "Created largeInt and smallInt" << endl;
    //Figure out which int is bigger.
    if( firstInt >= secondInt )
    {
        largeInt = firstInt;
        smallInt = secondInt;
    }
    else if ( firstInt < secondInt )
    {
        largeInt = secondInt;
        smallInt = firstInt;
    }
    //cout << "Found largeInt and smallInt" << endl;
    //cout << "LargeInt is: " << largeInt << " " << "smallInt is: " << smallInt << endl;
    //makes copies to hold the two big int arrays
    int largeLen = strlen(largeInt.getBigIntArray()); // length of the first BigInt
    int smallLen = strlen(smallInt.getBigIntArray()); // length of the second BigInt
    int resultLen = largeLen;      // length of the resulting int
    //cout << "largeLen = " << largeLen << " smallLen = " << smallLen << " resultLen = " << resultLen << endl;
    int largeIndex = largeLen-1; // set the large index
    int smallIndex = smallLen-1; // set the small index
    int resultIndex = resultLen-1; // set the result index
    int carry = 0; // set the carry additive to 0.
    //cout << "largeIndex, smallIndex, resultIndex, carry iniialized" << endl;
    // get the two indexes
    char* largeTempArray = largeInt.getBigIntArray();
    char* smallTempArray = smallInt.getBigIntArray();
    //cout << "largeTempArray = " << largeTempArray << " smallTempArray = " << smallTempArray << endl;
    //cout << "largeTempArray and smallTempArray initialized" << endl;
    char largeTempChar;
    char smallTempChar;
    char resultTempChar;
    //cout << "largeTempChar, smallTempChar and resultTempChar initialized" << endl;
    //initialize the length of the new array
    char* resultArray = new char[resultLen];
    //cout << "resultArray initially is: " << resultArray << endl;
    resultArray[resultLen] = NULL;
    //cout << "resultArray initialized" << endl;
    while ( (resultIndex >= 0) || (largeIndex >= 0) || (smallIndex >= 0) )
    {
        //cout << "START OF A NEW LOOP!" << endl;
        //cout << "resultIndex = " << resultIndex << " largeIndex = " << largeIndex << " smallIndex = " << smallIndex << " carry = " << carry << " " << endl;
        if ( (largeIndex >= 0) && (smallIndex >= 0) )
        {//if we have characters left
            // get the characters and put them into temp vars
            largeTempChar = largeTempArray[largeIndex];
            smallTempChar = smallTempArray[smallIndex];
            //cout << "largeTempChar is: " << largeTempChar << " smallTempChar is: " << smallTempChar << endl;
            //convert the temp vars from char to int
            largeTempChar = largeTempChar - '0';
            smallTempChar = smallTempChar - '0';
            // add the two integers
            resultTempChar = largeTempChar - smallTempChar - carry;
            // set carry to 0 now that we used it
            carry = 0;
            // check to see if the result is equal or larger than 10
            if (resultTempChar < 0)
            {
                carry = 1;
                resultTempChar = resultTempChar + 10;
                resultTempChar = resultTempChar % 10;
            }
            // convert result from an int back to a char
            resultTempChar = resultTempChar + '0';
            // put the result temp char back into the array in the right place
            //cout << "resultTempChar is: " << resultTempChar << endl;
            resultArray[resultIndex] = resultTempChar;
            //cout << "resultArray[resultIndex] value is: " << resultArray[resultIndex] << endl;
        }
        else if ( (largeIndex >= 0) && (smallIndex < 0) )
        { // if we have characters left on only
            // get the characters and put them into temp vars
            largeTempChar = largeTempArray[largeIndex];
            //cout << "largeTempChar is: " << largeTempChar << endl;
            //convert the temp vars from char to int
            largeTempChar = largeTempChar - '0';
            // add the two integers
            resultTempChar = largeTempChar - carry;
            // set carry to 0 now that we used it
            carry = 0;
            // check to see if the result is equal or larger than 10
            if (resultTempChar < 0)
            {
                carry = 1;
                resultTempChar = resultTempChar + 10;
                resultTempChar = resultTempChar % 10;
            }
            // convert result from an int back to a char
            resultTempChar = resultTempChar + '0';
            // put the result temp char back into the array in the right place
            //cout << "resultTempChar is: " << resultTempChar << endl;
            resultArray[resultIndex] = resultTempChar;
            //cout << "resultArray[resultIndex] value is: " <<  resultArray[resultIndex] << endl;
        }
        while ( (largeIndex <= 0) && (smallIndex <= 0) && (resultArray[0] == '0')  && (strlen(resultArray) >= 2) )   // both largeIndex and smallIndex are less than 0
        {
            // we now have a leading 0... i.e. 091\n
            //cout << "we need to shorten the array." << endl;
            char* tempResultArray = new char[resultLen];
            tempResultArray = resultArray; // tells us that the temp array points to the same place result array lives.  we dont want that.
            //cout << tempResultArray[0] << tempResultArray[1] << tempResultArray[2] << tempResultArray[3] << endl;
            //cout << "tempResultArray is: " << tempResultArray << endl;
            delete[] resultArray;
            char* newArray = new char[resultLen - 1];
            //cout << "newArray = :" << newArray << endl;
            //cout << "resultLen = :" << resultLen << endl;
            for (int i = 0; i <= resultLen -1; i++)
            {
                resultTempChar = tempResultArray[i+1];
                //cout << "i = " << i << " resultTempChar is :" << resultTempChar << endl;
                resultArray[i] = resultTempChar;
                //cout << "result index: " << i-1 <<  " resultArray " << resultArray[i-1] << " index = " << i <<  " tempResultArray " <<tempResultArray[i] << endl;
                //cout << resultArray << endl;
            }
            //resultArray[resultLen-1] = NULL;
            
        }
        // cout << "resultArray[resultIndex] value is: " << resultArray[resultIndex] << endl;
        resultIndex--;
        largeIndex--;
        smallIndex--;
    }
    return resultArray;
    //cout << "Addition Function Ended" << endl;
}

bigInt operator *(const bigInt &firstInt, const bigInt &secondInt)
{
    //initialize the counter and incriment bigInt variables
	bigInt counter(0);
    //cout << "counter = " << counter << endl;
	bigInt incriment(1);
    bigInt largeTempArray = firstInt.getBigIntArray();
    bigInt smallTempArray = secondInt.getBigIntArray();
    bigInt result;
    while ( counter < smallTempArray )
    {
        result = result + largeTempArray;
        //cout << "largeTempArray is: " << largeTempArray << endl;
        counter = counter + incriment;
        //cout << "counter = " << counter << endl;
        
    }
    return result;
}

bigInt operator /(const bigInt &firstInt, const bigInt &secondInt)
{
    //bigInt counter(0);
    bigInt incriment(1);
    bigInt numerator = firstInt.getBigIntArray();
    bigInt denominator = secondInt.getBigIntArray();
    bigInt result;
    while (numerator >= denominator)
    {
        numerator = numerator - denominator;
        result = result + incriment;
    }
    return result;
}

void bigInt::operator -= (const bigInt& intToSubtract)
{
	//If you've done minus, this should be easy
	//you can even use the this ptr.
    bigInt temp;
    temp = this->bigIntArray;
    temp = temp - intToSubtract;
    this->bigIntArray = temp.getBigIntArray();
}

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

