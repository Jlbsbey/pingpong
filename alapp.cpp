#include "alapp.hpp"
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
            std::cout << "Successfully exited!" << std::endl;
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