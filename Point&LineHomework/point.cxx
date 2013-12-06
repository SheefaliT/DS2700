//Name: Sheefali Tewari
//Collaborated with Weiquiang and Emily.
#include "point.h"
#include "math.h"
#include <iostream>
#include <cstdlib>
using namespace std;


point::point(point& p)               
{
    x = p.x;
    y = p.y;
}

point::point(double x_in, double y_in)
{
    x = x_in;
    y = y_in;
}


const double point::get_x()
{
    return x;
}

const double point::get_y()
{
    return y;
}


void point::set_x(double x_in)
{
    x = x_in;
}

void point::set_y(double y_in)
{
    y = y_in;
}


void point::translate(double x_in, double y_in)
{
    x = x + x_in;
    y = y + y_in;
}


void point::scale(double m)
{
    x = m * x;
    y = m * y;
}


void point::reflect_x()              
{
    y = -y;
    
}

void point::reflect_y()               
{
    x = -x;
}


void point::rotate(double r)
{
    double oldX = x;                       
    x = ((x) * cos(r) - (y) * sin(r));
    y = ((oldX) * sin(r) + (y) * cos(r));  

istream& operator >>(istream& ins, point& target)
{
    ins >> target.x >> target.y;
    return ins;
}

ostream& operator <<(ostream& outs, const point& source)
{
    outs << "(" << source.x << ", ";
    outs << source.y << ")";
    return outs;
}

bool operator == (const point &firstPoint, const point &secondPoint)
{
    return (firstPoint.x == secondPoint.x &&
            firstPoint.y == secondPoint.y);
}




