#include <iostream>
#include "AllegroBase.hpp"
#include <windows.h>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "figure.hpp"
#include "square.hpp"
#include "alapp.hpp"
#include "ss.hpp"
#include "figurefactory.hpp"
#include "players.hpp"
#include "var.cpp"
using namespace std;

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
