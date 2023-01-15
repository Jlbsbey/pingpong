#include "figurefactory.hpp"
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