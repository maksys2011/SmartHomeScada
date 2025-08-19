#pragma once
#include <optional>
#include <chrono>
#include <string>
#include <variant>
#include <cmath>
#include "Enum.hpp"
#include "SensorConfig.hpp"

class SensorState
{
    private:
    using TimePoint = std::chrono::system_clock::time_point;
    using Value = std::variant<int64_t, double, bool>;

    Status sensorStatus;                                        //  текущий статус датчика  
    std::optional<Value> lastValue;                             //  последнее полученное значение датчика
    TimePoint lastUpdateTime;                                   //  время последнего обновления
    std::optional<int> errorCode;                               //  код ошибки
    std::optional<std::string> errorMessage;                    //  описание ошибка для логов
    bool staleFlag;                                             //  флаг, что значение устарело
    bool qualityGood;                                           //  качество данных 
    SensorConfig &config;                                       //  храним текущие конфигурации

    public:

    SensorState(SensorConfig config) : sensorStatus(Status::Ok), 
                    lastUpdateTime(std::chrono::system_clock::now()),
                    errorCode(std::nullopt), 
                    errorMessage(std::nullopt), 
                    staleFlag(false), 
                    qualityGood(true),
                    config(config){}
    
    Status getStatus() const;

    SensorConfig& getSensorConfig() const;

    std::optional<Value> getLastValue() const;

    std::chrono::system_clock::time_point getLastUpdateTime() const; // момент последнего обновления

    std::optional<int> getErrorCode() const;

    std::optional<std::string> getErrorMessage()const;              // возвращает код ошибки (если не nullopt)             // возвращает текст ошибка (если не nullopt)

    bool isStale() const;                                           // возвращает true, если значение устарело

    bool isQualityGood() const;                                     //  возвращает признак качества данных

    void setStatus(Status newStatus);                               //  устанавливает статус

    void setError(int code, const std::string& message);            // status меняем на error

    void clearError();                                              // очищает ошибку - status::ok

    void markStale();                                               // помечает данные как устаревшие

    void markQualityGood(bool isGood);                              // устанавливает признак качества данных

    void reset();                                                   // устанавливает настройки по умолчанию

    void updateValue(int64_t v, bool qualityGood, TimePoint ts);         // для счетчиков

    void updateValue(double v, bool qualityGood, TimePoint ts);      // для аналоговых устройств

    void updateValue(bool v, bool qualityGood, TimePoint ts);        // для акуаторов



















};