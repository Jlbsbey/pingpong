#include "figure.hpp"
    Figure::Figure(){}
    Figure::~Figure(){};
    void Figure::Reset()=0;
    void Figure::Draw() = 0;
    void Figure::Move()=0;
    double Figure::getx(){
        return x_;
    }
    double Figure::gety(){
        return y_;
    }
     double Figure::geta()=0;