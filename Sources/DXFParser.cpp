#include "DXFParser.hpp"

void DXFParser::remove_char(std::string &line, std::string to_delete)
{
    for (char unwanted : to_delete)
    {
        line.erase(std::remove(line.begin(), line.end(), unwanted), line.end());
    }
}

void DXFParser::parse()
{
    bool in_entity = false;
    std::shared_ptr<DXFEntity> mid_parse_entity;
    while (!m_file.eof())
    {
        std::string line, value;
        int group_code;

        std::getline(m_file, line);
        std::getline(m_file, value);

        group_code = std::stoi(line);
        remove_char(value, " \r");

        if (group_code != 0 && in_entity)
        {
            auto code = group_codes.find(group_code);
            if (code != group_codes.end())
            {
                std::cout << "\t" << code->second << "\t" << value << "\n";
                if (mid_parse_entity)
                {
                    mid_parse_entity->insert_property(group_code, std::stof(value));
                }
            }
        }

        if (group_code == 0 && in_entity)
        {
            std::cout << "Exiting entity\n";
            in_entity = false;
            if (mid_parse_entity)
            {
                m_parsed_entities.push_back(mid_parse_entity);
                mid_parse_entity = nullptr;
            }
        }

        if (group_code == 0 && !in_entity)
        {
            bool we_care = false;
            for (std::string entity : entities)
            {
                if (value == entity)
                {
                    we_care = true;
                    break;
                }
            }
            if (we_care)
            {
                std::cout << "Entering entity:\t" << value << "\n";
                in_entity = true;
                if (value == "LINE")
                {
                    mid_parse_entity = std::make_shared<Line>();
                }
                if (value == "CIRCLE")
                {
                    mid_parse_entity = std::make_shared<Circle>();
                }
                if (value == "ARC")
                {
                    mid_parse_entity = std::make_shared<Arc>();
                }
                if (value == "ELLIPSE")
                {
                    mid_parse_entity = std::make_shared<Ellipse>();
                }
                if (value == "SPLINE")
                {
                    mid_parse_entity = std::make_shared<Spline>();
                }
            }
        }

        if (value == "EOF")
        {
            break;
        }
    }

    for (auto &ent : m_parsed_entities)
    {
        ent->bark();
    }
}
