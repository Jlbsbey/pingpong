#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class AllegroBase
{
public:
    enum
    {
        ALLEGRO_MOUSE_KEY_1 = ALLEGRO_KEY_MAX,
        ALLEGRO_MOUSE_KEY_2,
        ALLEGRO_MOUSE_KEY_3,
        ALLEGRO_MOUSE_KEY_4,
        ALLEGRO_MOUSE_KEY_5,
        ALLEGRO_MOUSE_KEY_6,
        ALLEGRO_MOUSE_KEY_7,
        ALLEGRO_MOUSE_KEY_8,
        ALLEGRO_MOUSE_KEY_9,
        ALLEGRO_MOUSE_KEY_10,
    };

    AllegroBase();
    virtual ~AllegroBase();

    bool Init( int screenWidth, int screenHeight, int fps );
    void Destroy();
    void Run();
    void Exit();

    // See help for ALLEGRO_KEYBOARD_STATE
    bool IsPressed( int keycode );
    // See help for ALLEGRO_MOUSE_KEY_1
    bool IsMousePressed( int buttonIndex );

    virtual void Fps() = 0;
    virtual void Draw() = 0;
    virtual void OnKeyDown( const ALLEGRO_KEYBOARD_EVENT &keyboard ) {};
    virtual void OnKeyUp( const ALLEGRO_KEYBOARD_EVENT &keyboard ) {};
    virtual void OnMouseMove( const ALLEGRO_MOUSE_EVENT &mouse ) {};
    virtual void OnMouseUp( const ALLEGRO_MOUSE_EVENT &mouse ) {};
    virtual void OnMouseDown( const ALLEGRO_MOUSE_EVENT &mouse ) {};

protected:
    enum
    {
        ALLEGRO_MOUSE_KEY_MAX = ALLEGRO_MOUSE_KEY_10 - ALLEGRO_MOUSE_KEY_1 + 1,
        ALLEGRO_MOUSE_KEY_OFFSET = ALLEGRO_KEY_MAX,
    };

    ALLEGRO_DISPLAY *alDisplay_;
    ALLEGRO_EVENT_QUEUE *alEventQueue_;
    ALLEGRO_TIMER *alTimer_;
    bool pressedKeys_[ALLEGRO_KEY_MAX + ALLEGRO_MOUSE_KEY_MAX];

private:
    bool exit_;

};
