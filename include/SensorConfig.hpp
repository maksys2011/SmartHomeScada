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
                        // общие поля
    std::string id;                         // уникальный идентификатор устройства
    std::string name;                       // имя устройства
    DeviceType type;                        // тип устройства
    std::string ioAddress;                  // адресс источника данных
    std::string unit;                       // единица измерения
                        // тайминиги и повтора
    int pollIntervalMs;                     // минимальный интервал между опросами
    int timeoutMs;                          // таймаут чтения (мс)
    int ttlMs;                               // время актульности данных
    int retries;                            // количество повторов чтения
    int backoffMs;                          // пауза между потворами

                        // аналоговые параметры
    std::optional<double>minValue;          // нижняя граница допустимых значений
    std::optional<double>maxValue;          // верхняя граница допустимых значений
    std::optional<double>deadband;          // мертвая зона (не реагировать на значение в пределах этой зоны)

                        // дискретные параметры
    std::optional<int>pulsesPerUnit;        // сколько импульсов соответствует единицы измерения
    std::optional<int>rolloverValue;        // максимальное значение счетчика (после будет 0) 

                        // счетчики
    std::optional<int>debounceMs;    
    std::optional<bool>activeHigh;          // полярность входа
    
    public:
    
    SensorConfig() = default;

    SensorConfig(const std::string& id, const std::string& name, int pollIntervalMs,
    DeviceType type, int ioAddress, const std::string& unit, int timeoutMs, int ttlMs, int retries,
    int backoffMs);

    void fromJson(const nlohmann::json& file);

    void fromJson(const std::string& path);

    const void printInfo();

    const std::string& getId() const;
    
    const std::string& getName() const;

    const DeviceType getType() const;
    
    std::optional<double> getMinValue() const;

    std::optional<double> getMaxValue() const;
       
    void SetMinValue(double);

    void SetMaxValue(double);

    void SetDeadband(double);

    void SetDebounce(int);

    void SetPulsesPerUnit(int);

    void SetRolloverValue(int);

    void SetActiveHigh(bool);
    
    friend std::ostream& operator<<(std::ostream& os, const SensorConfig& obj);
    
    const SensorConfig& operator=(SensorConfig& obj);

};