#pragma once
#include <string>
#include <vector>
#include "IFunction.h"

class ExpressionEvaluator {
public:
    // Передаём вектор функций по ссылке
    explicit ExpressionEvaluator(const std::vector<IFunction*>& funcs);
    double evaluate(const std::string& expr) const;  // добавил const

private:
    const std::vector<IFunction*>& functions;
};