#include "ss.hpp"
class ScreenSaver
{
private:
    std::vector< PFigure > figures;
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