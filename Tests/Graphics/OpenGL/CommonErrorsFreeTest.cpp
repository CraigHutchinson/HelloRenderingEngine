////////////////////////////////////////////////////////////////////
//                Copyright Oliver J. Rosten 2024.                //
// Distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.0. //
//    (See accompanying file LICENSE.md or copy at                //
//          https://www.gnu.org/licenses/gpl-3.0.en.html)         //
////////////////////////////////////////////////////////////////////

/*! \file */

#include "CommonErrorsFreeTest.hpp"

#include "curlew/Window/GLFWWrappers.hpp"
#include "avocet/Graphics/OpenGL/GLFunction.hpp"

#include "glad/gl.h"

namespace avocet::testing
{
    [[nodiscard]]
    std::filesystem::path common_errors_free_test::source_file() const
    {
        return std::source_location::current().file_name();
    }

    void common_errors_free_test::run_tests()
    {
        namespace agl = avocet::opengl;
        using namespace curlew;

        check_filtered_exception_thrown<std::runtime_error>(
	    reporter{"Constructing gl_function with a null pointer"},
            [](){
                gl_breaker breaker{glGetError};
                return agl::gl_function{agl::unchecked_debug_output, glGetError}();
            }
        );

        check_filtered_exception_thrown<std::runtime_error>(
	    reporter{"Null glGetError when checking for basic errors"},
            [](){
                gl_breaker breaker{glGetError};
                agl::check_for_basic_errors(std::source_location::current());
            }
        );
    }
}
