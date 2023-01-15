#include <cstdlib>
#include "circle.hpp"
#include "square.hpp"
class FigureFactory
{
public:
    enum Type{};
    static Figure * Create( Type type ){};
};