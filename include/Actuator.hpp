#pragma once
#include <string>
#include <chrono>
#include <utility>
#include "ActuatorConfig.hpp"

class Actuator
{
    private:

    ActuatorConfig config;                                      // конфигурации
    bool state{false};                                          // текущее состояние
    std::chrono::system_clock::time_point lastCmd;              // время последней команды 

    public:
    
    Actuator(ActuatorConfig config, bool initial);

    void TurnOn();

    void TurnOff();

    bool getState() const;

    void PrintInfo() const ;


};