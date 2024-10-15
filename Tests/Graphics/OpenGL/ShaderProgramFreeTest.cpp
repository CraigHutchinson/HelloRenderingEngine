////////////////////////////////////////////////////////////////////
//                Copyright Oliver J. Rosten 2024.                //
// Distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.0. //
//    (See accompanying file LICENSE.md or copy at                //
//          https://www.gnu.org/licenses/gpl-3.0.en.html)         //
////////////////////////////////////////////////////////////////////

/*! \file */

#include "ShaderProgramFreeTest.hpp"
#include "avocet/Graphics/OpenGL/ShaderProgram.hpp"

namespace sequoia::testing
{
    [[nodiscard]]
    std::filesystem::path shader_program_free_test::source_file() const
    {
        return std::source_location::current().file_name();
    }

    void shader_program_free_test::run_tests()
    {
        // e.g. check(equality, "Useful description", some_function(), 42);
    }
}
