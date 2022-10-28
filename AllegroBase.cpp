#include "AllegroBase.hpp"
#include <iostream>

using namespace std;


AllegroBase::AllegroBase() :
    alDisplay_( 0 ),
    alEventQueue_( 0 ),
    alTimer_( 0 ),
    exit_( false )
{
    memset( pressedKeys_, 0, sizeof( pressedKeys_ ) );
}

AllegroBase::~AllegroBase()
{
    Destroy();
}

bool AllegroBase::Init( int screenWidth, int screenHeight, int fps )
{
    if( !al_init() )
    {
        cout << "failed to initialize allegro!" << endl;
        return false;
    }

    alTimer_ = al_create_timer( 1.0 / fps );
    if( !alTimer_ )
    {
        cout << "failed to create timer!" << endl;
        return false;
    }

    alDisplay_ = al_create_display( screenWidth, screenHeight );
    if( !alDisplay_ )
    {
        cout << "failed to create display!" << endl;
        return false;
    }

    if ( !al_init_primitives_addon() )
    {
        cout << "failed to init addons!" << endl;
        return false;
    }

    alEventQueue_ = al_create_event_queue();
    if( !alEventQueue_ )
    {
        cout << "failed to create event queue!" << endl;
        return false;
    }

    if( !al_install_keyboard() )
    {
        cout << "failed to install keyboard!" << endl;
        return false;
    }

    if( !al_install_mouse() )
    {
        cout << "failed to initialize the mouse!" << endl;
        return false;
    }

    al_register_event_source( alEventQueue_, al_get_display_event_source( alDisplay_ ) );
    al_register_event_source( alEventQueue_, al_get_timer_event_source( alTimer_ ) );
    al_register_event_source( alEventQueue_, al_get_keyboard_event_source() );
    al_register_event_source( alEventQueue_, al_get_mouse_event_source() );

    exit_ = false;

    return true;

}

void AllegroBase::Destroy()
{
    if( alTimer_ )
    {
        al_destroy_timer( alTimer_ );
        alTimer_ = 0;
    }

    if ( alDisplay_ )
    {
        al_destroy_display( alDisplay_ );
        alDisplay_ = 0;
    }

    if ( alEventQueue_ )
    {
        al_destroy_event_queue( alEventQueue_ );
        alEventQueue_ = 0;
    }

}

void AllegroBase::Run()
{
    // clear screen
    al_clear_to_color( al_map_rgb( 0, 0, 0 ) );
    al_flip_display();

    al_start_timer( alTimer_ );

    bool redraw = false;
    while( true )
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event( alEventQueue_, &ev );

        if( ev.type == ALLEGRO_EVENT_TIMER )
        {
            Fps();
            redraw = true;
        }
        else if( ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE )
        {
            break;
        }
        else if( ev.type == ALLEGRO_EVENT_KEY_DOWN )
        {
            pressedKeys_[ ev.keyboard.keycode ] = true;
            OnKeyDown( ev.keyboard );
        }
        else if ( ev.type == ALLEGRO_EVENT_KEY_UP )
        {
            pressedKeys_[ ev.keyboard.keycode ] = false;
            OnKeyUp( ev.keyboard );
        }
        else if ( ( ev.type == ALLEGRO_EVENT_MOUSE_AXES ) ||
                  ( ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY ) )
        {
            OnMouseMove( ev.mouse );
        }
        else if( ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN )
        {
            pressedKeys_[ ALLEGRO_MOUSE_KEY_OFFSET + ev.mouse.button - 1 ] = true;
            OnMouseDown( ev.mouse );
        }
        else if( ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP )
        {
            pressedKeys_[ ALLEGRO_MOUSE_KEY_OFFSET + ev.mouse.button - 1 ] = false;
            OnMouseUp( ev.mouse );
        }

        if( redraw && al_is_event_queue_empty( alEventQueue_ ) )
        {
            redraw = false;
            Draw();
            al_flip_display();
        }

        if ( exit_ )
        {
            break;
        }
   }
}

void AllegroBase::Exit()
{
    exit_ = true;
}

bool AllegroBase::IsPressed( int keycode )
{
    return pressedKeys_[ keycode ];
}

bool AllegroBase::IsMousePressed(int keycode)
{
    return pressedKeys_[ALLEGRO_MOUSE_KEY_OFFSET + keycode - ALLEGRO_MOUSE_KEY_1];
}
