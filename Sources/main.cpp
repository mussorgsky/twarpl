#include <fstream>
#include <iostream>

#include "DXFParser.hpp"

int main(int argc, char *argv[])
{
    // We need an input file and an output file
    if (argc != 3)
    {
        std::cout << "Usage: twarpl input_file output_file\n";
        return 1;
    }

    // We open both files at the start so we don't do work and then fail at opening the output file
    std::ifstream in_file;
    in_file.open(argv[1], std::ios::in);
    if (!in_file.good())
    {
        std::cout << "Couldn't open input file.\n";
        return 1;
    }

    std::ofstream out_file;
    out_file.open(argv[2], std::ios::out | std::ios::trunc);
    if (!out_file.good())
    {
        std::cout << "Couldn't open output file.\n";
        return 1;
    }

    std::vector<std::shared_ptr<DXF::Entity>> entities = DXF::Parser::parse(in_file);
    in_file.close();
    if (entities.size() == 0)
    {
        std::cout << "Couldn't parse any DXF entities.\n";
        return 1;
    }
}
