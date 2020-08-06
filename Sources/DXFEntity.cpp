#include "DXFEntity.hpp"

void Line::insert_property(int group_code, float value)
{
    switch (group_code)
    {
    case 10:
        x1 = value;
        break;

    case 20:
        y1 = value;
        break;

    case 11:
        x2 = value;
        break;

    case 21:
        y2 = value;
        break;

    default:
        break;
    }
}

void Line::bark()
{
    std::cout << "I'm a fully parsed LINE :)\t";
    std::cout << "I start at (" << x1 << ", " << y1 << ") and end at ";
    std::cout << "(" << x2 << ", " << y2 << ")\n";
}