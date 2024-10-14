#pragma once
#include <string>
#include <windows.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <filesystem>

class Loader {
private:
    std::vector<HMODULE> lodaded_modules;
    std::unordered_map<std::string, FARPROC> functionMap;

public:
    Loader(const std::string& directory);
    ~Loader();

    template<typename FuncType>
    FuncType get_function(const std::string& function_name);

    double method_function(const std::string& function_name, double arg);
};