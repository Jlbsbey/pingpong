#include "var.cpp"
#include "figure.hpp"
#include "AllegroBase.hpp"
#include <cstdlib>
class Square : public Figure
{
protected:
    double a_;
    double x_;
    double y_;
public:
    double getx(){}
    double gety(){}
    double geta(){}
    Square( double a ){};
    virtual void Draw(){};
    virtual void Move(){};
    virtual void Reset(){};
};