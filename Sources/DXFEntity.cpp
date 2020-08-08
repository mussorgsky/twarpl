#include "DXFEntity.hpp"

namespace DXF
{
    void Line::insert_property(int group_code, float value)
    {
        switch (group_code)
        {
        case Codes::CP_X:
            start.x = value;
            break;

        case Codes::CP_Y:
            start.y = value;
            break;

        case Codes::FP_X:
            end.x = value;
            break;

        case Codes::FP_Y:
            end.y = value;
            break;

        default:
            break;
        }
    }

    void Line::bark()
    {
        std::cout << "I'm a fully parsed LINE :)\t";
        std::cout << "I start at (" << start.x << ", " << start.y << ") and end at ";
        std::cout << "(" << end.x << ", " << end.y << ")\n";
    }

    void Circle::insert_property(int group_code, float value)
    {
        switch (group_code)
        {
        case Codes::CP_X:
            center.x = value;
            break;

        case Codes::CP_Y:
            center.y = value;
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
        std::cout << "center at (" << center.x << ", " << center.y << ") with a radius of ";
        std::cout << "(" << radius << ")\n";
    }

    void Arc::insert_property(int group_code, float value)
    {
        switch (group_code)
        {
        case Codes::CP_X:
            center.x = value;
            break;

        case Codes::CP_Y:
            center.y = value;
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
        std::cout << "have a center (" << center.x << ", " << center.y << ") radius of " << radius;
        std::cout << " and such start end angles (" << start << ", " << end << ")\n";
    }

    void Ellipse::insert_property(int group_code, float value)
    {
        switch (group_code)
        {
        case Codes::CP_X:
            center.x = value;
            break;

        case Codes::CP_Y:
            center.y = value;
            break;

        case Codes::FP_X:
            major_axis.x = value;
            break;

        case Codes::FP_Y:
            major_axis.y = value;
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
        std::cout << "have a center (" << center.x << ", " << center.y << ") axis ratio of " << ratio;
        std::cout << " major axis is (" << major_axis.x << ", " << major_axis.y << ")";
        std::cout << " start and end (" << start << ", " << end << ")\n";
    }

    void Spline::insert_property(int group_code, float value)
    {
        switch (group_code)
        {
        case Codes::CP_X:
            cps.push_back(Point{value, 0.0f});
            break;

        case Codes::CP_Y:
            cps.back().y = value;
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
            knots.reserve((int)value);
            break;

        case Codes::CP_COUNT:
            cps.reserve((int)value);
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

        std::cout << "\tI've got " << knots.size() << " knots:\t";
        for (float knot : knots)
        {
            std::cout << knot << ", ";
        }
        std::cout << "\n";

        std::cout << "\tI've got " << cps.size() << " control points:\t";
        for (Point cp : cps)
        {
            std::cout << "(" << cp.x << ", " << cp.y << "), ";
        }
        std::cout << "\n";
    }

} // namespace DXF
