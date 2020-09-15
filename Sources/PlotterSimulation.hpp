#ifndef PlotterSimulation_hpp
#define PlotterSimulation_hpp

#include <cmath>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class PlotterSimulation
{
public:
    virtual void update(float delta_time) = 0;
    virtual std::vector<sf::Drawable *> get_drawables() = 0;
    virtual bool is_finished() = 0;
};

class TwinArmPlotterSimulation : public PlotterSimulation
{
private:
    sf::RectangleShape m_upperarm_left,
        m_upperarm_right,
        m_forearm_left,
        m_forearm_right;

    std::vector<sf::CircleShape> m_drawing;

    float m_arm_rotation_left = 135.0f,
          m_arm_rotation_right = 45.0f,
          m_forearm_length,
          m_upperarm_lenght,
          m_shoulder_separation;

    float m_target_left = m_arm_rotation_left,
          m_target_right = m_arm_rotation_right;

    std::istringstream m_g_code;

    bool m_pen_down = false;
    bool m_is_finished = false;

    std::vector<float> get_new_targets();

public:
    TwinArmPlotterSimulation(std::string g_code, float shoulder_separation, float forearm_length, float upperarm_length);
    void update(float delta_time) override;
    std::vector<sf::Drawable *> get_drawables() override;
    bool is_finished() override;
};

#endif
