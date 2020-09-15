#include <fstream>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "DXFParser.hpp"
#include "PlotterKinematics.hpp"

int main(int argc, char *argv[])
{
    std::string in_file_name, out_file_name;
    bool show_visualization = false;

    // We need an input file and an output file
    if (argc == 1)
    {
        std::cout << "Input (.dxf) file path: ";
        std::cin >> in_file_name;

        std::cout << "Output (.gcode) file path: ";
        std::cin >> out_file_name;
    }
    else if (argc == 3)
    {
        in_file_name = argv[1];
        out_file_name = argv[2];
    }
    else if (argc == 4)
    {
        std::string option = argv[1];
        if (option == "-v" || option == "--visualize")
        {
            in_file_name = argv[2];
            out_file_name = argv[3];
            show_visualization = true;
        }
        else
        {
            std::cout << "Valid options are '-v' or '--visualize' to show visualization.\n";
            return 1;
        }
    }
    else
    {
        std::cout << "Run this program with no arguments for interactive mode.\n";
        return 1;
    }

    // We open both files at the start so we don't do work and then fail at opening the output file
    std::ifstream in_file;
    in_file.open(in_file_name, std::ios::in);
    if (!in_file.good())
    {
        std::cout << "Couldn't open input file.\n";
        return 1;
    }

    std::ofstream out_file;
    out_file.open(out_file_name, std::ios::out | std::ios::trunc);
    if (!out_file.good())
    {
        std::cout << "Couldn't open output file.\n";
        return 1;
    }

    std::vector<std::shared_ptr<DXF::Entity>> entities;
    try
    {
        entities = DXF::Parser::parse(in_file);
    }
    catch (...)
    {
        std::cout << "Couldn't parse input file. Please check if it's a valid DXF file.\n";
        return 1;
    }
    in_file.close();
    if (entities.size() == 0)
    {
        std::cout << "Couldn't parse any DXF entities.\n";
        return 1;
    }

    int reachable_count = 0,
        uncheachable_count = 0;
    bool pen_down = true;

    std::string g_code = "G28\n";
    std::unique_ptr<PlotterKinematics> kinematics = std::make_unique<TwinArmPlotterKinematics>(50.0f, 150.0f, 150.0f);
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
            if (kinematics->check_reachability(point))
            {
                g_code += "G00";
                int i = 0;
                const char *rotational_g_code = "ABC";
                for (float angle : kinematics->inverse_kinematics(point))
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
                uncheachable_count += 1;
            }
        }
        g_code += "F0\n";
    }
    g_code += "G28\nM02\n";
    out_file << g_code;
    out_file.close();

    std::cout << "Gcode file created (" << out_file_name << ").\n";

    if (uncheachable_count > 0)
    {
        std::cout << "Out of " << reachable_count + uncheachable_count << " points, "
                  << uncheachable_count << " are unreachable and ignored. ("
                  << 100 * uncheachable_count / (reachable_count + uncheachable_count) << "%)\n";
    }
    else
    {
        std::cout << "All " << reachable_count << " points are reachable.\n";
    }

    if (argc == 1)
    {
        std::cout << "Show visualization of the plotter's movement? (y/n): ";
        std::string visualization_answer;
        std::cin >> visualization_answer;
        if (visualization_answer == "yes" || visualization_answer == "y" || visualization_answer == "Y")
        {
            show_visualization = true;
        }
        else
        {
            show_visualization = false;
        }
    }

    if (show_visualization)
    {
        std::cout << "Opening visualization window.\n";

        sf::ContextSettings settings;
        settings.antialiasingLevel = 2;
        sf::RenderWindow window(sf::VideoMode(800, 600), "Plotter Visualization", sf::Style::Default, settings);
        window.setFramerateLimit(60);

        sf::Clock delta_clock;
        sf::View camera = sf::View(sf::Vector2f(0.0f, 160.0f), sf::Vector2f(480.0f, -360.0f));
        window.setView(camera);

        std::unique_ptr<PlotterSimulation> simulation = kinematics->create_simulation(g_code);

        while (window.isOpen() && !simulation->is_finished())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
            }

            window.clear();

            float delta_time = delta_clock.restart().asSeconds();
            simulation->update(delta_time);

            for (auto drawable : simulation->get_drawables())
            {
                window.draw(*drawable);
            }

            window.display();
        }

        std::cout << "Visualization finished, exiting.\n";
    }
}
