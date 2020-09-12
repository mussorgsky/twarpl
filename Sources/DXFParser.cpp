#include "DXFParser.hpp"

namespace DXF
{
    void Parser::remove_char(std::string &line, std::string to_delete)
    {
        for (char unwanted : to_delete)
        {
            line.erase(std::remove(line.begin(), line.end(), unwanted), line.end());
        }
    }

    std::vector<std::shared_ptr<Entity>> Parser::parse(std::ifstream &file)
    {
        std::vector<std::shared_ptr<Entity>> parsed_entities;
        bool in_entity = false;
        std::shared_ptr<Entity> mid_parse_entity;
        while (!file.eof())
        {
            std::string line, value;
            GroupCode group_code;

            std::getline(file, line);
            std::getline(file, value);

            group_code = static_cast<GroupCode>(std::stoi(line));
            remove_char(value, " \r");

            if (group_code != GroupCode::ENTITY_TYPE && in_entity)
            {
                if (std::count(m_group_codes.begin(), m_group_codes.end(), group_code) > 0)
                {
                    if (mid_parse_entity)
                    {
                        if (group_code == GroupCode::HANDLE)
                        {
                            mid_parse_entity->set_handle(std::stoi(value, 0, 16));
                        }
                        else
                        {
                            mid_parse_entity->insert_property(group_code, std::stof(value));
                        }
                    }
                }
            }

            if (group_code == GroupCode::ENTITY_TYPE && in_entity)
            {
                in_entity = false;
                if (mid_parse_entity)
                {
                    parsed_entities.push_back(mid_parse_entity);
                    mid_parse_entity = nullptr;
                }
            }

            if (group_code == GroupCode::ENTITY_TYPE && !in_entity)
            {
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
                if (value == "LWPOLYLINE")
                {
                    mid_parse_entity = std::make_shared<LWPolyline>();
                }
            }

            if (value == "EOF")
            {
                break;
            }
        }

        return parsed_entities;
    }

} // namespace DXF
