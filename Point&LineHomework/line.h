#ifndef LINE_H_
#define LINE_H_

#include <iostream>
#include "point.h"

class line
{
public:
    
    line();                    
    line(point p1_in);        
    line(point p1_in, point p2_in); 
    line(line& l);   

    void translate(double x_in, double y_in);
    void reflect_x();           
    void reflect_y();        

    const double findYInt(); 
    const double slope();
    
   
    const friend bool operator== (line &lineOne, line &lineTwo); 
    line operator= (const line &lineOne);
    
    friend std::ostream& operator <<(std::ostream& outs, line& source); 
    friend std::istream& operator >>(std::istream& ins, line& target); 
    
private:
    
    point p1, p2;
};

#endif