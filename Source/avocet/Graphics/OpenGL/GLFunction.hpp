////////////////////////////////////////////////////////////////////
//                Copyright Oliver J. Rosten 2024.                //
// Distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.0. //
//    (See accompanying file LICENSE.md or copy at                //
//          https://www.gnu.org/licenses/gpl-3.0.en.html)         //
////////////////////////////////////////////////////////////////////

#pragma once

#include "avocet/Graphics/OpenGL/Errors.hpp"

#include <concepts>
#include <stdexcept>
#include <tuple>

namespace avocet::opengl {
    enum class debugging_mode { none = 0, basic };

    [[nodiscard]]
    constexpr debugging_mode get_debugging_mode() noexcept {
        #if defined(NDEBUG)
            return debugging_mode::none;
        #else
            return debugging_mode::basic;
        #endif
    }

    inline void do_check_for_errors(std::source_location loc) {
        if constexpr(get_debugging_mode() == debugging_mode::basic)
            check_for_errors(loc);
    }

    template<class Fn>
    class [[nodiscard]] gl_function;

    template<class R, class... Args>
    class [[nodiscard]] gl_function<R(Args...)> {
    public:
        using function_type = R(*)(Args...);

        gl_function(function_type f)
            : m_Fn{f}
        {}

        [[nodiscard]]
        R operator()(Args... args, std::source_location loc = std::source_location::current()) const {
            const auto ret{safe_invoke(args...)};
            do_check_for_errors(loc);

            return ret;
        }

        void operator()(Args... args, std::source_location loc = std::source_location::current()) const requires std::is_void_v<R> {
            safe_invoke(args...);
            do_check_for_errors(loc);
        }
    private:
        function_type m_Fn;

        [[nodiscard]]
        R safe_invoke(Args... args) const {
            if(!m_Fn) throw std::runtime_error{"Null OpenGL function pointer"};
            return m_Fn(args...);
        }
    };

    template<class R, class... Args>
    gl_function(R(*)(Args...)) -> gl_function<R(Args...)>;
}