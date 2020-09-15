#include <fstream>
#include <iostream>

#include "DXFParser.hpp"

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
}
