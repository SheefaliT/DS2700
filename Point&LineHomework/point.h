//Name: Sheefali Tewari
//Collaborated with Weiquiang and Emily.
#ifndef POINT_H_            
#define POINT_H_

#include <iostream>

class point            
{
public:
    point(double x_in = 0, double y_in = 0);   
    point(point& p);  

    const double get_x();                             
    const double get_y();                           
    
    void set_x(double x_in);                   
    void set_y(double y_in);              
    void scale(double m);      
    void reflect_x();
    void reflect_y();                          
    void rotate(double r);
    void translate(double x_in, double y_in);                 
    
    friend std::ostream& operator <<(std::ostream& outs, const point& source);
    friend std::istream& operator >>(std::istream& ins, point& target);
    friend bool operator == (const point &firstPoint, const point &secondPoint);
    
private:
    double x, y;    
};

#endif