#pragma once
#include <iostream>
#include <string>
#include "Enum.hpp"

std::string DeviceTypeToString(DeviceType type);                    // преобразование DeviceType в string

DeviceType StringToDeviceType(const std::string& str);              // преобразование string в DeviceType

std::string DeviceStatusToString(DeviceStatus status);              // преобразование DeviceStatus в string

DeviceStatus StringToDeviceStatus(const std::string& str);          // преобразование string в DeviceStatus

std::string ActuatorTypeToString(ActuatorType type);                // преобразование ActuatorType в string

ActuatorType StringToActuatorType(const std::string& str);          // преобразование string в ActuatorType