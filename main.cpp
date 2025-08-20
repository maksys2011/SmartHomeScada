#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Enum.hpp"
#include "EnumUtils.hpp"
#include "SensorConfig.hpp"
#include "ActuatorConfig.hpp"
#include "Actuator.hpp"
#include "nlohmann/json.hpp"
#include "SensorState.hpp"
using json = nlohmann::json;

int main()
{
    setlocale(LC_ALL, "ru");
    std::vector<double>test{25, 40, 79, 80, 85, 89, 90, 95};
    std::string file = "C:\\cpp_project\\SmartHome\\SensorConfig.json";
    SensorConfig cfg;
    cfg.fromJson(file);
    SensorState st(cfg);
    auto ts = std::chrono::system_clock::now();
    for(double it : test)
    {
        st.updateValue(it, true);
        std::cout << "value: " <<it << ": ";
        st.printInfoState();
    }

    return 0;
}