#include "DXFEntity.hpp"

void Line::insert_property(int group_code, float value)
{
    switch (group_code)
    {
    case 10:
        start_x = value;
        break;

    case 20:
        start_y = value;
        break;

    case 11:
        end_x = value;
        break;

    case 21:
        end_y = value;
        break;

    default:
        break;
    }
}

void Line::bark()
{
    std::cout << "I'm a fully parsed LINE :)\t";
    std::cout << "I start at (" << start_x << ", " << start_y << ") and end at ";
    std::cout << "(" << end_x << ", " << end_y << ")\n";
}

void Circle::insert_property(int group_code, float value)
{
    switch (group_code)
    {
    case 10:
        center_x = value;
        break;

    case 20:
        center_y = value;
        break;

    case 40:
        radius = value;
        break;

    default:
        break;
    }
}

void Circle::bark()
{
    std::cout << "I'm a fully parsed CIRCLE :)\t";
    std::cout << "center at (" << center_x << ", " << center_y << ") with a radius of ";
    std::cout << "(" << radius << ")\n";
}

void Arc::insert_property(int group_code, float value)
{
    switch (group_code)
    {
    case 10:
        center_x = value;
        break;

    case 20:
        center_y = value;
        break;

    case 40:
        radius = value;
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
    std::cout << "have a center (" << center_x << ", " << center_y << ") radius of " << radius;
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
