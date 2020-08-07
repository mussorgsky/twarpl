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

void Spline::insert_property(int group_code, float value)
{
    switch (group_code)
    {
    case 10:
        x.push_back(value);
        break;

    case 20:
        y.push_back(value);
        break;

    case 40:
        knots.push_back(value);
        break;

    case 42:
        knot_tolerance = value;
        break;

    case 70:
        flags = (int)value;
        break;

    case 71:
        degree = (int)value;
        break;

    case 72:
        knot_count = (int)value;
        knots.reserve(knot_count);
        break;

    case 73:
        cp_count = (int)value;
        x.reserve(cp_count);
        y.reserve(cp_count);
        break;

    default:
        break;
    }
}

void Spline::bark()
{
    std::cout << "I'm a fully parsed spline :)\t";
    std::cout << "my flags " << flags << " my degree " << degree;
    std::cout << " tolerance " << knot_tolerance << "\n";

    std::cout << "\tI've got " << knot_count << " knots:\t";
    for (float knot : knots)
    {
        std::cout << knot << ", ";
    }
    std::cout << "\n";

    std::cout << "\tI've got " << cp_count << " control points:\t";
    for (int i = 0; i < cp_count; ++i)
    {
        std::cout << "(" << x[i] << ", " << y[i] << "), ";
    }
    std::cout << "\n";
}
