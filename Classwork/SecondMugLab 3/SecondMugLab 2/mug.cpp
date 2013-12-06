#include<cassert>//provides assert
#include "mug.h"
#include <iostream> //we are adding ostream and istream
#include <cstdlib>
using namespace std;
//these comments should help you, as the programmer of this out
//i.e. everyone else who gets handed this code
//should rely on the comments in the .h file

mug::mug() //default constructor for mug class   //COMMENT THIS GUY//
{
	amountFilled=0;
}

mug::mug(double initialFill) //Constructor with an initial fill passed in
							 //
{							
	assert(initialFill>=0.0);
	amountFilled=initialFill;
}

void mug::fillMug(double fillAmount) //adds the fill amount to the mug 
									//**IMPLEMENT THIS**, make sure fillAmount
 									//is greater or equal to zero (i.e. assert 
 									//something....)
{ 
	assert(fillAmount>=0.0);
	amountFilled+=fillAmount;
}

void mug::empty() //empties the mug **IMPLEMENT THIS**
{
	amountFilled=0;
}

double mug::getFillAmount() const //looks at the mug and returns the
{                                 //amount it's filled to
	return amountFilled;
}

bool mug::isEmpty() const   //checks if the mug is empty and return s
{
	return (amountFilled==0.0);
}

void mug::operator = (const mug& mugToCopy) //IMPLEMENT THIS!
{
	//y'know prolly want to set the one and only private variable to 
	// of this instance the same value as this mugToCopy....
	
}



bool operator ==(const mug &firstMug, const mug &secondMug) //IMPLEMENT THIS{
	//In this case, since it's not a member both mugs get passed in
	//So how would you check if they were equal....	
}

istream& operator >>(istream& ins, mug& target) //IMPLEMENT THIS!!
{
	
	//UPDATE THIS FOR MUG LAB 2-- (hint it'd be ins>>target.<something>)
	//Remember we can use the private variable here because it's a friend
	ins >> ;
	return ins;
}


ostream& operator <<(ostream& outs, const mug& source) //IMPLEMENT THIS!!
{  
	
	//UPDATE THIS FOR MUG LAB 2 (maybe outs<<source.<something>.....)
	//Remember we can use the private variable here because it's a friend
	outs << ;
	return outs;
}

