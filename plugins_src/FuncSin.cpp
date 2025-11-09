#include "IFunction.h"
#include <cmath>
#include <string>
#include <stdexcept>

class FuncSin : public IFunction {
public:
    std::string name() const override { return "sin"; }

    double execute(double arg) const override {
        // синус принимает градусы, переводим в радианы
        return std::sin(arg * M_PI / 180.0);
    }
};

extern "C" __declspec(dllexport) IFunction* create() {
    return new FuncSin();
}