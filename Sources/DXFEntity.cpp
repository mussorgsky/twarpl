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

void Circle::insert_property(int group_code, float value)
{
    switch (group_code)
    {
    case 10:
        x = value;
        break;

    case 20:
        y = value;
        break;

    case 40:
        r = value;
        break;

    default:
        break;
    }
}

void Circle::bark()
{
    std::cout << "I'm a fully parsed CIRCLE :)\t";
    std::cout << "center at (" << x << ", " << y << ") with a radius of ";
    std::cout << "(" << r << ")\n";
}

void Arc::insert_property(int group_code, float value)
{
    switch (group_code)
    {
    case 10:
        x = value;
        break;

    case 20:
        y = value;
        break;

    case 40:
        r = value;
        break;

    case 50:
        start = value;
        break;

    case 51:
        end = value;
        break;

    default:
        break;
    }
}

void Arc::bark()
{
    std::cout << "I'm a fully parsed ARC :)\t";
    std::cout << "have a center (" << x << ", " << y << ") radius of " << r;
    std::cout << " and such start end angles (" << start << ", " << end << ")\n";
}
