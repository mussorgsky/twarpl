#ifndef PlotterKinematics_hpp
#define PlotterKinematics_hpp

#include "DXFEntity.hpp"
#include "PlotterSimulation.hpp"

using DXF::Point;

#include <cmath>
#include <string>
#include <vector>

class PlotterKinematics
{
public:
    virtual bool check_reachability(Point point) = 0;
    virtual std::vector<float> inverse_kinematics(Point target) = 0;
    virtual std::unique_ptr<PlotterSimulation> create_simulation(std::string g_code) = 0;
};

class TwinArmPlotterKinematics : public PlotterKinematics
{
private:
    float m_shoulder_separation,
        m_forearm_length,
        m_upperarm_length;

public:
    TwinArmPlotterKinematics(float shoulder_separation, float forearm_length, float upperarm_length);
    bool check_reachability(Point point) override;
    std::vector<float> inverse_kinematics(Point target) override;
    std::unique_ptr<PlotterSimulation> create_simulation(std::string g_code) override;
};

#endif
