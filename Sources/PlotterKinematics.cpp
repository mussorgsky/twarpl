#include "PlotterKinematics.hpp"

TwinArmPlotterKinematics::TwinArmPlotterKinematics(float shoulder_separation, float forearm_length, float upperarm_length)
    : m_shoulder_separation(shoulder_separation),
      m_forearm_length(forearm_length),
      m_upperarm_length(upperarm_length)
{
}

bool TwinArmPlotterKinematics::check_reachability(Point point)
{
    if (point.y < 0.0f)
        return false;

    if (distance_2d(point, {-m_shoulder_separation * 0.5f, 0.0f}) < m_upperarm_length)
        return false;

    if (distance_2d(point, {m_shoulder_separation * 0.5f, 0.0f}) < m_upperarm_length)
        return false;

    if (distance_2d(point, {-m_shoulder_separation * 0.5f, 0.0f}) > (m_forearm_length + m_upperarm_length))
        return false;

    if (distance_2d(point, {m_shoulder_separation * 0.5f, 0.0f}) > (m_forearm_length + m_upperarm_length))
        return false;

    return true;
}

// Adapted from http://ambrsoft.com/TrigoCalc/Circles2/circle2intersection/CircleCircleIntersection.htm
std::vector<float> TwinArmPlotterKinematics::inverse_kinematics(Point target)
{
    const float r0 = m_upperarm_length;
    const float r1 = m_forearm_length;
    const float a = target.x;
    const float b = target.y;
    const float d = 0.0f;

    std::vector<float> angles;

    int i = 0;
    for (float c : {-m_shoulder_separation * 0.5f, m_shoulder_separation * 0.5f})
    {
        const float D2 = std::pow(c - a, 2) + std::pow(d - b, 2);
        const float D = std::sqrt(D2);
        float area = 0.25f * std::sqrt((D + r0 + r1) * (D + r0 - r1) * (D - r0 + r1) * (-D + r0 + r1));

        const float x1 = (a + c) * 0.5f + (c - a) * (r0 * r0 - r1 * r1) / (2.0f * D2) + 2.0f * (b - d) * area / D2;
        const float x2 = (a + c) * 0.5f + (c - a) * (r0 * r0 - r1 * r1) / (2.0f * D2) - 2.0f * (b - d) * area / D2;

        const float y1 = (b + d) * 0.5f + (d - b) * (r0 * r0 - r1 * r1) / (2.0f * D2) - 2.0f * (a - c) * area / D2;
        const float y2 = (b + d) * 0.5f + (d - b) * (r0 * r0 - r1 * r1) / (2.0f * D2) + 2.0f * (a - c) * area / D2;

        if (i == 0)
        {
            angles.push_back(std::atan2(y2 - d, x2 - c));
        }
        if (i == 1)
        {
            angles.push_back(std::atan2(y1 - d, x1 - c));
        }

        i += 1;

        // std::cout << c << "\t" << d << "\t" << target.x << "\t" << target.y << "\t" << x1 << "\t" << y1 << "\t" << x2 << "\t" << y2 << "\t" << angles.back() << "\n";
    }

    return angles;
}

std::unique_ptr<PlotterSimulation> TwinArmPlotterKinematics::create_simulation(std::string g_code)
{
    return std::make_unique<TwinArmPlotterSimulation>(g_code, m_shoulder_separation, m_forearm_length, m_upperarm_length);
}
