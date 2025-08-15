#pragma once
#include <optional>
#include <string>
#include <fstream>
#include "Enum.hpp"
#include "EnumUtils.hpp"
#include "nlohmann/json.hpp"

class ActuatorConfig                    //КОНФИГУРАЦИИ ИСПОЛНИТЕЛЬНЫХ МЕХАНИЗМОВ
{
    private:
                        // общие поля
    std::string id;                         // уникальный идентификатор механихма
    std::string name;                       // имя механизма
    ActuatorType type;                    // тип механизма
    std::string ioAddress;                  // адресс источника данных
    
    std::optional<std::string> unit;                       // единица измерения
    std::optional<bool> activeHigh;           // логи активации
    std::optional<std::string> description;   // описание

    public:

    ActuatorConfig() = default;

    void fromJson(const nlohmann::json& j);

    void fromJson(const std::string& path);

    void validate() const;

    const std::string& getId() const;

    const std::string& getName() const ;

};