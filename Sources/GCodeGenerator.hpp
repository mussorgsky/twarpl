#ifndef GCodeGenerator_hpp
#define GCodeGenerator_hpp

#include <fstream>
#include "PlotterKinematics.hpp"

class GCodeGenerator
{
public:
    static std::string generate(std::vector<std::shared_ptr<DXF::Entity>> &entities,
                                PlotterKinematics &kinematics,
                                int &reachable_count,
                                int &unreachable_count);
};

#endif
