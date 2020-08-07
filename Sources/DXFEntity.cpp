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

void Ellipse::insert_property(int group_code, float value)
{
    switch (group_code)
    {
    case 10:
        center_x = value;
        break;

    case 20:
        center_y = value;
        break;

    case 11:
        major_x = value;
        break;

    case 21:
        major_y = value;
        break;

    case 40:
        ratio = value;
        break;

    case 41:
        start = value;
        break;

    case 42:
        end = value;
        break;

    default:
        break;
    }
}

void Ellipse::bark()
{
    std::cout << "I'm a fully parsed ELLIPSE :)\t";
    std::cout << "have a center (" << center_x << ", " << center_y << ") axis ratio of " << ratio;
    std::cout << " major axis is (" << major_x << ", " << major_y << ")";
    std::cout << " start and end (" << start << ", " << end << ")\n";
}
