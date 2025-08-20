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
void SensorState::updateValue(double value, bool isQualityGood)
{
    // Шаг 0 - перед записью обновляем время и ставим флаг устаревшего значения
    //lastUpdateTime = ts;
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
    double warn_high = config.getWarnHigh().value();
    double alarm_low = config.getAlarmLow().value();
    double alarm_high = config.getAlarmHigh().value();
    double histeresis_pct = config.getHisteresisPct().value();
    const auto R = std::fabs(warn_high - warn_low);
    const auto H = (histeresis_pct / 100.0) * R;
    
    std::cout << "входим к гетерезис" << std::endl;
    // Шаг 6.1
    if(config.getAlarmPolicy() == AlarmPolicy::Strict)
    {
        if(value <= alarm_low) sensorStatus = Status::Alarm;
        else if(value >= alarm_high) sensorStatus = Status::Alarm; // value = 79
        else if (value <= warn_low) sensorStatus = Status::Warning;
        else if(value >= warn_high) sensorStatus = Status::Warning;
        else sensorStatus = Status::Ok;
        
        std::cout << "StTostring: " << StatusToString(sensorStatus) << std::endl;

        auto prevStatus = sensorStatus;

        if(prevStatus == Status::Warning)
        {   
            if(value <= alarm_low || value >= alarm_high) prevStatus = Status::Alarm;
            else if(value > warn_low + H && value < warn_high - H) prevStatus = Status::Ok;
            else prevStatus = Status::Warning;
        }
        if(prevStatus == Status::Alarm)
        {
            if(value >= alarm_high || value <= alarm_low) prevStatus = Status::Alarm;
            else if(value < alarm_high - H)
            {
                if(value >= warn_high) prevStatus = Status::Warning;
                else prevStatus = Status::Ok;
            }
            else if(value > alarm_low + H)
            {
                if(value <= warn_low) prevStatus = Status::Warning;
                else prevStatus = Status::Ok;
            }
        }
        sensorStatus = prevStatus;
        
    }
    
}













void SensorState::printInfoState() const
{
    std::cout << StatusToString(sensorStatus) << std::endl;
}
