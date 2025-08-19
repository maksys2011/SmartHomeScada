#include "SensorConfig.hpp"
using json = nlohmann::json;

SensorConfig::SensorConfig(const std::string& id, const std::string& name, int pollIntervalMs, 
    DeviceType type, int ioAddress, int timeoutMs, int ttlMs, int retries,
    int backoffMs)
    {
        this->id = id;
        this->name = name;
        this->pollIntervalMs = pollIntervalMs;
        this->type = type;
        this->ioAddress = ioAddress;
        this->timeoutMs = timeoutMs;
        this->ttlMs = ttlMs;
        this->retries = retries;
        this->backoffMs = backoffMs;
    }

void SensorConfig::fromJson(const json& file)
    {
        id = file.at("id").get<std::string>();
        name = file.at("name").get<std::string>();
        type = StringToDeviceType(file.at("type").get<std::string>());
        ioAddress = file.at("ioAddress").get<std::string>();
        pollIntervalMs = file.at("pollIntervalMs").get<int>();
        timeoutMs = file.at("timeoutMs").get<int>();
        ttlMs = file.at("ttlMs").get<int>();    
        retries = file.at("retries").get<int>();
        backoffMs = file.at("backoffMs").get<int>();

        if(file.contains("unit") && !file["unit"].is_null())
            {
            unit = file.at("unit").get<std::string>();
        }else{
            unit.reset();
            }

        if(file.contains("minValue") && !file["minValue"].is_null())
            {
                minValue = file.at("minValue").get<double>();
            }else{
                minValue.reset();
            }

        if(file.contains("maxValue") && !file["maxValue"].is_null())
            {
                maxValue = file.at("maxValue").get<double>();
            }else{
                 maxValue.reset();
            }

        if(file.contains("deadband") && !file["deadband"].is_null())
            {
                deadband = file.at("deadband").get<double>();
            }else{
                 deadband.reset();
            }

        if(file.contains("hysteresisPct") && !file["hysteresisPct"].is_null())
            {
                hysteresisPct = file.at("hysteresisPct").get<double>();
            }else{
                hysteresisPct.reset();
            }   
            
        if(file.contains("debounceCount") && !file["debounceCount"].is_null())
            {
                debounceCount = file.at("debounceCount");
            }else{
                debounceCount.reset();
            }

        if(file.contains("pulsesPerUnit") && !file["pulsesPerUnit"].is_null())
            {
                pulsesPerUnit = file.at("pulsesPerUnit").get<int>();
            }else{
                pulsesPerUnit.reset();
            }

        if(file.contains("rolloverValue") && !file["rolloverValue"].is_null())
            {
                rolloverValue = file.at("rolloverValue").get<int>();
            }else{
                 rolloverValue.reset();
            }

        if(file.contains("debounceMs") && !file["debounceMs"].is_null())
            {
                debounceMs = file.at("debounceMs").get<int>();
            }else{
                debounceMs.reset();
            }

        if(file.contains("activeHigh") && !file["activeHigh"].is_null())
            {
                 activeHigh = file.at("activeHigh").get<bool>();
            }else{
                 activeHigh.reset();
            }
            
        if(file.contains("warnLow") && !file["warnLow"].is_null())
            {
                warnLow = file.at("warnLow").get<double>();    
            }else{
                warnLow.reset();
            }

        if(file.contains("warnHigh") && !file["warnHigh"].is_null())
            {
                warnHigh = file.at("warnHigh").get<double>();
            }else{
                warnHigh.reset();
            }

        if(file.contains("alarmLow") && !file["alarmLow"].is_null())
            {
                alarmLow = file.at("alarmLow").get<double>();
            }else{
                alarmLow.reset();
            }

        if(file.contains("alarmHigh") && !file["alarmHigh"].is_null())
            {
                alarmHigh = file.at("alarmHigh").get<double>();
            }else{
                alarmHigh.reset();
            }
        if(file.contains("alarm_policy") && file["alarm_policy"].is_null())
        {
            alarm_policy = StringAlarmPolicy(file.at("alarm_policy").get<std::string>());
        }else{
            alarm_policy = AlarmPolicy::Strict;
        }     
    } 

void SensorConfig::fromJson(const std::string& path)

    {
        std::ifstream file(path);
        if(!file)
        {
            throw std::runtime_error("Cannot open config file: " + path);
        }
        json j;
        file >> j;

        fromJson(j);
    }   

