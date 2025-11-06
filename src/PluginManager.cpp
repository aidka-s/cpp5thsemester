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

            dlls.push_back(dll);
            std::cout << "Loaded: " << entry.path().filename().string() << std::endl;
        }
    }

    if (dlls.empty())
        std::cout << "No plugins loaded.\n";
}

