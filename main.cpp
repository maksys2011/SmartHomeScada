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
    ActuatorConfig config;
        try{
                config.fromJson(std::string("C:\\cpp_project\\SmartHome\\ActuatorConfig.json"));
                config.Validate();
                std::cout << "ActuatorConfig ok" << std::endl;
            }
            catch(const std::exception& e){
                std::cerr << "Config Error" << e.what() << std::endl;
            }
    Actuator obj(config, false);
    obj.PrintInfo();
        
    
    
    return 0;
}