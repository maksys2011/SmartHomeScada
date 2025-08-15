#include "SensorState.hpp"

Status SensorState::getStatus() const
{
    return sensorStatus;
}

std::optional<double>SensorState::getLastValue() const
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
    sensorStatus = Status::Error;
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
    sensorStatus = Status::Disconected;
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

void SensorState::upDateValue(double newValue, bool qualityGood, 
    std::chrono::system_clock::time_point upDateTime)
    {

    }