#include "Actuator.hpp"

Actuator::Actuator(ActuatorConfig config, bool initial)
    :config(std::move(config)), 
    state(initial),
    lastCmd(std::chrono::system_clock::now())
{}

void Actuator::TurnOn()
{
    state = true;
    lastCmd = std::chrono::system_clock::now();
}

void Actuator::TurnOff()
{
    state = false;
    lastCmd = std::chrono::system_clock::now();
}

bool Actuator::getState() const
{
    return state;
}

void Actuator::PrintInfo() const
{
    std::cout << "id actuator: " << config.getId() << "\n";
    std::cout << "name actuator: " << config.getName() << "\n";
    std::cout << "state actuator: " << getState() << "\n";
}