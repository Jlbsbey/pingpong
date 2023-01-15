#include "figure.hpp"
#include "var.cpp"
#include <cstdlib>
#include <iostream>
#include "AllegroBase.hpp"
#include "tmpreset.hpp"
class Circle : public Figure
{
protected:
    double r_;
public:
    double geta(){};
    void invertdx(){};
    void invertdy(){};
    double getx(){};
    double gety(){};
    double getdx(){};
    double getdy(){};
    Circle( double r ){};
    virtual void Draw(){};
    virtual void Move(){};
    void Reset(){};
};