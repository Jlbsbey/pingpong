#include "square.hpp"
class Square : public Figure
{
protected:
    double a_;
    double x_;
    double y_;
public:
    double getx(){
        return x_;
    }
    double gety(){
        return y_;
    }
    double geta(){
        return a_;
    }
    Square( double a ) :
        Figure(),
        a_( 0.05*SCREEN_H )
    {
        int lim1=0.6*SCREEN_W;
        x_=SCREEN_W*0.2+(rand()%lim1);
        y_=rand()%int(SCREEN_H);
        while(0.40*SCREEN_W<x_ && x_<0.55*SCREEN_W && 0.40*SCREEN_H<y_ && y_<0.55*SCREEN_H){
            x_=SCREEN_W*0.2+(rand()%lim1-a_);
            y_=rand()%int(SCREEN_H- a_);
        }
    }
    virtual void Draw()
    {
        al_draw_filled_rectangle( x_, y_ , x_+a_, y_+a_, al_map_rgb( 255, 255, 255 ) );
    }
    virtual void Move()
    {
        dx_=0;
        dy_=0;
    };
    virtual void Reset(){
        int lim1=0.6*SCREEN_W;
        x_=SCREEN_W*0.2+(rand()%lim1);
        y_=rand()%int(SCREEN_H-a_);
        while(0.45*SCREEN_W<x_ && x_<0.55*SCREEN_W && 0.45*SCREEN_H<y_ && y_<0.55*SCREEN_H){
            x_=SCREEN_W*0.2+(rand()%lim1);
            y_=rand()%int(SCREEN_H-a_);
        }
    };
};