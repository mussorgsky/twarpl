#ifndef DXFEntity_hpp
#define DXFEntity_hpp

#include <iostream>
#include <vector>

namespace DXF
{
    enum Codes
    {
        ENTITY_TYPE = 0,
        CP_X = 10,
        CP_Y = 20,
        FP_X = 11,
        FP_Y = 21,
        RADIUS = 40,
        KNOT_VALUE = 40,
        SEMIMAJOR_AXIS_RATIO = 40,
        ELLIPSE_START = 41,
        ELLIPSE_END = 42,
        KNOT_TOLERANCE = 42,
        START_ANGLE = 50,
        END_ANGLE = 51,
        SPLINE_FLAG = 70,
        SPLINE_DEGREE = 71,
        KNOT_COUNT = 72,
        CP_COUNT = 73,
    };

    class Entity
    {
    public:
        virtual void insert_property(int group_code, float value) = 0;
        virtual void bark() = 0;
    };

    class Line : public Entity
    {
    public:
        void insert_property(int group_code, float value) override;
        void bark() override;

    private:
        float start_x, start_y, end_x, end_y;
    };

    class Circle : public Entity
    {
    public:
        void insert_property(int group_code, float value) override;
        void bark() override;

    private:
        float center_x, center_y, radius;
    };

    class Arc : public Entity
    {
    public:
        void insert_property(int group_code, float value) override;
        void bark() override;

    private:
        float center_x, center_y, radius, start, end;
    };

    class Ellipse : public Entity
    {
    public:
        void insert_property(int group_code, float value) override;
        void bark() override;

    private:
        float center_x, center_y, major_x, major_y, ratio, start, end;
    };

    class Spline : public Entity
    {
    public:
        void insert_property(int group_code, float value) override;
        void bark() override;

    private:
        int flags, degree, knot_count, cp_count;
        float knot_tolerance;
        std::vector<float> knots, x, y;
    };

} // namespace DXF

#endif
