#include "players.hpp"
class Player1 : public Figure
{
protected:
    double a_=0.15*SCREEN_H;
    double x_;
    double y_;
public:
    double geta(){
        return a_;
    }
    double getx(){
        return x_;
    }
    double gety(){
        double y=y_-half;
        return y;
    }
    Player1( double side ) :
        Figure()
    {
        x_=SCREEN_W*0.1;
        y_ = SCREEN_H/2;
    }
    double half = a_/2;
    void MoveBy(double dy1 )
    {
        dy_ = dy1;
        Move();
    }
    virtual void Draw()
    {
        al_draw_filled_rectangle( SCREEN_W*0.1,  y_+half,
            SCREEN_W*0.11, y_-half, al_map_rgb( 255, 255, 255 ) );
    }
    void Move(){
        if(y_+a_/2 >=SCREEN_H && dy_ >0 || y_- a_ /2 <= 1 && dy_ <0){
            dy_ = 0;
            y_+=dy_;
        } else{
            y_+=dy_;
        }

    };
    virtual void Reset(){
        y_ = SCREEN_H/2;
    }
};
class Player2 : public Figure
{
protected:
    double a_=0.15*SCREEN_H;
    double x_;
    double y_;
public:
    double geta(){
        return a_;
    }
    double getx(){
        return x_;
    }
    double gety(){
        double y=y_-half;
        return y;
    }
    Player2( double side ) :
        Figure()
    {
        x_=SCREEN_W*0.89;
        y_ = SCREEN_H/2;
    }
    double half = a_/2;
    void MoveBy(double dy2 )
    {
        dy_ = dy2;
        Move();
    }
    virtual void Draw()
    {
        al_draw_filled_rectangle( SCREEN_W*0.89,  y_+half,
            SCREEN_W*0.9, y_-half, al_map_rgb( 255, 255, 255 ) );
    }
    void Move(){
        if(y_+a_/2 >=SCREEN_H && dy_ >0 || y_- a_ /2 <= 1 && dy_ <0){
            dy_ = 0;
            y_+=dy_;
        } else{
            y_+=dy_;
        }

    };
    virtual void Reset(){
        y_ = SCREEN_H/2;
    }
};