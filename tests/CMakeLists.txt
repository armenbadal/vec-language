enable_language(CXX)

find_package(Catch2 3 QUIET)
if(NOT Catch2_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.15.3
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(Catch2)
endif()

add_executable(vec_syntax_tests syntax_tests.cpp)
target_compile_features(vec_syntax_tests PRIVATE cxx_std_17)
target_compile_definitions(vec_syntax_tests PRIVATE
    VEC_EXECUTABLE="$<TARGET_FILE:${PROJECT_NAME}>"
    VEC_TEST_EXAMPLES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/examples"
)
target_link_libraries(vec_syntax_tests PRIVATE Catch2::Catch2WithMain)
add_dependencies(vec_syntax_tests ${PROJECT_NAME})

include(Catch)
catch_discover_tests(vec_syntax_tests)
