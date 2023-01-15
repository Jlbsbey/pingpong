#include "circle.hpp"
class Circle : public Figure
{
protected:
    double r_;
public:
    double geta(){}
    void invertdx(){
        dx_=-dx_;
    }
    void invertdy(){
        dy_=-dy_;
    }
    double getx(){
        return x_;
    }
    double gety(){
        return y_;
    }
    double getdx(){
        return dx_;
    }
    double getdy(){
        return dy_;
    }
    Circle( double r ) :
        Figure()
    {
        x_ = SCREEN_W/2;
        y_ = SCREEN_H/2;
        int rnd= rand()%4;
        switch (rnd)
        {
        case 0:
            dx_ = 9;
            dy_ = 5;
            break;
        case 1:
            dx_ = -9;
            dy_ = 5;
            break;
        case 2:
            dx_ = 9;
            dy_ = -5;
            break;
        case 3:
            dx_ = -9;
            dy_ = -5;
            break;
        default:
            break;
        }
    }
    virtual void Draw()
    {
        al_draw_filled_circle( x_, y_, 10, al_map_rgb( 255, 255, 255 ) );
    }
    virtual void Move()
    {
        x_ += dx_;
        y_ += dy_;
        if ( ( x_ < 10.0))
        {
            po2++;
            system("cls");
            std::cout << po1 << ":" << po2 << std::endl;
            tmpReset(); //ресет всех фигур, что есть в массиве из фигур через сс.ресет
        }else if(( x_+10.0 > SCREEN_W )){
            po1++;
            system("cls");
            std::cout << po1 << ":" << po2 << std::endl;
            tmpReset();
        }
        if ( ( y_ < 10.0 ) ||
            ( y_+10.0 > SCREEN_H ))
        {
            invertdy();
        }
    };
    void Reset()
    {
        x_ = SCREEN_W/2;
        y_ = SCREEN_H/2;
        int rnd= rand()%4;
        switch (rnd)
        {
        case 0:
            dx_ = 9;
            dy_ = 5;
            break;
        case 1:
            dx_ = -9;
            dy_ = 5;
            break;
        case 2:
            dx_ = 9;
            dy_ = -5;
            break;
        case 3:
            dx_ = -9;
            dy_ = -5;
            break;
        default:
            break;
        }
    }
};