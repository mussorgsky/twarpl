#include "DXFEntity.hpp"

namespace DXF
{
    void Line::insert_property(int group_code, float value)
    {
        switch (group_code)
        {
        case Codes::CP_X:
            start_x = value;
            break;

        case Codes::CP_Y:
            start_y = value;
            break;

        case Codes::FP_X:
            end_x = value;
            break;

        case Codes::FP_Y:
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
        case Codes::CP_X:
            center_x = value;
            break;

        case Codes::CP_Y:
            center_y = value;
            break;

        case Codes::RADIUS:
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
        case Codes::CP_X:
            center_x = value;
            break;

        case Codes::CP_Y:
            center_y = value;
            break;

        case Codes::RADIUS:
            radius = value;
            break;

        case Codes::START_ANGLE:
            start = value;
            break;

        case Codes::END_ANGLE:
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
        case Codes::CP_X:
            center_x = value;
            break;

        case Codes::CP_Y:
            center_y = value;
            break;

        case Codes::FP_X:
            major_x = value;
            break;

        case Codes::FP_Y:
            major_y = value;
            break;

        case Codes::SEMIMAJOR_AXIS_RATIO:
            ratio = value;
            break;

        case Codes::ELLIPSE_START:
            start = value;
            break;

        case Codes::ELLIPSE_END:
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
        case Codes::CP_X:
            x.push_back(value);
            break;

        case Codes::CP_Y:
            y.push_back(value);
            break;

        case Codes::KNOT_VALUE:
            knots.push_back(value);
            break;

        case Codes::KNOT_TOLERANCE:
            knot_tolerance = value;
            break;

        case Codes::SPLINE_FLAG:
            flags = (int)value;
            break;

        case Codes::SPLINE_DEGREE:
            degree = (int)value;
            break;

        case Codes::KNOT_COUNT:
            knot_count = (int)value;
            knots.reserve(knot_count);
            break;

        case Codes::CP_COUNT:
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

} // namespace DXF
