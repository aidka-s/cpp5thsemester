#include "ExpressionEvaluator.h"
#include <iostream>

int main() {
    ExpressionEvaluator evaluator;
    evaluator.evaluate("16 + 4 * (3 - 1)");
    return 0;
}
