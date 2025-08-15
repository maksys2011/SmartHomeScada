#pragma once
#include <optional>
#include <chrono>
#include <string>
#include "Enum.hpp"

class SensorState
{
    private:

    Status sensorStatus;                                        //  текущий статус датчика  
    std::optional<double> lastValue;                            //  последнее полученное значение датчика
    std::chrono::system_clock::time_point lastUpdateTime;       //  время последнего обновления
    std::optional<int> errorCode;                               //  код ошибки
    std::optional<std::string> errorMessage;                    //  описание ошибка для логов
    bool staleFlag;                                             //  флаг, что значение устарело
    bool qualityGood;                                           //  качество данных 

    public:

    SensorState() : sensorStatus(Status::Ok), 
                    lastValue(std::nullopt), 
                    lastUpdateTime(std::chrono::system_clock::now()),
                    errorCode(std::nullopt), 
                    errorMessage(std::nullopt), 
                    staleFlag(false), 
                    qualityGood(true){}
    
    Status getStatus() const;

    std::optional<double> getLastValue() const;

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

    void upDateValue(double, bool, std::chrono::system_clock::time_point);

















};