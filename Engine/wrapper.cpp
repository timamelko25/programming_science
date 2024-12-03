#include "wrapper.h"
#include <vector>
#include <functional>
#include <string>
#include <iostream>
#include <algorithm>

using InputArgs = std::vector<std::pair<std::string, std::string>>;
using ArgsMap = std::vector<std::pair<std::string, std::string>>;

template <typename Subject, typename Method, std::size_t... I>
std::string Wrapper::func_caller(Subject* subject, Method method, const std::vector<std::string>& args, std::index_sequence<I...>) {
    return (subject->*method)(args[I]...);
}

template<typename Subject, typename... Args>
Wrapper::Wrapper(Subject* subject, std::string(Subject::* method)(Args...), const InputArgs& input_args) {
    if (input_args.size() != sizeof...(Args)) {
        std::cerr << "Wrong number of arguments." << std::endl;
    }

    for (const auto& arg : input_args) {
        argsTitles.push_back(arg.first);
    }

    function = [this, subject, method](const std::vector<std::string>& argsVector) {
        return func_caller(subject, method, argsVector, std::index_sequence_for<Args...>{});
    };
}

std::string Wrapper::execute(const ArgsMap& args_map) {
    if (args_map.size() != argsTitles.size()) {
        std::cerr << "Wrong number of arguments." << std::endl;
        return "";
    }
    std::vector<std::string> argsFunc;
    for (const auto& title : argsTitles) {
        auto it = std::find_if(args_map.begin(), args_map.end(), [&title](const std::pair<std::string, std::string>& pair) {
            return pair.first == title;
        });
        if (it == args_map.end()) {
            std::cerr << "Missing argument: " << title << std::endl;
            return "";
        }
        argsFunc.push_back(it->second);
    }
    return function(argsFunc);
}