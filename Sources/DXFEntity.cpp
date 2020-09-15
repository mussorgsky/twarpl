#include "DXFEntity.hpp"

namespace DXF
{
    void Entity::set_handle(int name)
    {
        handle = name;
    }

    int Entity::get_handle()
    {
        return handle;
    }

    void Entity::append_points_from_line(std::vector<Point> &points, Point start, Point end, float step)
    {
        float length = std::sqrt(std::pow(end.x - start.x, 2) + std::pow(end.y - start.y, 2));

        int step_count = (int)std::ceil(length / step);
        int point_count = step_count + 1;

        Point step_vector{(end.x - start.x) / step_count, (end.y - start.y) / step_count};

        points.push_back(start);
        for (int j = 0; j < step_count; ++j)
        {
            Point new_point;
            new_point.x = points.back().x + step_vector.x;
            new_point.y = points.back().y + step_vector.y;
            points.push_back(new_point);
        }
    }

    void Line::insert_property(GroupCode code, float value)
    {
        switch (code)
        {
        case GroupCode::CP_X:
            start.x = value;
            break;

        case GroupCode::CP_Y:
            start.y = value;
            break;

        case GroupCode::FP_X:
            end.x = value;
            break;

        case GroupCode::FP_Y:
            end.y = value;
            break;

        default:
            break;
        }
    }

    std::vector<Point> Line::make_points(float step)
    {
        std::vector<Point> points;
        append_points_from_line(points, start, end, step);

        return points;
    }

    void Circle::insert_property(GroupCode code, float value)
    {
        switch (code)
        {
        case GroupCode::CP_X:
            center.x = value;
            break;

        case GroupCode::CP_Y:
            center.y = value;
            break;

        case GroupCode::RADIUS:
            radius = value;
            break;

        default:
            break;
        }
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

        return points;
    }

    void Arc::insert_property(GroupCode code, float value)
    {
        switch (code)
        {
        case GroupCode::CP_X:
            center.x = value;
            break;

        case GroupCode::CP_Y:
            center.y = value;
            break;

        case GroupCode::RADIUS:
            radius = value;
            break;

        case GroupCode::START_ANGLE:
            start = value;
            break;

        case GroupCode::END_ANGLE:
            end = value;
            break;

        default:
            break;
        }
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

        return points;
    }

    void Ellipse::insert_property(GroupCode code, float value)
    {
        switch (code)
        {
        case GroupCode::CP_X:
            center.x = value;
            break;

        case GroupCode::CP_Y:
            center.y = value;
            break;

        case GroupCode::FP_X:
            major_axis.x = value;
            break;

        case GroupCode::FP_Y:
            major_axis.y = value;
            break;

        case GroupCode::SEMIMAJOR_AXIS_RATIO:
            ratio = value;
            break;

        case GroupCode::ELLIPSE_START:
            start = value;
            break;

        case GroupCode::ELLIPSE_END:
            end = value;
            break;

        default:
            break;
        }
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

        return points;
    }

    void Spline::insert_property(GroupCode code, float value)
    {
        switch (code)
        {
        case GroupCode::CP_X:
            cps.push_back(Point{value, 0.0f});
            weights.push_back(1.0f);
            break;

        case GroupCode::CP_Y:
            cps.back().y = value;
            break;

        case GroupCode::KNOT_VALUE:
            knots.push_back(value);
            break;

        case GroupCode::KNOT_TOLERANCE:
            knot_tolerance = value;
            break;

        case GroupCode::SPLINE_FLAG:
            flags = (int)value;
            break;

        case GroupCode::SPLINE_DEGREE:
            degree = (int)value;
            break;

        case GroupCode::KNOT_COUNT:
            knots.reserve((int)value);
            break;

        case GroupCode::CP_COUNT:
            cps.reserve((int)value);
            break;

        case GroupCode::WEIGHT:
            weights.back() = value;
            break;

        default:
            break;
        }
    }

    std::vector<Point> Spline::make_points(float step)
    {
        std::vector<Point> points;

        float rough_approx_length = 0.0f;
        Point last_cp = cps[0];
        for (int i = 1; i < cps.size(); ++i)
        {
            Point cp = cps[i];
            rough_approx_length += std::sqrt(std::pow(cp.x - last_cp.x, 2) + std::pow(cp.y - last_cp.y, 2));
            last_cp = cp;
        }

        if (flags && Mask::CLOSED)
        {
            rough_approx_length += std::sqrt(std::pow(cps[0].x - last_cp.x, 2) + std::pow(cps[0].y - last_cp.y, 2));
        }

        const int step_count = (int)std::ceil(rough_approx_length / step);
        const int point_count = step_count + 1;
        const float min_parameter = knots.front();
        const float max_parameter = knots.back();
        const float parameter_step = (max_parameter - min_parameter) / step_count;

        points.reserve(point_count);

        for (float parameter = min_parameter; parameter < max_parameter; parameter += parameter_step)
        {
            Point numerator{0.0f, 0.0f};
            Point denominator{0.0f, 0.0f};
            for (int i = 0; i < cps.size(); ++i)
            {
                float basis = normalized_b_spline_basis(i, degree, parameter);
                Point cp = cps[i];
                float weight = weights[i];

                numerator.x += weight * cp.x * basis;
                denominator.x += weight * basis;

                numerator.y += weight * cp.y * basis;
                denominator.y += weight * basis;
            }
            points.push_back(Point{numerator.x / denominator.x, numerator.y / denominator.y});
        }

        return points;
    }

    float Spline::normalized_b_spline_basis(int i, int k, float u)
    {
        if (k == 0)
        {
            return (u >= knots[i] && u < knots[i + 1]) ? 1.0f : 0.0f;
        }

        float num_a = (u - knots[i]);
        float den_a = (knots[i + k] - knots[i]);
        float a = (num_a == 0.0f || den_a == 0.0f) ? 0.0f : num_a / den_a;

        float num_b = (knots[i + k + 1] - u);
        float den_b = (knots[i + k + 1] - knots[i + 1]);
        float b = (num_b == 0.0f || den_b == 0.0f) ? 0.0f : num_b / den_b;

        return a * normalized_b_spline_basis(i, k - 1, u) + b * normalized_b_spline_basis(i + 1, k - 1, u);
    }

    void LWPolyline::insert_property(GroupCode code, float value)
    {
        switch (code)
        {
        case GroupCode::VERTEX_COUNT:
            vertices.reserve((int)value);
            break;

        case GroupCode::CP_X:
            vertices.push_back(Point{value, 0.0f});
            break;

        case GroupCode::CP_Y:
            vertices.back().y = value;

        default:
            break;
        }
    }

    std::vector<Point> LWPolyline::make_points(float step)
    {
        std::vector<Point> points;

        if (vertices.size() < 2)
        {
            return points;
        }

        Point start, end;
        for (int i = 1; i < vertices.size(); ++i)
        {
            start = vertices[i - 1];
            end = vertices[i];

            append_points_from_line(points, start, end, step);
        }

        return points;
    }

} // namespace DXF
