#include <iostream>
#include "ExpressionEvaluator.h"
#include "PluginManager.h"

int main() {
    PluginManager manager;
    manager.loadPlugins("./plugins");

    ExpressionEvaluator evaluator;
    std::string expr = "16 + 4 * (3 - 1)";
    std::cout << "Result: " << evaluator.evaluate(expr) << std::endl;
}
