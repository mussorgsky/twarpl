#include "GCodeGenerator.hpp"

std::string GCodeGenerator::generate(std::vector<std::shared_ptr<DXF::Entity>> &entities,
                                     PlotterKinematics &kinematics,
                                     int &reachable_count,
                                     int &unreachable_count)
{
    reachable_count = 0;
    unreachable_count = 0;
    bool pen_down = true;

    std::string g_code = "G28\n";
    for (auto entity : entities)
    {
        if (pen_down)
        {
            g_code += "F0\n";
            pen_down = false;
        }
        bool first = true;
        for (auto point : entity->make_points(1.0f))
        {
            if (kinematics.check_reachability(point))
            {
                g_code += "G00";
                int i = 0;
                const char *rotational_g_code = "ABC";
                for (float angle : kinematics.inverse_kinematics(point))
                {
                    g_code += " ";
                    g_code += rotational_g_code[i++];
                    g_code += " ";
                    g_code += std::to_string(angle);
                }
                g_code += "\n";
                reachable_count += 1;

                if (first)
                {
                    if (!pen_down)
                    {
                        g_code += "F1\n";
                        pen_down = true;
                    }
                    first = false;
                }
            }
            else
            {
                if (pen_down)
                {
                    g_code += "F0\n";
                    pen_down = false;
                }
                first = true;
                unreachable_count += 1;
            }
        }
        g_code += "F0\n";
    }
    g_code += "G28\nM02\n";
    return g_code;
}
