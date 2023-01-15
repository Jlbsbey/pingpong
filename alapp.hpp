#include "AllegroBase.hpp"
#include <windows.h>
#include <iostream>
#include "var.cpp"
#include "ss.hpp"
#include "figurefactory.hpp"
class AllegroApp : public AllegroBase
{
private:
public:
    AllegroApp(){};
    virtual void Fps(){};
    virtual void Draw(){};
    virtual void OnKeyDown( const ALLEGRO_KEYBOARD_EVENT &keyboard ){};
};
void AltEnter(){}