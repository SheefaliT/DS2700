//Name: Sheefali Tewari
//Collaborated with Weiquiang and Emily.
#include "line.h"
#include "math.h"
#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;

line::line()                          
{
    p1 = 0,0;
    p2 = 1,0;
}

line::line(point p1_in)       
{
    p1 = p1_in;
    p2 = 0,0;
}

line::line(point p1_in, point p2_in)    
{
    p1 = p1_in;
    p2 = p2_in;
}

line::line(line& l)                    
{
    p1 = l.p1;
    p2 = l.p2;
}


const double line::slope()                  
{
    if (p1.get_x() == p2.get_x())
    {
        double m = INFINITY;
        return m;
    } else
    {
        double m = (p2.get_y() - p1.get_y()) / (p2.get_x() - p1.get_x());
        return m;
    }
}

void line::translate(double x_in, double y_in)     
{
    p1.translate(x_in, y_in);
    p2.translate(x_in, y_in);
}

void line::reflect_x()             
{
    p1.reflect_x();
    p2.reflect_x();
    
}

void line::reflect_y()               
{
    p1.reflect_y();
    p2.reflect_y();
}

const double line::findYInt()    
{
    double b = p2.get_y() - line::slope() * p2.get_x();
    return b;
}


istream& operator >>(istream& ins, line& target) 
{
    ins >> target.p1 >> target.p2;
    return ins;
}

ostream& operator <<(ostream& outs, line& source)  
{
    if (source.p1.get_x() == source.p2.get_x())
    {
        outs << "x = " << source.p1.get_x() << endl;
    } else if (source.p1.get_y() == source.p2.get_y())
    {
        outs << "y = " << source.p1.get_y() << endl;
    } else
    {
        outs << "y = " << source.slope() << "x + " << source.findYInt() << endl;
    }

    return outs;
}

const bool operator ==(line &lineOne, line &lineTwo)    
{
    if (lineOne.slope() == INFINITY){
        return  (lineOne.p1.get_x() == lineOne.p2.get_x() &&
                 lineTwo.p1.get_x() == lineTwo.p2.get_x() &&
                 lineOne.p1.get_x() == lineTwo.p1.get_x());

    }else {
        return (lineOne.slope() == lineTwo.slope() &&
                lineOne.findYInt() == lineTwo.findYInt());
    }
}

line line::operator= (const line& lineOne)             
{
    p1 = lineOne.p1;
    p2 = lineOne.p2;
    
    return *this;
}
