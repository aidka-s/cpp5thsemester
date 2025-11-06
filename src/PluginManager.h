#pragma once
#include "IFunction.h"
#include <vector>
#include <string>
#include <memory>

class PluginManager {
public:
    void loadPlugins(const std::string& folder);
    const std::vector<std::shared_ptr<IFunction>>& functions() const { return funcs; }

private:
    std::vector<void*> dlls;
    std::vector<std::shared_ptr<IFunction>> funcs;
};
