#include <iostream>
#include "AllegroBase.hpp"
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
//пауза после отрисоки а не до; радиус не спавна около центра экрана
using namespace std;
const int FPS = 60;
const int SCREEN_H = 1040;
const int SCREEN_W = SCREEN_H/9*16;
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
typedef Figure * PFigure;
const int MAX =10;
int po1=0, po2=0;
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
            cout << po1 << ":" << po2 << endl;
            tmpReset(); //ресет всех фигур, что есть в массиве из фигур через сс.ресет
        }else if(( x_+10.0 > SCREEN_W )){
            po1++;
            system("cls");
            cout << po1 << ":" << po2 << endl;
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
        for( int i = 0; i < size_; ++i )
        {
            figures[i]->Draw();
        }
        p1->Draw();
        p2->Draw();
        c->Draw();
    }
    void Next()
    {
        if(GetKeyState(VK_UP) & 0x8000){
            p2->MoveBy(-7);
        }
        if(GetKeyState(VK_DOWN) & 0x8000){
            p2->MoveBy(7);
        }
        if(GetKeyState('W') & 0x8000){
            p1->MoveBy(-7);
        }
        if(GetKeyState('S') & 0x8000){
            p1->MoveBy(7);
        }
        for( int i = 0; i < figures.size() ; ++i )
        {
            if((c->getx()+10 >= figures[i]->getx() && c->getx()+10 < figures[i]->getx() + figures[i]->geta() && c->getx()-10 < figures[i]->getx() && c->gety() <= figures[i]->gety() + figures[i]->geta() && c->gety() >= figures[i]->gety() && c->getdx()>0 )
                || (c->getx()-10 <= figures[i]->getx()+figures[i]->geta() && c->getx()-10 > figures[i]->getx() && c->getx()+10> figures[i]->getx()+figures[i]->geta() && c->gety() <= figures[i]->gety() + figures[i]->geta() && c->gety() >= figures[i]->gety() && c->getdx()<0)){
                c->invertdx();
            }
            if((c->gety()+10 >= figures[i]->gety() && c->gety()+10 < figures[i]->gety() + figures[i]->geta() && c->gety()-10 < figures[i]->gety() && c->getx() >= figures[i]->getx() && c->getx() <= figures[i]->getx() + figures[i]->geta() && c->getdy()>0)
                || (c->gety()-10 <= figures[i]->gety() + figures[i]->geta() && c->gety()-10 > figures[i]->gety() && c->gety()+10 > figures[i]->gety()+ figures[i]->geta() && c->getx() >= figures[i]->getx() && c->getx() <= figures[i]->getx() + figures[i]->geta() && c->getdy()<0)){
                c->invertdy();
            }
           figures[i]->Move();
        }
        if((c->getx()+10 >= p2->getx() && c->getx()+10 < p2->getx() + SCREEN_W*0.01 && c->getx()-10 < p2->getx() && c->gety() <= p2->gety() + p2->geta() && c->gety() >= p2->gety() && c->getdx()>0 )
            || (c->getx()-10 <= p1->getx() +SCREEN_W*0.01 && c->getx()-10 > p1->getx() && c->getx()+10 > p1->getx()+SCREEN_W*0.01 && c->gety() <= p1->gety() + p1->geta() && c->gety() >= p1->gety() && c->getdx()<0)){
                c->invertdx();
            }
        if((c->gety()+10 >= p1->gety() && c->gety()+10 < p1->gety() + p1->geta() && c->gety()-10 < p1->gety() && c->getx() >= p1->getx() && c->getx() <= p1->getx() + SCREEN_W*0.01 && c->getdy()>0)
            || (c->gety()-10 <= p1->gety() + p1->geta() && c->gety()-10 > p1->gety() && c->gety()+10 > p1->gety()+ SCREEN_W*0.01 && c->getx() >= p1->getx() && c->getx() <= p1->getx() + SCREEN_W*0.01 && c->getdy()<0)){
                c->invertdy();
            }
        if((c->gety()+10 >= p2->gety() && c->gety()+10 < p2->gety() + p2->geta() && c->gety()-10 < p2->gety() && c->getx() >= p2->getx() && c->getx() <= p2->getx() + SCREEN_W*0.01 && c->getdy()>0)
            || (c->gety()-10 <= p2->gety() + p2->geta() && c->gety()-10 > p2->gety() && c->gety()+10 > p2->gety()+ SCREEN_W*0.01 && c->getx() >= p2->getx() && c->getx() <= p2->getx() + SCREEN_W*0.01 && c->getdy()<0)){
                c->invertdy();
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
        p1->Reset();
        p2->Reset();
    }
private:
    ScreenSaver() :
        size_( 0 )
    {
        c = new Circle( 10.0 );
        p1 = new Player1(0.3*SCREEN_H);
        p2 = new Player2( 0.3*SCREEN_H );
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
public:
    AllegroApp() :
        AllegroBase()
    {
        for( int i = 0; i < 10; ++i )
        {
            ScreenSaver::Instance().Add(
                FigureFactory::Create( FigureFactory::RandomSquare ) );
        }
    }
    virtual void Fps()
    {
        ScreenSaver::Instance().Next();
    }
    virtual void Draw()
    {
        ScreenSaver::Instance().Draw();
    }
    virtual void OnKeyDown( const ALLEGRO_KEYBOARD_EVENT &keyboard )
    {
        if ( keyboard.keycode == ALLEGRO_KEY_SPACE )
        {
            po1=0;
            po2=0;
            ScreenSaver::Instance().Reset();
        }
        else if ( keyboard.keycode == ALLEGRO_KEY_ESCAPE )
        {
            Exit();
            cout << "Successfully exited!" << endl;
        }
    }
};
void AltEnter()
{
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
    return;
}
int main(int argc, char **argv)
{
    AltEnter();
    srand( time(0) );
    system("cls");
    cout << po1 << ":" << po2 << endl;
    AllegroApp app;
    if ( !app.Init( SCREEN_W, SCREEN_H, FPS ) )
    {
        return 1;
    }
    app.Run();
    // cin.get();
    return 0;
}
