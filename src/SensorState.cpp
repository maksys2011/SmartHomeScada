#include "SensorState.hpp"
using TimePoint = std::chrono::system_clock::time_point;
using Value = std::variant<int64_t, double, bool>;

SensorConfig& SensorState::getSensorConfig() const
{
    return config;
}

Status SensorState::getStatus() const
{
    return sensorStatus;
}

std::optional<std::variant<int64_t, double, bool>> SensorState::getLastValue() const
{
    return lastValue;
}

std::chrono::system_clock::time_point SensorState::getLastUpdateTime() const
{
    return lastUpdateTime;
}

std::optional<int> SensorState::getErrorCode() const
{
    return errorCode;
}

std::optional<std::string> SensorState::getErrorMessage()const
{
    return errorMessage;
}           

bool SensorState::isStale() const
{
    return staleFlag;
}

bool SensorState::isQualityGood() const
{
    return qualityGood;
}                                    

void SensorState::setStatus(Status newStatus)
{
    sensorStatus = newStatus;
}

void SensorState::setError(int code, const std::string& message)
{
    sensorStatus = Status::Invalid;
    errorCode = code;
    errorMessage = message;
}                  

void SensorState::clearError()
{
    errorCode = std::nullopt;
    errorMessage = std::nullopt;
}                                            

void SensorState::markStale()  
{
    staleFlag = true;
    sensorStatus = Status::Invalid;
}                                              

void SensorState::markQualityGood(bool isGood)
{
    qualityGood = isGood;
}                            

void SensorState::reset()
{
    sensorStatus = Status::Ok;
    lastValue = std::nullopt;
    lastUpdateTime = std::chrono::system_clock::now();
    errorCode = std::nullopt; 
    errorMessage = std::nullopt; 
    staleFlag = false; 
    qualityGood = true;
}

// Для аналоговых устройств
void SensorState::updateValue(double value, bool isQualityGood, TimePoint ts)
{
    // Шаг 0 - перед записью обновляем время и ставим флаг устаревшего значения
    lastUpdateTime = ts;
    staleFlag = false;
    // Шаг 1 - Проверка качества сигнала
    if(isQualityGood == false)
    {
        qualityGood = false;
        setError(1, "Bad quality");
        return;
    }
    // Шаг 2 - проверяем значение на соответствие типу датчика/устройства
    if(classify(config.getType()) != DeviceClass::Analog)
    {
        setError(2, "Type mismatch: expected <cfg.type");
        return;
    }
    // Шаг 3 - базовая валидация значения
    if(std::isnan(value) || std::isinf(value))
    {
        setError(3, "Bad numeric");
        return;
    }
    // Шаг 4 - фильтрация мелких изменений ///  Щаг 5 - если проверку прошли принимаем новое значени
    if(lastValue.has_value())
    {   
        if(std::holds_alternative<double>(*lastValue))
        {
            auto prev = std::get<double>(*lastValue);
            double delta = std::fabs(value - prev);
            if(config.getDeadband() <= 0)
            {
                qualityGood = true;
                clearError();
                lastValue = value;
                return;
            }
            if(delta < config.getDeadband())
            {
                qualityGood = true;
                return;
            }
                qualityGood = true;
                clearError();
                lastValue = value;
        }
        else
        {
            assert(false);
            setError(4,"Variant type mismatch");
        }
    }
    else
    {
        qualityGood = true;
        clearError();
        lastValue = value;
    }
    // Шаг - 6 классификация статуса === WARN === ALARM === OK ===

    double warn_low = config.getWarnLow().value();
    double warn_High = config.getWarnHigh().value();
    double histeresis_pct = config.getHisteresisPct().value();

    const auto R = std::fabs(warn_High - warn_low);
    const auto H = histeresis_pct * R;

    if(config.getAlarmPolicy() == AlarmPolicy::Strict)
    {
        if(value <= warn_low)
        {
            if(value <= config.getAlarmLow().value())
            {
                sensorStatus = Status::Alarm;
            }
            else
            {
                sensorStatus = Status::Warning;
            }
        }
        else if(value >= warn_High)
        {
            if(value >= config.getAlarmHigh().value())
            {
                sensorStatus = Status::Alarm;
            }
            else
            {
                sensorStatus = Status::Warning;
            }
        }
        else
        {
        sensorStatus = Status::Ok;
        }
    }
    
}

















void SensorState::updateValue(int64_t v, bool qualityGood, TimePoint ts)
{

}    
void SensorState::updateValue(bool v, bool qualityGood, TimePoint ts)
{

}  