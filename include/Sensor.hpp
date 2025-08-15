#pragma once
#include <string>
#include <chrono>
#include <utility>
#include <variant>
#include <vector>
#include "SensorConfig.hpp"
#include "Enum.hpp"

class Sensor
{
    private:
        SensorConfig& config;
        std::variant<double, int, bool> currentValue;
        bool flagState;
        std::chrono::system_clock::time_point lastUpdate;
        Status status;
        std::vector<std::variant<double, int, bool>>historyValue;
    public:
        Sensor(SensorConfig& config, std::variant<double, int, bool>currentValue, bool flagState,
        SensorType status);

        void UpdateValue();

        const std::variant<double, int, bool> GetCurrentValue();

        const std::vector<std::variant<double, int, bool> GetHistoryValue();

        const Status GetStatus();

        void SetStatus();


};

