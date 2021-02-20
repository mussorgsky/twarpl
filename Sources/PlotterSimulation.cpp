#include "PlotterSimulation.hpp"

TwinArmPlotterSimulation::TwinArmPlotterSimulation(std::string g_code, float shoulder_separation, float forearm_length, float upperarm_length)
    : m_shoulder_separation(shoulder_separation),
      m_forearm_length(forearm_length),
      m_upperarm_lenght(upperarm_length)
{
    m_g_code = std::istringstream(g_code);

    m_upperarm_left = sf::RectangleShape(sf::Vector2f(m_upperarm_lenght, 2.0f));
    m_upperarm_left.setOrigin(0.0f, 1.0f);
    m_upperarm_left.setPosition(-m_shoulder_separation * 0.5f, 0.0f);
    m_upperarm_left.setFillColor(sf::Color::White);

    m_upperarm_right = sf::RectangleShape(sf::Vector2f(m_upperarm_lenght, 2.0f));
    m_upperarm_right.setOrigin(0.0f, 1.0f);
    m_upperarm_right.setPosition(m_shoulder_separation * 0.5f, 0.0f);
    m_upperarm_right.setFillColor(sf::Color::White);

    m_forearm_left = sf::RectangleShape(sf::Vector2f(m_forearm_length, 2.0f));
    m_forearm_left.setOrigin(0.0f, 1.0f);
    m_forearm_left.setPosition(-m_shoulder_separation * 0.5f, 0.0f);
    m_forearm_left.setFillColor(sf::Color::White);

    m_forearm_right = sf::RectangleShape(sf::Vector2f(m_forearm_length, 2.0f));
    m_forearm_right.setOrigin(0.0f, 1.0f);
    m_forearm_right.setPosition(m_shoulder_separation * 0.5f, 0.0f);
    m_forearm_right.setFillColor(sf::Color::White);
}

void TwinArmPlotterSimulation::update(float delta_time)
{
    float speed = 15.0f;

    float difference_left = m_target_left - m_arm_rotation_left;
    float difference_right = m_target_right - m_arm_rotation_right;

    if (difference_left > 0.0f)
    {
        m_arm_rotation_left += (difference_left < speed * delta_time) ? difference_left : speed * delta_time;
    }
    else if (difference_left < 0.0f)
    {
        m_arm_rotation_left += (difference_left > speed * delta_time) ? -difference_left : -speed * delta_time;
    }

    if (difference_right > 0.0f)
    {
        m_arm_rotation_right += (difference_right < speed * delta_time) ? difference_right : speed * delta_time;
    }
    else if (difference_right < 0.0f)
    {
        m_arm_rotation_right += (difference_right > speed * delta_time) ? -difference_right : -speed * delta_time;
    }

    if (std::abs(difference_left) < 0.001f && std::abs(difference_right) < 0.001f)
    {
        std::vector<float> new_targets = get_new_targets();
        m_target_left = new_targets[0];
        m_target_right = new_targets[1];
    }

    m_upperarm_left.setRotation(m_arm_rotation_left);
    m_upperarm_right.setRotation(m_arm_rotation_right);

    sf::Vector2f elbow_left = m_upperarm_left.getPosition() + sf::Vector2f(m_upperarm_lenght * std::cos(m_arm_rotation_left * 0.01745f), m_upperarm_lenght * std::sin(m_arm_rotation_left * 0.01745f));
    sf::Vector2f elbow_right = m_upperarm_right.getPosition() + sf::Vector2f(m_upperarm_lenght * std::cos(m_arm_rotation_right * 0.01745f), m_upperarm_lenght * std::sin(m_arm_rotation_right * 0.01745f));

    m_forearm_left.setPosition(elbow_left);
    m_forearm_right.setPosition(elbow_right);

    const float r = m_forearm_length;
    const float a = elbow_left.x;
    const float b = elbow_left.y;
    const float c = elbow_right.x;
    const float d = elbow_right.y;

    const float D2 = std::pow(c - a, 2) + std::pow(d - b, 2);
    const float D = std::sqrt(D2);
    float area = 0.25f * std::sqrt((D + r + r) * (D + r - r) * (D - r + r) * (-D + r + r));

    const float x1 = (a + c) * 0.5f + 2.0f * (b - d) * area / D2;
    const float x2 = (a + c) * 0.5f - 2.0f * (b - d) * area / D2;

    const float y1 = (b + d) * 0.5f - 2.0f * (a - c) * area / D2;
    const float y2 = (b + d) * 0.5f + 2.0f * (a - c) * area / D2;

    m_forearm_left.setRotation(std::atan2(y1 - elbow_left.y, x1 - elbow_left.x) * 57.2958f);
    m_forearm_right.setRotation(std::atan2(y1 - elbow_right.y, x1 - elbow_right.x) * 57.2958f);

    sf::Vector2f pen_position = elbow_left + sf::Vector2f(m_forearm_length * std::cos(m_forearm_left.getRotation() * 0.01745f), m_forearm_length * std::sin(m_forearm_left.getRotation() * 0.01745f));

    if (m_pen_down)
    {
        m_drawing.push_back(sf::CircleShape(1.0f, 4));
        m_drawing.back().setOrigin(0.5f, 0.5f);
        m_drawing.back().setPosition(pen_position);
        m_drawing.back().setFillColor(sf::Color::Green);
    }
}

std::vector<sf::Drawable *> TwinArmPlotterSimulation::get_drawables()
{
    std::vector<sf::Drawable *> drawables = {};
    for (auto &c : m_drawing)
    {
        drawables.push_back((sf::Drawable *)&c);
    }
    drawables.push_back((sf::Drawable *)&m_upperarm_left);
    drawables.push_back((sf::Drawable *)&m_upperarm_right);
    drawables.push_back((sf::Drawable *)&m_forearm_left);
    drawables.push_back((sf::Drawable *)&m_forearm_right);

    return drawables;
}

std::vector<float> TwinArmPlotterSimulation::get_new_targets()
{
    std::string line;
    if (std::getline(m_g_code, line))
    {

        if (line == "G28")
        {
            return {135.0f, 45.0f};
        }
        else if (line == "F0")
        {
            m_pen_down = false;
        }
        else if (line == "F1")
        {
            m_pen_down = true;
        }
        else if (line == "M02")
        {
            m_is_finished = true;
        }
        else
        {
            float a, b;
            size_t where_a, where_b;
            where_a = line.find("A ");
            where_b = line.find("B ");

            if (where_a != std::string::npos && where_b != std::string::npos)
            {

                a = std::stof(line.substr(where_a + 2, where_b - where_a - 4));
                b = std::stof(line.substr(where_b + 2));

                return {a * 57.2958f, b * 57.2958f};
            }
        }
    }

    return {m_target_left, m_target_right};
}

bool TwinArmPlotterSimulation::is_finished()
{
    return m_is_finished;
}
