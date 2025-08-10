#pragma once

enum class DeviceType                   // ТИПЫ ДАТЧИКОВ
{
    MotionSensor,                   	// датчик движения
    LightSensor,                   	    // датчик освещенности
    TemperatureSensor,                  // датчик температуры
    WaterPresenceSensor,                // датчик протечки
    AirHumiditySensor,              	// датчик увлажненности воздуха
    SmokeSensor,                    	// датчик дыма
    OtherSensors,                  	    // датчик иной
    ElectricSwitch,                 	// выключатель электрический
    VideoCameras,                 	    // видеокамера
    SmartLocks,                     	// умные замки
    OtherDevice                     	// иное устройство
};
enum class DeviceStatus                 // ПЕРЕЧИСЛЕНИЯ СТАТУСА УСТРОЙСТВ
{
    Running,                            // в работе
    Stopped,                            // отключен
    Error,                              // неисправность
    Default
};
enum class CommandStatus                // ПЕРЕЧИСЛЕНИЯ СТАТУСА ВЫПОЛНЕНИЯ КОМАНД             
{
    Success,                            // все выполнилось
    AlreadyRunning,                     // было включено
    WasTurnedOff,                       // было отключено
    Inhibited,                          // заблокированно правилом (пользователя, администратора)
    Error,                              // ошибка
    Timeout                             // нет подтверждения за время n
};
enum class SensorType                   // ВИДЫ УСТРОЙСТВ
{
    Analog,                              // аналоговое утройство
    Digital,                             // цыфровое устройство
    Counter,                             // счетчик
    Enum                                 // перечисление
};
enum class ActuatorType                  // ТИПЫ МЕХАНИЗМОВ
{
    Relay,                               // реле
    Motor,                               // двигатель
    Servo,                               // серводвигатель
    PwmController,                       // pwm контроллер
    Valve,                               // электроманитный клапан
    Lock,                                // умный замок
    Heater,                              // нагреватель или тепловентилятор
    Cooler,                              // охладитель
    Buzzer,                              // звуковой сигнал
    Display,                             // дисплей или индикатор
    Other                                // прочее устройство
};
enum class SensorStatus
{
    Ok,                                 // норма
    Warning,                            // предупреждение
    Error,                              // ошибка
    Disconected                         // потеря связи
};
