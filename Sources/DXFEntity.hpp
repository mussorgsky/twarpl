#ifndef DXFEntity_hpp
#define DXFEntity_hpp

#include <iostream>
#include <vector>

namespace DXF
{
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
