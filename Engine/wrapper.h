#pragma once
#include <vector>
#include <functional>
#include <string>

using InputArgs = std::vector<std::pair<std::string, std::string>>;
using ArgsMap = std::vector<std::pair<std::string, std::string>>;

class Wrapper {
private:
    template <typename Subject, typename Method, std::size_t... I>
    std::string func_caller(Subject* subject, Method method, const std::vector<std::string>& args, std::index_sequence<I...>);
    std::function<std::string(const std::vector<std::string>& argsVector)> function;
    std::vector<std::string> argsTitles;
public:
    template<typename Subject, typename... Args>
    Wrapper(Subject* subject, std::string(Subject::* method)(Args...), const InputArgs& input_args);
    std::string execute(const ArgsMap& args_map);
};
