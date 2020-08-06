#ifndef DXFParser_hpp
#define DXFParser_hpp

#include "DXFEntity.hpp"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>

class DXFParser
{
    std::ifstream &m_file;

    std::vector<std::shared_ptr<DXFEntity>> m_parsed_entities;

    std::string entities[5] = {
        "LINE",
        "ELLIPSE",
        "ARC",
        "CIRCLE",
        "SPLINE",
    };

    std::map<int, std::string> group_codes = {
        {0, "Entity type"},
        {10, "Control point X"},
        {20, "Control point Y"},
        {30, "Control point Z"},
        {11, "Fit point X"},
        {21, "Fit point Y"},
        {31, "Fit point Z"},
        {12, "Start tangent X"},
        {22, "Start tangent Y"},
        {32, "Start tangent Z"},
        {40, "Radius/Knot value"},
        {41, "Ellipse start"},
        {42, "Ellipse end/Knot tolerance"},
        {50, "Start angle"},
        {51, "End angle"},
        {70, "Spline flag"},
        {71, "Degree of spline curve"},
        {72, "Number of knots"},
        {73, "Number of control points"},
        {74, "Number of fit points"},
    };

    void remove_char(std::string &, std::string);

public:
    DXFParser(std::ifstream &file) : m_file(file)
    {
    }

    void parse();
};

#endif
