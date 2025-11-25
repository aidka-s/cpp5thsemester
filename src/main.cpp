#include <iostream>
#include <windows.h>
#include "ExpressionEvaluator.h"
#include "PluginManager.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::cout << "=== Calculator started ===\n";

    PluginManager manager;
    manager.loadPlugins("./plugins");

    // Вывод списка загруженных функций
    const auto& funcs = manager.getFunctions();
    if (!funcs.empty()) {
        std::cout << "Loaded functions:\n";
        for (auto f : funcs) {
            std::cout << "- " << f->name() << std::endl;
        }
    }

    ExpressionEvaluator evaluator(funcs);

    std::string expr;
    std::cout << "Enter expression: ";
    std::getline(std::cin, expr);

    try {
        double result = evaluator.evaluate(expr);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    manager.unloadPlugins();

    std::cout << "==========================\n";
    return 0;
}
