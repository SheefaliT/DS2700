/*pseudo-code for mug.h
File: Mug.h
Class Provided: A class that simulates a no longer magic mug, Suddenly we have
a Hard capacity. Still only non-alcoholic drinks though. 
By the end of this lab we will also be able to 
print out the mug contents (using cout) and add contents of one mug to another mug, or instantiate another mug to the same amount by initializing it with a given amount. 
Finally we will be able to cin into a mug and 

Constructors for the mug class:
	(mug()
		Postcondition: amountFilled=0.0)--> this is now covered by our default argument in the mug(double initialFill) constructor
		
	mug(double initialFill)
		Precondition: initialFill>=0.0
		Postcondition: amountFilled equals initialFill
	
Modification Member Functions
	 void fillMug(double amount)
	 	Precondition: amount>=0.0
	 	Postcondition: amountFilled is now increased by amount
	 	
	 void empty()
	 	Postcondition: the cup is emptied
	 	
Constant Member Functions
	double getFillAmount() const
	Postcondition: The value returned is the amount the mug is currently filled to
	
	bool isEmpty() const
	Postcondition: returns true if the mug is empty, and false if it's not.
	
	 NONMEMBER FUNCTIONS
  istream& operator >>(istream& ins, mug& target)
  Postcondition: The amountFilled of target has been written from ins.The return value is the istream ins.

  ostream& operator <<(ostream& outs, const mug& source)
  Postcondition: The amountFilled of source has been written to outs
  The return value is the outstream outs.
*/

#ifndef MUG_H_   //macroguard that stops the header from being included twice.
#define MUG_H_  //Including the header twice stops the compilation, Note no Semilcolon

#include <iostream>

class mug //a no-longer magic mug that holds non-infinite amount of non-alcoholic drinks{
	public:
		//Member Constants
		static const double CAPACITY=74.0; //we now have a capacity of 74.0
		//Constructors
		mug(); // default constructor    //COMMENT THIS GUY
		mug(double initialFill); //ADD A DEFAULT ARGUMENT!!
				//Public Members
		void fillMug(double amount); //Adds to the amountFilled
									//must now check if it's over capacity
		void empty(); //empties our mug
		
		//Constant Member Functions
		double getFillAmount() const; //gets the current amount the cup is filled to
		bool isEmpty() const;
		
		
		//Overloaded Operators
    	void operator = (const mug& mugToCopy);
    	
		
		
		//Friend function, we put both cin and cout overloads here to mimic
		//the homework specs (though the book does cout as a nonmember)
		
	//for cin
	friend std::istream& operator >>(std::istream& ins, mug& target);
    
    //for cout
    friend std::ostream& operator <<(std::ostream& outs, const mug& source);
		private:		double amountFilled; //private member variable}; //NOTE THIS SEMICOLON AT THE END OF THIS CLASS DEFINITION!

//NONMEMBERS
bool operator ==(const mug &firstMug, const mug &secondMug);

#endif   