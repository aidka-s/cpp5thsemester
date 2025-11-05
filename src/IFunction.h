#pragma once
#include <string>

// базовый интерфейс для функции, подключаемой из DLL
class IFunction {
public:
    virtual ~IFunction() = default;

    // имя функции (например, "sin", "deg")
    virtual std::string name() const = 0;

    // сама реализация функции
    virtual double execute(double arg) const = 0;
};
