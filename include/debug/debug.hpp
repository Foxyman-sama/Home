#ifndef LOCALHOST_DEBUG_INCLUDE_HPP
#define LOCALHOST_DEBUG_INCLUDE_HPP
#include <iostream>
#include <format>
#include <chrono>

namespace local::utility {
class Debug {
private:
    static inline std::stringstream s_ss_;

public:
    template<typename T, typename... Args>
    static constexpr void debug(T &&_value, Args &&..._args) noexcept {
        s_ss_ << _value;
        debug(_args...);
    }
    static void debug() noexcept {
        auto now { std::chrono::system_clock::now() };
        auto time { std::chrono::current_zone()->to_local(now) };
        auto time_str { std::format("{:%X}", time)  };
        std::cout << '[' << time_str << "]: " << s_ss_.str() << '\n';
        s_ss_.str(std::string { });
        s_ss_.clear();
    }
};
}

#endif
