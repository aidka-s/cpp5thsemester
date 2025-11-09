#include "IFunction.h"
#include <cmath>
#include <string>

class FuncDeg : public IFunction {
public:
    std::string name() const override { return "deg"; }

    double execute(double arg) const override {
        // Перевод радиан в градусы
        return arg * 180.0 / M_PI;
    }
};

extern "C" __declspec(dllexport) IFunction* create() {
    return new FuncDeg();
}
