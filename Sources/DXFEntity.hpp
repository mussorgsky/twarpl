#ifndef DXFEntity_hpp
#define DXFEntity_hpp

#include <iostream>

class DXFEntity
{
public:
    virtual void insert_property(int group_code, float value) = 0;
    virtual void bark() = 0;
};

class Line : public DXFEntity
{
public:
    void insert_property(int group_code, float value) override;
    void bark() override;

private:
    float x1, y1, x2, y2;
};

class Circle : public DXFEntity
{
public:
    void insert_property(int group_code, float value) override;
    void bark() override;

private:
    float x, y, r;
};

class Arc : public DXFEntity
{
public:
    void insert_property(int group_code, float value) override;
    void bark() override;

private:
    float x, y, r, start, end;
};

class Ellipse : public DXFEntity
{
public:
    void insert_property(int group_code, float value) override;
    void bark() override;

private:
    float center_x, center_y, major_x, major_y, ratio, start, end;
};

#endif
