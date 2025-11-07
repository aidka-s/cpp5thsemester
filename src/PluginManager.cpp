#include "PluginManager.h"
#include <iostream>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

void PluginManager::loadPlugins(const std::string& folder) {
    std::cout << "Loading plugins from " << folder << "...\n";

    if (!fs::exists(folder)) {
        std::cout << "No plugin folder found.\n";
        return;
    }

    for (auto& entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() == ".dll") {
            auto path = entry.path().string();
            HMODULE dll = LoadLibraryA(path.c_str());

            if (!dll) {
                std::cerr << "Failed to load " << path << std::endl;
                continue;
            }
            using CreateFunc = IFunction* (*)();
            CreateFunc create = (CreateFunc)GetProcAddress(dll, "create");

            if (!create) {
                std::cerr << "⚠️  No create() found in " << path << std::endl;
                FreeLibrary(dll);
                continue;
            }

            IFunction* func = nullptr;
            try {
                func = create();
                functions.push_back(func);
                dlls.push_back(dll);
                std::cout << "✅ Loaded plugin: " << func->name() << std::endl;
            } catch (...) {
                std::cerr << "⚠️  Exception while initializing " << path << std::endl;
                FreeLibrary(dll);
            }
        }
    }

    if (functions.empty())
        std::cout << "No valid plugins loaded.\n";
}

void PluginManager::unloadPlugins() {
    for (auto f : functions) delete f;
    for (auto d : dlls) FreeLibrary(d);
    functions.clear();
    dlls.clear();
}