#include <iostream>
#include <fstream>
#include <string>
#include "Enum.hpp"
#include "EnumUtils.hpp"
#include "SensorConfig.hpp"
#include "ActuatorConfig.hpp"
#include "Actuator.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

int main()
{
    SensorConfig config;
        try{
                config.fromJson(std::string("C:\\cpp_project\\SmartHome\\SensorConfig.json"));
                config.validate();
                std::cout << "SensorConfig ok" << std::endl;
            }
            catch(const std::exception& e){
                std::cerr << "Config Error: " << e.what() << std::endl;
            }

        
    
    
    return 0;
}