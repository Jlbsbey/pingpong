#include <iostream>
#include "AllegroBase.hpp"
#include <windows.h>
#include <cstdlib>
#include <cstdio>
//вывод счета; ресет линий, которые отбивают мяч, если они не состоят в массиве из фигур(?); пауза после отрисоки а не до
/*using namespace std;

const int FPS = 60;
const int SCREEN_W = 1280;
const int SCREEN_H = 720;

class Figure
{
protected:
    double x_;
    double y_;
    double dx_;
    double dy_;

public:
    Figure(){}
    virtual ~Figure(){};
    virtual void Reset()=0;
    virtual void Draw() = 0;
    virtual void Move()=0;
};


class Square : public Figure
{
protected:
    double a_;
    double x_=SCREEN_W/2+(rand()%768) - SCREEN_W*0.3;
    double y_=rand()%600 +40;
public:
    Square( double a ) :
        Figure(),
        a_( 30 )
    {}
    virtual void Draw()
    {
        al_draw_filled_rectangle( x_, y_ , x_+a_, y_-a_, al_map_rgb( 255, 255, 255 ) );
    }
    virtual void Move()
    {
        dx_=0;
        dy_=0;
    };
    virtual void Reset(){
        x_=SCREEN_W/2+(rand()%768) - SCREEN_W*0.3;
        y_=rand()%600 +40;
        al_draw_filled_rectangle( x_, y_ , x_+a_, y_-a_, al_map_rgb( 255, 255, 255 ) );
    };
};

typedef Figure * PFigure;
const int MAX = 6;

class ScreenSaver
{
private:
    PFigure figures[MAX];
    int size_;
public:
    static ScreenSaver &Instance()
    {
        static ScreenSaver instance;
        return instance;
    }

    void Draw()
    {
        al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
        for( int i = 0; i < size_; ++i )
        {
            figures[i]->Draw();
        }
    }

    void Next()
    {
        for( int i = 0; i < size_; ++i )
        {
            figures[i]->Move();
        }
    }

    void Add( Figure *f )
    {
        if ( size_ >= MAX )
        {
            return;
        }
        figures[ size_ ] = f;
        ++size_;
    }

    void Reset()
    {
        for( int i = 0; i < size_; ++i )
        {
            figures[i]->Reset();
        }
    }

private:
    ScreenSaver() :
        size_( 0 )
    {
        memset( figures, 0, sizeof( figures ) );
    }

    ~ScreenSaver()
    {
        for( int i = 0; i < size_; ++i )
        {
            delete figures[i];
            figures[i] = 0;
        }
    }
};
*/


class Circle : public Figure
{
protected:
    double r_;
public:
    Circle( double r ) :
        Figure()
    {
    }
    virtual void Draw()
    {
        al_draw_filled_circle( x_, y_, 10, al_map_rgb( 255, 255, 255 ) );
    }
    virtual void Move()
    {
        x_ += dx_;
        y_ += dy_;
        if ( ( x_ < 1.0 ) ||
             ( x_ > SCREEN_W ))
        {
            ScreenSaver::Instance().Reset(); //ресет всех фигур, что есть в массиве из фигур через сс.ресет
        }else if ( ( y_ < 1.0 ) ||
            ( y_ > SCREEN_H ))
        {
            dy_= -dy_;
        }
    };
    void Reset()
    {
        x_ = SCREEN_W/2;
        y_ = SCREEN_H/2;
        dx_ = (rand() % 10) - 5;
        if( dx_ == 0){ dx_ = 1; }
        dy_ = 5.0;
        al_draw_filled_circle( x_, y_, 10, al_map_rgb( 255, 255, 255 ) );
    }
};

class Player1 : public Figure
{
protected:
    double a_=0.3*SCREEN_H;
public:
    Player1( double side ) :
        Figure()
    {
        y_=SCREEN_H/2;
    }
    double half = a_/2;
    void MoveBy(double dy )
    {
        dy_ = dy;
        Move();
    }
    virtual void Draw()
    {
        al_draw_filled_rectangle( SCREEN_W*0.1,  y_-half, SCREEN_W*0.11, y_+half, al_map_rgb( 255, 255, 255 ) );
    }
    void Move(){
        if(y_+half >=SCREEN_H && dy_ >0 || y_-half <= 1 && dy_ <0){
            dy_ = 0;
            y_+=dy_;
        } else{
            y_+=dy_;
        }
    };
    void Reset(){
        y_ = SCREEN_H/2;
    };
};

class Player2 : public Figure
{
protected:
    double a_=0.3*SCREEN_H;
public:
    Player2( double side ) :
        Figure()
    {
        y_=SCREEN_H/2;
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
        if(y_+half >=SCREEN_H && dy_ >0 || y_-half <= 1 && dy_ <0){
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

class FigureFactory
{
public:
    enum Type
    {
        RandomCircle,
        RandomSquare
    };

    static Figure * Create( Type type )
    {
        switch( type )
        {
            case RandomCircle:
                return new Circle( 10.0 + rand() % 30 );
            case RandomSquare:
                return new Square( 10.0 + rand() % 30 );
        }
    }
};

class AllegroApp : public AllegroBase
{
private:
    Player1 humanSquare_;
    Player2 humanSquare2_;
public:
    AllegroApp() :
        AllegroBase(),
        humanSquare_( 30 ),
        humanSquare2_( 30 )
    {
        ScreenSaver::Instance().Add(
                    FigureFactory::Create( FigureFactory::RandomCircle ) );
        for( int i = 0; i < 10; ++i )
        {
                ScreenSaver::Instance().Add(
                    FigureFactory::Create( FigureFactory::RandomSquare ) );

        }
    }

    virtual void Fps()
    {
        ScreenSaver::Instance().Next();

        double dy = 0, dy2=0;
        if ( IsPressed( ALLEGRO_KEY_UP ) )
        {
            dy2 = -5;
        }
        if(IsPressed(ALLEGRO_KEY_W )){
            dy = -5;
        }
        if ( IsPressed( ALLEGRO_KEY_DOWN ) )
        {
            dy2 = +5;
        }
        if(IsPressed(ALLEGRO_KEY_S )){
            dy = +5;
        }
        humanSquare_.MoveBy(dy);
        humanSquare2_.MoveBy(dy2);
    }

    virtual void Draw()
    {
        ScreenSaver::Instance().Draw();
        humanSquare_.Draw();
        humanSquare2_.Draw();
    }

    virtual void OnKeyDown( const ALLEGRO_KEYBOARD_EVENT &keyboard )
    {
        if ( keyboard.keycode == ALLEGRO_KEY_SPACE )
        {
            ScreenSaver::Instance().Reset();
            humanSquare_.Reset();
            humanSquare2_.Reset();
        }
        else if ( keyboard.keycode == ALLEGRO_KEY_ESCAPE )
        {
            Exit();
            cout << "Successfully exited!" << endl;
        }
    }
};


int main(int argc, char **argv)
{
    srand( time(0) );

    AllegroApp app;
    if ( !app.Init( SCREEN_W, SCREEN_H, FPS ) )
    {
        return 1;
    }
    app.Run();

    // cin.get();
    return 0;
}