#include <iostream>
#include "ExpressionEvaluator.h"
#include "PluginManager.h"

int main() {
    std::cout << "=== Calculator started ===\n";

    PluginManager manager;
    manager.loadPlugins("./plugins");

    ExpressionEvaluator evaluator;

    std::string expr;
    std::cout << "Enter expression: ";
    std::getline(std::cin, expr);

    try {
        double result = evaluator.evaluate(expr);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "==========================\n";
    return 0;
}
