#include <vector>
#include <iostream>
#include <windows.h>
#include "AllegroBase.hpp"
#include "var.cpp"
#include "circle.hpp"
#include "players.hpp"
class ScreenSaver
{
private:
    vector< PFigure > figures;
    int size_;
    Circle *c;
    Player1 *p1;
    Player2 *p2;
public:
    static ScreenSaver &Instance(){};
    void Draw(){};
    void Next(){};
    void Add( Figure *f ){};
    void Reset(){};
private:
    ScreenSaver(){};
    ~ScreenSaver(){};
};