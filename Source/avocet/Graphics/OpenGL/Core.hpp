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
    enum class debugging_mode { none = 0, basic, advanced };

    [[nodiscard]]
    constexpr debugging_mode get_debugging_mode() noexcept {
        #if defined(GL_ADVANCED_DEBUGGING)
            return debugging_mode::advanced;
        #elif defined(GL_BASIC_DEBUGGING)
            return debugging_mode::basic;
        #elif defined(NDEBUG)
            // release build
            return debugging_mode::none;
        #elif defined(__APPLE__)
            return debugging_mode::basic;
        #else
            return debugging_mode::basic;
        #endif
    }

    inline void do_check_for_errors(std::source_location loc) {
        if constexpr(get_debugging_mode() == debugging_mode::basic)
            check_for_errors(loc);
    }

    template<class Fn>
    class [[nodiscard]] gl_function {
        Fn m_Fn;
        std::source_location m_Loc;

        template<class... Args>
            requires std::invocable<Fn, Args...>
        [[nodiscard]]
        std::invoke_result_t<Fn, Args...> safe_invoke(Args... args) const {
            if(!m_Fn) throw std::runtime_error{"Null OpenGL function pointer"};
            return m_Fn(args...);
        }
    public:
        gl_function(Fn f, std::source_location loc = std::source_location::current())
            : m_Fn{f}
            , m_Loc{loc}
        {}

        template<class... Args>
            requires std::invocable<Fn, Args...>
        [[nodiscard]]
        std::invoke_result_t<Fn, Args...> operator()(Args... args) const {
            auto ret{safe_invoke(args...)};
            do_check_for_errors(m_Loc);

            return ret;
        }

        template<class... Args>
            requires std::invocable<Fn, Args...> && std::is_void_v<std::invoke_result_t<Fn, Args...>>
        void operator()(Args... args) const {
            safe_invoke(args...);
            do_check_for_errors(m_Loc);
        }
    };
}