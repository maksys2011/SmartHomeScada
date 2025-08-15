#include "SensorConfig.hpp"
using json = nlohmann::json;

SensorConfig::SensorConfig(const std::string& id, const std::string& name, int pollIntervalMs, 
    DeviceType type, int ioAddress, const std::string& unit, int timeoutMs, int ttlMs, int retries,
    int backoffMs)
    {
        this->id = id;
        this->name = name;
        this->pollIntervalMs = pollIntervalMs;
        this->type = type;
        this->ioAddress = ioAddress;
        this->unit = unit;
        this->timeoutMs = timeoutMs;
        this->ttlMs = ttlMs;
        this->retries = retries;
        this->backoffMs = backoffMs;
    }

void SensorConfig::fromJson(const json& file)
    {
        id = file.at("id").get<std::string>();
        name = file.at("name").get<std::string>();
        type = StringToDeviceType(file.at("type").get<std::string>());
        ioAddress = file.at("ioAddress").get<std::string>();
        unit = file.at("unit").get<std::string>();
        pollIntervalMs = file.at("pollIntervalMs").get<int>();
        timeoutMs = file.at("timeoutMs").get<int>();
        ttlMs = file.at("ttlMs").get<int>();    
        retries = file.at("retries").get<int>();
        backoffMs = file.at("backoffMs").get<int>();
        if(file.contains("minValue") && !file["minValue"].is_null())
            {
                minValue = file.at("minValue").get<double>();
            }else{
                minValue.reset();
            }

        if(file.contains("maxValue") && !file["maxValue"].is_null())
            {
                maxValue = file.at("maxValue").get<double>();
            }else{
                 maxValue.reset();
            }

        if(file.contains("deadband") && !file["deadband"].is_null())
            {
                deadband = file.at("deadband").get<double>();
            }else{
                 deadband.reset();
            }

        if(file.contains("pulsesPerUnit") && !file["pulsesPerUnit"].is_null())
            {
                pulsesPerUnit = file.at("pulsesPerUnit").get<int>();
            }else{
                pulsesPerUnit.reset();
            }

        if(file.contains("rolloverValue") && !file["rolloverValue"].is_null())
            {
                rolloverValue = file.at("rolloverValue").get<int>();
            }else{
                 rolloverValue.reset();
            }

        if(file.contains("debounceMs") && !file["debounceMs"].is_null())
            {
                debounceMs = file.at("debounceMs").get<int>();
            }else{
                debounceMs.reset();
            }

        if(file.contains("activeHigh") && !file["activeHigh"].is_null())
            {
                 activeHigh = file.at("activeHigh").get<bool>();
            }else{
                 activeHigh.reset();
            }
    } 

void SensorConfig::fromJson(const std::string& path)

    {
        std::ifstream file(path);
        if(!file)
        {
            throw std::runtime_error("Cannot open config file: " + path);
        }
        json j;
        file >> j;

        fromJson(j);
    }   

const void SensorConfig::printInfo()
{
    std::cout << "id: " << getId()<< std::endl;
    std::cout << "name: " << getName() << std::endl;
    std::cout << "type: " << DeviceTypeToString(getType()) << std::endl;

}

const std::string& SensorConfig::getId() const
{
    return id;
}
    
const std::string& SensorConfig::getName() const
{
    return name;
}

const DeviceType SensorConfig::getType() const
{
    return type;
}

std::optional<double> SensorConfig::getMinValue() const
{
    return minValue;
}

std::optional<double> SensorConfig::getMaxValue() const
{
    return maxValue;
}

void SensorConfig::setMinValue(double value)
{
    minValue = value;
}

void SensorConfig::setMaxValue(double value)
{
    maxValue = value;
}

void SensorConfig::setDeadband(double value)
{
    deadband = value;
} 

void SensorConfig::setDebounce(int value)
{
    debounceMs = value;
}

void SensorConfig::setPulsesPerUnit(int value)
{
    pulsesPerUnit = value;
}

void SensorConfig::setRolloverValue(int value)
{
    rolloverValue = value;
}

void SensorConfig::setActiveHigh(bool value)
{
    activeHigh = value;
}

void SensorConfig::validate()
{
        if(id.empty()) 
            {
                throw std::runtime_error("id must not be empty");
            }
        if(name.empty())
            {
                throw std::runtime_error("name must not be empty");   
            }
        if(ioAddress.empty())
            {
                throw std::runtime_error("ioAddress must not be empty");
            }
        if(unit.empty())
            {
                throw std::runtime_error("unit must not be empty");
            }
        if(pollIntervalMs <= 0)
            {
                throw std::runtime_error("pollIntervalMs must not be > 0");
            }
        if(timeoutMs < 0)
            {
                throw std::runtime_error("timeoutMs must not be >= 0");
            }
        if (ttlMs < 0)
            {
                throw std::runtime_error("ttlMs must not be >= 0");
            }
        if(retries < 0)
            {
                throw std::runtime_error("retries must not be >= 0");
            }
        if(backoffMs < 0)
            {
                throw std::runtime_error("backoffMs must not be >= 0");
            }

}


  




    