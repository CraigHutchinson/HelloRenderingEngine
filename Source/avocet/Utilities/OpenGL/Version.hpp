////////////////////////////////////////////////////////////////////
//                Copyright Oliver J. Rosten 2024.                //
// Distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.0. //
//    (See accompanying file LICENSE.md or copy at                //
//          https://www.gnu.org/licenses/gpl-3.0.en.html)         //
////////////////////////////////////////////////////////////////////

#pragma once

#include "avocet/Preprocessor/Core/PreprocessorDefs.hpp"

#include <cstddef>

namespace avocet::opengl{
    struct opengl_version {
        std::size_t major{4}, minor{get_min_minor_version()};

        constexpr static std::size_t get_min_minor_version() noexcept { return avocet::is_windows() ? 6 : 1; }
    };

    [[nodiscard]]
    opengl_version get_opengl_version();
}