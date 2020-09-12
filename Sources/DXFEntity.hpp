#ifndef DXFEntity_hpp
#define DXFEntity_hpp

#include <cmath>
#include <iostream>
#include <vector>

namespace DXF
{
    enum class GroupCode
    {
        ENTITY_TYPE = 0,
        HANDLE = 5,
        CP_X = 10,
        CP_Y = 20,
        FP_X = 11,
        FP_Y = 21,
        RADIUS = 40,
        KNOT_VALUE = 40,
        SEMIMAJOR_AXIS_RATIO = 40,
        WEIGHT = 41,
        ELLIPSE_START = 41,
        ELLIPSE_END = 42,
        KNOT_TOLERANCE = 42,
        START_ANGLE = 50,
        END_ANGLE = 51,
        SPLINE_FLAG = 70,
        SPLINE_DEGREE = 71,
        KNOT_COUNT = 72,
        CP_COUNT = 73,
        VERTEX_COUNT = 90,
    };

    struct Point
    {
        float x, y;
    };

    class Entity
    {
    protected:
        int handle;

    public:
        virtual void insert_property(GroupCode code, float value) = 0;
        virtual void bark() = 0;
        virtual std::vector<Point> make_points(float step = 1.0f) = 0;
        void set_handle(int name);
        int get_handle();
        void append_points_from_line(std::vector<Point> &points, Point start, Point end, float step);
    };

    class Line : public Entity
    {
    public:
        void insert_property(GroupCode code, float value) override;
        void bark() override;
        std::vector<Point> make_points(float step) override;

    private:
        Point start, end;
    };

    class Circle : public Entity
    {
    public:
        void insert_property(GroupCode code, float value) override;
        void bark() override;
        std::vector<Point> make_points(float step) override;

    private:
        Point center;
        float radius;
    };

    class Arc : public Entity
    {
    public:
        void insert_property(GroupCode code, float value) override;
        void bark() override;
        std::vector<Point> make_points(float step) override;

    private:
        Point center;
        float radius, start, end;
    };

    class Ellipse : public Entity
    {
    public:
        void insert_property(GroupCode code, float value) override;
        void bark() override;
        std::vector<Point> make_points(float step) override;

    private:
        Point center, major_axis;
        float ratio, start, end;
    };

    class Spline : public Entity
    {
    public:
        void insert_property(GroupCode code, float value) override;
        void bark() override;
        std::vector<Point> make_points(float step) override;

    private:
        enum Mask
        {
            CLOSED = 1,
            PERIODIC = 2,
            RATIONAL = 4,
            PLANAR = 8,
            LINEAR = 16,
        };
        int flags, degree;
        float knot_tolerance;
        std::vector<float> knots, weights;
        std::vector<Point> cps;
        float normalized_b_spline_basis(int i, int k, float u);
    };

    class LWPolyline : public Entity
    {
    public:
        void insert_property(GroupCode code, float value) override;
        void bark() override;
        std::vector<Point> make_points(float step) override;

    private:
        std::vector<Point> vertices;
    };

} // namespace DXF

#endif