const void SensorConfig::printInfo()
{
    std::cout << "id: " << getId()<< std::endl;
    std::cout << "name: " << getName() << std::endl;
    std::cout << "type: " << DeviceTypeToString(getType()) << std::endl;

}

const std::string& SensorConfig::getId() const
{
    return id;
}
    
const std::string& SensorConfig::getName() const
{
    return name;
}

const DeviceType SensorConfig::getType() const
{
    return type;
}

std::optional<double> SensorConfig::getMinValue() const
{
    return minValue;
}

std::optional<double> SensorConfig::getMaxValue() const
{
    return maxValue;
}

std::optional<double> SensorConfig::getDeadband() const
{
    return deadband;
}

std::optional<double> SensorConfig::getWarnLow() const
{
    return std::optional<double>(warnLow);
}

std::optional<double> SensorConfig::getWarnHigh() const
{
    return std::optional<double>(warnHigh);
}

std::optional<double> SensorConfig::getHisteresisPct() const
{
    return std::optional<double>(hysteresisPct);
}

AlarmPolicy SensorConfig::getAlarmPolicy() const
{
    return AlarmPolicy(alarm_policy);
}

std::optional<double> SensorConfig::getAlarmLow() const
{
    return std::optional(alarmLow);
}

std::optional<double> SensorConfig::getAlarmHigh() const
{
    return std::optional(alarmHigh);
}

void SensorConfig::setMinValue(double value)
{
    minValue = value;
}

void SensorConfig::setMaxValue(double value)
{
    maxValue = value;
}

void SensorConfig::setDeadband(double value)
{
    deadband = value;
} 

void SensorConfig::setDebounce(int value)
{
    debounceMs = value;
}

void SensorConfig::setPulsesPerUnit(int value)
{
    pulsesPerUnit = value;
}

void SensorConfig::setRolloverValue(int value)
{
    rolloverValue = value;
}

void SensorConfig::setActiveHigh(bool value)
{
    activeHigh = value;
}

