#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include "IFunction.h"

class PluginManager {
public:
    void loadPlugins(const std::string& folder);
    void unloadPlugins();
    const std::vector<IFunction*>& getFunctions() const { return functions; }

private:
    std::vector<HMODULE> dlls;
    std::vector<IFunction*> functions;
};
