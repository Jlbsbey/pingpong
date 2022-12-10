#include <iostream>
#include "AllegroBase.hpp"
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
//вывод счета; ресет линий, которые отбивают мяч, если они не состоят в массиве из фигур(?); пауза после отрисоки а не до; радиус не спавна около центра экрана
using namespace std;

const int FPS = 60;
const int SCREEN_W = 1280;
const int SCREEN_H = 720;
int p1=0, p2=0;
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
    virtual double getx(){
        return x_;
    }
    virtual double gety(){
        return y_;
    }
    virtual double geta()=0;
};


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
        a_( 30 )
    {
        x_=SCREEN_W/2+(rand()%768) - SCREEN_W*0.3;
        y_=rand()%600 +40;
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
        x_=SCREEN_W/2+(rand()%768) - SCREEN_W*0.3;
        y_=rand()%600 +40;
    };
};

typedef Figure * PFigure;
const int MAX =6;
void tmpReset();

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
        if ( ( x_ < 10.0 ))
        {
            p2++;
            tmpReset(); //ресет всех фигур, что есть в массиве из фигур через сс.ресет
        }else if(( x_+10.0 > SCREEN_W )){
            p1++;
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
        dx_ = (rand() % 10) - 5;
        if( dx_ == 0){ dx_ = 5.0; }
        dy_ = 5.0;
    }
};

class Player1 : public Figure
{
protected:
    double a_=0.3*SCREEN_H;
public:
    double geta(){
        return a_;
    }
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
    double geta(){
        return a_;
    }
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

class ScreenSaver
{
private:
    vector< PFigure > figures;
    int size_;
    Circle *c;
    Player1 *p1;
    Player2 *p2;
public:
    static ScreenSaver &Instance()
    {
        static ScreenSaver instance;
        return instance;
    }

    void Draw()
    {
        al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
        /*al_init_font_addon();
        al_init_ttf_addon();*/
        //const string text  =(char*) p1 + ' : ' +p2;
        //al_draw_text( al_load_font( "arial.ttf", 50, 0 ), al_map_rgb( 255, 255, 255 ), SCREEN_W/2, SCREEN_H/2, ALLEGRO_ALIGN_CENTRE, "123" );

        for( int i = 0; i < size_; ++i )
        {
            figures[i]->Draw();
        }
        c->Draw();
    }

    void Next()
    {
        for( int i = 0; i < figures.size() ; ++i )
        {

            if((c->getx()+10 >= figures[i]->getx() && c->getx()+10 < figures[i]->getx() + figures[i]->geta() && c->gety() <= figures[i]->gety() + figures[i]->geta() && c->gety() >= figures[i]->gety() )
                || (c->getx()-10 <= figures[i]->getx()+figures[i]->geta() && c->getx()-10 > figures[i]->getx() && c->gety() <= figures[i]->gety() + figures[i]->geta() && c->gety() >= figures[i]->gety())){
                c->invertdx();
            }

            if((c->gety()+10 >= figures[i]->gety() && c->gety()+10 < figures[i]->gety() + figures[i]->geta() && c->getx() >= figures[i]->getx() && c->getx() <= figures[i]->getx() + figures[i]->geta())
                || (c->gety()-10 <= figures[i]->gety() + figures[i]->geta() && c->gety()-10 > figures[i]->gety() && c->getx() >= figures[i]->getx() && c->getx() <= figures[i]->getx() + figures[i]->geta())){
                c->invertdy();
            }
            if((c->getx()-10 <= p1->getx()+0.01*SCREEN_W && c->gety()+8 >= p1->gety() && c->gety()-8 <= p1->gety()+p1->geta())
                || (c->getx()+10 >= p2->getx() && c->gety()+8 >= p2->gety() && c->gety()-8 <= p2->gety()+p2->geta())){
                c->invertdx();
            }
           figures[i]->Move();
        }
        c->Move();
    }

    void Add( Figure *f )
    {
        if ( size_ >= MAX )
        {
            return;
        }
        figures.push_back(f);
        ++size_;
    }

    void Reset()
    {
        for( int i = 0; i < size_; ++i )
        {
           figures[i]->Reset();
        }
        c->Reset();
    }

private:
    ScreenSaver() :
        size_( 0 )
    {
        c = new Circle( 10.0 );
        //p1 = new Player1( 40.0 );
        //p2 = new Player2( 40.0 );
    }

    ~ScreenSaver()
    {
        for( int i = 0; i < size_; ++i )
        {
            delete figures[i];
        }
    }
};

void tmpReset() {
ScreenSaver::Instance().Reset();
}



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
        /*ScreenSaver::Instance().Add(
            FigureFactory::Create( FigureFactory::RandomCircle ) );*/
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
