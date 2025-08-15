#include "ActuatorConfig.hpp"
#include "EnumUtils.hpp"
using json = nlohmann::json;

void ActuatorConfig::fromJson(const nlohmann::json& j)
{
    id = j.at("id").get<std::string>();
    name = j.at("name").get<std::string>();
    type = StringToActuatorType(j.at("type").get<std::string>());
    ioAddress = j.at("ioAddress").get<std::string>();
    if(j.contains("unit") && !j["unit"].is_null())
    {
        unit = j.at("unit").get<std::string>();
    }else{
        unit.reset();
    }
    if(j.contains("activeHigh") && !j["activeHigh"].is_null())
    {
        if(j["activeHigh"].is_boolean()){
            activeHigh = j.at("activeHigh").get<bool>();
        }else if (j["activeHigh"].is_number_integer()){
            activeHigh = (j.at("activeHigh").get<int>() != 0);
        }else{
            throw std::runtime_error("activeHigh must be boolean or 0/1");
        }
    }else{
        activeHigh.reset();
    }

    if(j.contains("description") && !j["description"].is_null())
    {
        description = j.at("description").get<std::string>();
    }else{
        description.reset();
    }
}

void ActuatorConfig::fromJson(const std::string& path)
{
    std::ifstream f(path);

    if(!f)
    {
        throw std::runtime_error("Cannot open file: " + path);
    }
    json j;
    f >> j;
    fromJson(j);
}

void ActuatorConfig::validate() const
{
    if(id.empty()) throw std::runtime_error("id must not be empty");
    if(name.empty()) throw std::runtime_error("name must not be empty");
    if(ioAddress.empty()) throw std::runtime_error("ioAddress must not be empty");
}

const std::string& ActuatorConfig::getId() const
{
    return id;
}

const std::string& ActuatorConfig::getName() const
{
    return name;
}