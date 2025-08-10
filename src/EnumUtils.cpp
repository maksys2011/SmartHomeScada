#include <iostream> 
#include "EnumUtils.hpp"


std::string DeviceTypeToString(DeviceType type)
{
    switch (type)
    {
    case DeviceType::MotionSensor: return "MotionSensor";
    case DeviceType::LightSensor: return "LightSensor";
    case DeviceType::TemperatureSensor: return "TemperatureSensor";
    case DeviceType::WaterPresenceSensor: return "WaterPresenceSensor";
    case DeviceType::AirHumiditySensor: return "AirHumiditySensor";
    case DeviceType::SmokeSensor: return "SmokeSensor";
    case DeviceType::OtherSensors: return "OtherSensors";
    case DeviceType::ElectricSwitch: return "ElectricSwitch";
    case DeviceType::VideoCameras: return "VideoCameras";
    case DeviceType::SmartLocks: return "SmartLocks";
    case DeviceType::OtherDevice: return "OtherDevice";
    default:return " ";
    }
}

DeviceType StringToDeviceType(const std::string& str)
{
    if(str == "MotionSensor") return DeviceType::MotionSensor;
    else if(str == "LightSensor") return DeviceType::LightSensor;
    else if(str == "TemperatureSensor") return DeviceType::TemperatureSensor;
    else if(str == "WaterPresenceSensor") return DeviceType::WaterPresenceSensor;
    else if(str == "AirHumiditySensor") return DeviceType::AirHumiditySensor;
    else if(str == "SmokeSensor") return DeviceType::SmokeSensor;
    else if(str == "OtherSensors") return DeviceType::OtherDevice;
    else if(str == "VideoCameras") return DeviceType::VideoCameras;
    else if(str == "SmartLocks") return DeviceType::SmartLocks;
    else if(str == "OtherDevice") return DeviceType::OtherDevice;
    throw std::runtime_error("Unknown device type: " + str);
}

std::string DeviceStatusToString(DeviceStatus status)
{
    switch (status)
    {
    case DeviceStatus::Default: return "Default";
    case DeviceStatus::Error: return "Error";
    case DeviceStatus::Running: return "Running";
    case DeviceStatus::Stopped: return "Stopped";
    default:return " ";
    }
}

DeviceStatus StringToDeviceStatus(const std::string& str)
{
    if(str == "Runnning") return DeviceStatus::Running;
    else if(str == "Stopped") return DeviceStatus::Stopped;
    else if(str == "Error") return DeviceStatus::Error;
    else if(str == "Default") return DeviceStatus::Default;

    throw std::runtime_error("Unknown devise status: " + str);
}

std::string ActuatorTypeToString(ActuatorType type)
{
    switch (type)
    {
    case ActuatorType::Relay: return "Relay";
    case ActuatorType::Motor: return "Motor";
    case ActuatorType::Servo: return "Servo";
    case ActuatorType::PwmController: return "PwmController";
    case ActuatorType::Valve: return "Valve";
    case ActuatorType::Lock: return "Lock";
    case ActuatorType::Heater: return "Heater";
    case ActuatorType::Cooler: return "Cooler";
    case ActuatorType::Buzzer: return "Buzzer";
    case ActuatorType::Display: return "Display";
    case ActuatorType::Other: return "Other";
    default: return " ";
    }
}

ActuatorType StringToActuatorType(const std::string& str)
{
    if(str == "Relay") return ActuatorType::Relay;
    else if(str == "Motor") return ActuatorType::Motor;
    else if(str == "Servo") return ActuatorType::Servo;
    else if(str == "PwmController") return ActuatorType::PwmController;
    else if(str == "Valve") return ActuatorType::Valve;
    else if(str == "Lock") return ActuatorType::Lock;
    else if(str == "Heater") return ActuatorType::Heater;
    else if(str == "Cooler") return ActuatorType::Cooler;
    else if(str == "Buzzer") return ActuatorType::Buzzer;
    else if(str == "Display") return ActuatorType::Display;
    else if(str == "Other") return ActuatorType::Other;
    throw std::runtime_error("Unknown actuator type: " + str);
}