void SensorConfig::validate()
{
    // ОБЯЗАТЕЛЬНЫЕ ПОЛЯ — ПРОВЕРКА
    if (id.empty()) {
        throw std::runtime_error("id is empty or has invalid characters");
    }
    if (name.empty()) {
        throw std::runtime_error("name is empty");
    }
    if (ioAddress.empty()) {
        throw std::runtime_error("ioAddress is empty");
    }
    if (pollIntervalMs < 100 || pollIntervalMs > 86400000) {
        throw std::runtime_error("pollIntervalMs must be in 100..86400000");
    }
    if (timeoutMs <= 0 || timeoutMs >= pollIntervalMs) {
        throw std::runtime_error("timeoutMs must be > 0 and < pollIntervalMs");
    }
    if (ttlMs < pollIntervalMs) {
        throw std::runtime_error("ttlMs must be >= pollIntervalMs");
    }
    if (retries < 0 || retries > 10) {
        throw std::runtime_error("retries must be in 0..10");
    }
    if (backoffMs < 0 || backoffMs > 60000) {
        throw std::runtime_error("backoffMs must be in 0..60000");
    }

    // ВЕТКИ ПО ТИПУ УСТРОЙСТВА
    DeviceClass cls = classify(type);

    // === NON-ANALOG ===
    if (cls != DeviceClass::Analog) {
        // thresholds для не-Analog — игнорируем
        if (warnHigh || warnLow || alarmHigh || alarmLow) {
            std::cout << "thresholds ignored for non-analog" << "\n";
        }

        if (cls == DeviceClass::Binary) {
            if (debounceMs) {
                const auto v = *debounceMs;
                if (v < 0 || v > 10000) {
                    throw std::runtime_error("debounceMs must be in 0..10000");
                }
            }
            if (debounceCount) {
                const auto n = *debounceCount;
                if (n < 0 || n > 10) {
                    throw std::runtime_error("debounceCount must be in 0..10");
                }
            }
        }

        if (cls == DeviceClass::Counter) {
            if (debounceMs) {
                const auto v = *debounceMs;
                if (v < 0 || v > 10000) {
                    throw std::runtime_error("debounceMs must be in 0..10000");
                }
            }
            if (debounceCount) {
                const auto n = *debounceCount;
                if (n < 0 || n > 10) {
                    throw std::runtime_error("debounceCount must be in 0..10");
                }
            }
            if (pulsesPerUnit) {
                const auto pulses = *pulsesPerUnit;
                if (pulses <= 0) {
                    throw std::runtime_error("pulsesPerUnit must be > 0");
                }
            }
            if (rolloverValue) {
                const auto rollover = *rolloverValue;
                if (rollover <= 0) {
                    throw std::runtime_error("rolloverValue must be > 0");
                }
            }
            if (pulsesPerUnit && rolloverValue) {
                const auto pulses   = *pulsesPerUnit;
                const auto rollover = *rolloverValue;
                if (rollover % static_cast<uint64_t>(pulses) != 0ULL) {
                    std::cout << "rolloverValue should be divisible by pulsesPerUnit" << std::endl;
                }
            }
        }

        return; // дальше аналоговые проверки не нужны
    }

    // === ANALOG === (всё, что связано с alarm_policy — ТОЛЬКО здесь)
    if (!unit || unit->empty()) {
        throw std::runtime_error("unit is required for analog sensors");
    }

    // min/max: если обе заданы — порядок
    if (minValue && maxValue) {
        if (*minValue > *maxValue) {
            throw std::runtime_error("minValue must be <= maxValue");
        }
    }

    // --- Политики тревог ---
    if (alarm_policy == AlarmPolicy::FivePctOverNorm) {
        // Требует обе границы; ручные пороги будут переопределены
        if (!minValue) {
            throw std::runtime_error("minValue is required");
        }
        if (!maxValue) {
            throw std::runtime_error("maxValue is required");
        }
        if (warnHigh || warnLow || alarmHigh || alarmLow) {
            std::cout << "thresholds will be overridden" << "\n";
        }
        return; // Завершаем на этой политике
    }
    else if (alarm_policy == AlarmPolicy::Strict) {
        // Шаг 1 — должен быть хотя бы один порог
        if (!warnHigh && !warnLow && !alarmHigh && !alarmLow) {
            throw std::runtime_error("strict alarm_policy requires at least one threshold");
        }

        // Шаг 2 — попадание в min/max для каждого заданного порога
        if (minValue) {
            const auto mn = *minValue;
            if (alarmLow  && *alarmLow  < mn) throw std::runtime_error("alarmLow must be >= minValue");
            if (warnLow   && *warnLow   < mn) throw std::runtime_error("warnLow must be >= minValue");
            if (warnHigh  && *warnHigh  < mn) throw std::runtime_error("warnHigh must be >= minValue");
            if (alarmHigh && *alarmHigh < mn) throw std::runtime_error("alarmHigh must be >= minValue");
        }
        if (maxValue) {
            const auto mx = *maxValue;
            if (alarmLow  && *alarmLow  > mx) throw std::runtime_error("alarmLow must be <= maxValue");
            if (warnLow   && *warnLow   > mx) throw std::runtime_error("warnLow must be <= maxValue");
            if (warnHigh  && *warnHigh  > mx) throw std::runtime_error("warnHigh must be <= maxValue");
            if (alarmHigh && *alarmHigh > mx) throw std::runtime_error("alarmHigh must be <= maxValue");
        }

        // Шаг 3 — порядок порогов (проверяем только существующие пары)
        if (alarmLow && warnLow   && *alarmLow  > *warnLow)   {
            throw std::runtime_error("alarmLow must be <= warnLow");
        }
        if (warnLow  && warnHigh  && *warnLow   > *warnHigh)  {
            throw std::runtime_error("warnLow must be <= warnHigh");
        }
        if (warnHigh && alarmHigh && *warnHigh > *alarmHigh) {
            throw std::runtime_error("warnHigh must be <= alarmHigh");
        }

        // Шаг 4 — доп. параметры
        if (deadband && *deadband < 0) {
            throw std::runtime_error("deadband must be >= 0");
        }
        if (hysteresisPct) {
            const auto h = *hysteresisPct;
            if (h < 0 || h > 50) {
                throw std::runtime_error("hysteresisPct must be in 0..50");
            }
        }
        if (debounceCount) {
            const auto d = *debounceCount;
            if (d < 0 || d > 10) {
                throw std::runtime_error("debounceCount must be in 0..10");
            }
        }

        return; // Завершили ветку Strict
    }
    else {
        // Неподдерживаемая политика — формально не должна сюда попадать,
        // т.к. из from_json() приходит валидное значение.
        // Оставляем на всякий случай:
        throw std::runtime_error("unsupported alarm_policy value");
    }
}


  




    