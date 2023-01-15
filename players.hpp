#include "figure.hpp"
#include "var.cpp"
#include "AllegroBase.hpp"
class Player1 : public Figure
{
protected:
    double a_=0.15*SCREEN_H;
    double x_;
    double y_;
public:
    double geta(){};
    double getx(){};
    double gety(){};
    Player1( double side ){};
    double half = a_/2;
    void MoveBy(double dy1 ){};
    virtual void Draw(){};
    void Move(){};
    virtual void Reset(){}
};
class Player2 : public Figure
{
protected:
    double a_=0.15*SCREEN_H;
    double x_;
    double y_;
public:
    double geta(){};
    double getx(){};
    double gety(){};
    Player2( double side ){};
    double half = a_/2;
    void MoveBy(double dy2 ){};
    virtual void Draw(){};
    void Move(){};
    virtual void Reset(){};
};