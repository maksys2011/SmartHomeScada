#pragma once
#include <string>
#include <optional>
#include <fstream>
#include "Enum.hpp"
#include "EnumUtils.hpp"
#include "nlohmann/json.hpp"

class SensorConfig                      // КОНФИГУРАЦИИ ДАТЧИКОВ
{
    private:
                        // общие поля/обязательные
    std::string id;                         // уникальный идентификатор устройства
    std::string name;                       // имя устройства
    DeviceType type;                        // тип устройства
    std::string ioAddress;                  // адресс источника данных                          
                        // тайминиги и повтора
    int pollIntervalMs;                     // минимальный интервал между опросами
    int timeoutMs;                          // таймаут чтения (мс)
    int ttlMs;                              // время актульности данных
    int retries;                            // количество повторов чтения
    int backoffMs;                          // пауза между потворами
    
                        // параметры для аналоговых устройств
    std::optional<std::string> unit;        // единица измерения            
    std::optional<double>minValue;          // нижняя граница допустимых значений
    std::optional<double>maxValue;          // верхняя граница допустимых значений
    std::optional<double>deadband;          // мертвая зона (не реагировать на значение в пределах этой зоны)
    std::optional<double>hysteresisPct;     // процент гистерезиса для аналоговых датчиков
    std::optional<int>debounceCount;        // 
                        // дискретные параметры
    std::optional<int>pulsesPerUnit;        // сколько импульсов соответствует единицы измерения
    std::optional<int>rolloverValue;        // максимальное значение счетчика (после будет 0) 

                        // счетчики
    std::optional<int>debounceMs;    
    std::optional<bool>activeHigh;                                   // полярность входа
                        // пороговые значение
    std::optional<double>warnLow;                                    // нижняя граница предупреждения
    std::optional<double>warnHigh;                                   // верхняя граница предупреждения
    std::optional<double>alarmLow;                                   // нижняя граница аварии
    std::optional<double>alarmHigh;                                  // верхняя граница авари
    AlarmPolicy alarm_policy = AlarmPolicy::Strict;                  // политикак тревог
    public:
    
    SensorConfig() = default;

    SensorConfig(const std::string& id, const std::string& name, int pollIntervalMs,
    DeviceType type, int ioAddress, int timeoutMs, int ttlMs, int retries,
    int backoffMs);

    void fromJson(const nlohmann::json& file);

    void fromJson(const std::string& path);

    const void printInfo();

    const std::string& getId() const;
    
    const std::string& getName() const;

    const DeviceType getType() const;
    
    std::optional<double> getMinValue() const;

    std::optional<double> getMaxValue() const;

    std::optional<double> getDeadband() const;

    std::optional<double>getWarnLow() const;                                    // нижняя граница предупреждения

    std::optional<double>getWarnHigh() const;                                    // нижняя граница предупреждения

    std::optional<double>getHisteresisPct() const;

    AlarmPolicy getAlarmPolicy() const;

    std::optional<double> getAlarmLow() const;

    std::optional<double> getAlarmHigh() const;

    void setMinValue(double);

    void setMaxValue(double);

    void setDeadband(double);

    void setDebounce(int);

    void setPulsesPerUnit(int);

    void setRolloverValue(int);

    void setActiveHigh(bool);
    
    friend std::ostream& operator<<(std::ostream& os, const SensorConfig& obj);
    
    const SensorConfig& operator=(SensorConfig& obj);

    void validate();

};