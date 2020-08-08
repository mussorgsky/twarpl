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

    std::vector<Point> Line::make_points(float step)
    {
        float length = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));

        int step_count = (int)std::ceil(length / step);
        int point_count = step_count + 1;

        Point step_vector{(end.x - start.x) / step_count, (end.y - start.y) / step_count};

        std::vector<Point> points;
        points.reserve(point_count);
        points.push_back(start);
        for (int i = 0; i < step_count; ++i)
        {
            Point new_point;
            new_point.x = points.back().x + step_vector.x;
            new_point.y = points.back().y + step_vector.y;
            points.push_back(new_point);
        }

        for (Point p : points)
        {
            std::cout << p.x << ", " << p.y << "\n";
        }
        std::cout << "\n";

        return points;
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

    std::vector<Point> Circle::make_points(float step)
    {
        std::vector<Point> points;

        if (radius == 0.0f)
        {
            return points;
        }
        const float pi = 3.14159f;
        float circumference = 2.0f * pi * radius;

        int step_count = (int)std::ceil(circumference / step);
        int point_count = step_count + 1;

        float step_angle = 2.0f * pi / step_count;
        float angle = 0.0f;

        points.reserve(point_count);

        while (angle < 2.0f * pi)
        {
            Point new_point;
            new_point.x = center.x + std::cos(angle) * radius;
            new_point.y = center.y + std::sin(angle) * radius;
            points.push_back(new_point);
            angle += step_angle;
        }

        for (Point p : points)
        {
            std::cout << p.x << ", " << p.y << "\n";
        }
        std::cout << "\n";

        return points;
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

    std::vector<Point> Arc::make_points(float step)
    {
        std::vector<Point> points;

        if (radius == 0.0f)
        {
            return points;
        }
        const float pi = 3.14159f;
        const float span_angle = (start > end) ? (360.0f - start + end) : end - start;
        const float length = 2.0f * pi * radius * span_angle / 360.0f;

        const int step_count = (int)std::ceil(length / step);
        const int point_count = step_count + 1;

        float step_angle = span_angle * pi / 180.0f / step_count;
        float angle = start * pi / 180.0f;

        points.reserve(point_count);

        for (int i = 0; i < point_count; ++i)
        {
            Point new_point;
            new_point.x = center.x + std::cos(angle) * radius;
            new_point.y = center.y + std::sin(angle) * radius;
            points.push_back(new_point);
            angle += step_angle;
        }

        for (Point p : points)
        {
            std::cout << p.x << ", " << p.y << "\n";
        }
        std::cout << "\n";

        return points;
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

    std::vector<Point> Ellipse::make_points(float step)
    {
        std::vector<Point> points;

        const float major_length = std::sqrt(std::pow(major_axis.x, 2) + std::pow(major_axis.y, 2));
        const float minor_length = major_length * ratio;
        const float rotation = std::atan2(major_axis.y, major_axis.x);

        const float pi = 3.14159f;
        const float span_angle = end - start;
        const float super_rough_approx_length = 0.5f * (major_length + minor_length) * span_angle;

        const int step_count = (int)std::ceil(super_rough_approx_length / step);
        const int point_count = step_count + 1;

        const float step_angle = span_angle / step_count;

        float angle = start;
        while (angle <= end)
        {
            Point new_point;
            new_point.x = major_length * std::cos(angle) * std::cos(rotation) - minor_length * std::sin(angle) * std::sin(rotation) + center.x;
            new_point.y = major_length * std::cos(angle) * std::sin(rotation) + minor_length * std::sin(angle) * std::cos(rotation) + center.y;
            points.push_back(new_point);
            angle += step_angle;
        }

        for (Point p : points)
        {
            std::cout << p.x << ", " << p.y << "\n";
        }
        std::cout << "\n";

        return points;
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
