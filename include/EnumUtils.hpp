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

DeviceClass classify(DeviceType);                                    // классификатор классов устройств

std::string DeviceClassToString(DeviceClass cls);                    // преобразование в строку

AlarmPolicy StringAlarmPolicy(const std::string& str);               // преоразование string в AlarmPolicy

std::string AlarmPolicyToString(AlarmPolicy alarm_police);           // преоразование AlarmPolicy в string