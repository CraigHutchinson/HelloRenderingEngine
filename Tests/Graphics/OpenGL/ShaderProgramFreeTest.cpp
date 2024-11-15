////////////////////////////////////////////////////////////////////
//                Copyright Oliver J. Rosten 2024.                //
// Distributed under the GNU GENERAL PUBLIC LICENSE, Version 3.0. //
//    (See accompanying file LICENSE.md or copy at                //
//          https://www.gnu.org/licenses/gpl-3.0.en.html)         //
////////////////////////////////////////////////////////////////////

/*! \file */

#include "ShaderProgramFreeTest.hpp"
#include "curlew/Window/GLFWWrappers.hpp"
#include "avocet/Graphics/OpenGL/ShaderProgram.hpp"

namespace avocet::testing
{
    [[nodiscard]]
    std::filesystem::path shader_program_free_test::source_file() const
    {
        return std::source_location::current().file_name();
    }

    void shader_program_free_test::run_tests()
    {
        using namespace curlew;
        glfw_manager manager{};
        auto w{manager.create_window({.hiding{window_hiding_mode::on}})};

        namespace agl = avocet::opengl;
        const auto shaderDir{working_materials()};

        check_filtered_exception_thrown<std::runtime_error>(
            "Missing Vertex Shader",
            [&shaderDir](){
                agl::shader_program sp{
                    shaderDir,
                    shaderDir / "Monochrome.fs"
                };
            }
        );

        check_filtered_exception_thrown<std::runtime_error>(
            "Misnamed Vertex Shader",
            [&shaderDir](){
                agl::shader_program sp{
                    shaderDir / "foo.vs",
                    shaderDir / "Monochrome.fs"
                };
            }
        );

        check_filtered_exception_thrown<std::runtime_error>(
            "Missing Fragment Shader",
            [&shaderDir](){
                agl::shader_program sp{
                    shaderDir / "Identity.vs",
                    shaderDir
                };
            }
        );

        check_filtered_exception_thrown<std::runtime_error>(
            "Misnamed Fragment Shader",
            [&shaderDir](){
                agl::shader_program sp{
                    shaderDir / "Identity.vs",
                    shaderDir / "bar.fs"
                };
            }
        );

        check_filtered_exception_thrown<std::runtime_error>(
            "Broken Vertex Shader",
            [&shaderDir](){
                agl::shader_program sp{
                    shaderDir / "Broken_Identity.vs",
                    shaderDir / "Monochrome.fs"
                };
            }
        );

        check_filtered_exception_thrown<std::runtime_error>(
            "Unlinkable Vertex Shader",
            [&shaderDir](){
                agl::shader_program sp{
                    shaderDir / "Unlinkable_Identity.vs",
                    shaderDir / "Monochrome.fs"
                };
            }
        );

        check_filtered_exception_thrown<std::runtime_error>(
            "Broken Fragment Shader",
            [&shaderDir](){
                agl::shader_program sp{
                    shaderDir / "Identity.vs",
                    shaderDir / "Broken_Monochrome.fs"
                };
            }
        );

        check_filtered_exception_thrown<std::runtime_error>(
            "Unlinkable Fragment Shader",
            [&shaderDir](){
                agl::shader_program sp{
                    shaderDir / "Identity.vs",
                    shaderDir / "Unlinkable_Monochrome.fs"
                };
            }
        );
    }
}
