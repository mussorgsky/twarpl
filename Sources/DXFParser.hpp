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
        constexpr static std::array<GroupCode, 20> m_group_codes = {
            GroupCode::ENTITY_TYPE,
            GroupCode::HANDLE,
            GroupCode::CP_X,
            GroupCode::CP_Y,
            GroupCode::FP_X,
            GroupCode::FP_Y,
            GroupCode::RADIUS,
            GroupCode::KNOT_VALUE,
            GroupCode::SEMIMAJOR_AXIS_RATIO,
            GroupCode::ELLIPSE_START,
            GroupCode::ELLIPSE_END,
            GroupCode::KNOT_TOLERANCE,
            GroupCode::START_ANGLE,
            GroupCode::END_ANGLE,
            GroupCode::SPLINE_FLAG,
            GroupCode::SPLINE_DEGREE,
            GroupCode::KNOT_COUNT,
            GroupCode::CP_COUNT,
            GroupCode::VERTEX_COUNT,
        };

        static void remove_char(std::string &, std::string);

    public:
        static std::vector<std::shared_ptr<Entity>> parse(std::ifstream &file);
    };

} // namespace DXF

#endif
