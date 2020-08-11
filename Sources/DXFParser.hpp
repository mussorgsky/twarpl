#ifndef DXFParser_hpp
#define DXFParser_hpp

#include "DXFEntity.hpp"

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

namespace DXF
{
    class Parser
    {
        std::ifstream &m_file;

        std::vector<std::shared_ptr<Entity>> m_parsed_entities;

        std::array<Codes, 19> m_group_codes = {
            ENTITY_TYPE,
            HANDLE,
            CP_X,
            CP_Y,
            FP_X,
            FP_Y,
            RADIUS,
            KNOT_VALUE,
            SEMIMAJOR_AXIS_RATIO,
            ELLIPSE_START,
            ELLIPSE_END,
            KNOT_TOLERANCE,
            START_ANGLE,
            END_ANGLE,
            SPLINE_FLAG,
            SPLINE_DEGREE,
            KNOT_COUNT,
            CP_COUNT,
        };

        void remove_char(std::string &, std::string);

    public:
        Parser(std::ifstream &file) : m_file(file)
        {
        }

        void parse();
    };

} // namespace DXF

#endif
