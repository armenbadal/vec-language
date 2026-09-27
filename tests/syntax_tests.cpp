#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>

namespace {

namespace fs = std::filesystem;

std::string shell_quote(const std::string &value)
{
    std::string result = "'";
    for (char character : value) {
        if (character == '\'')
            result += "'\\''";
        else
            result += character;
    }
    result += "'";
    return result;
}

std::vector<fs::path> example_files()
{
    std::vector<fs::path> files;
    for (const auto &entry : fs::directory_iterator(VEC_TEST_EXAMPLES_DIR)) {
        if (entry.is_regular_file() && entry.path().extension() == ".vl")
            files.push_back(entry.path());
    }
    std::sort(files.begin(), files.end());
    return files;
}

int parse(const fs::path &input)
{
    const std::string command = shell_quote(VEC_EXECUTABLE) + " < "
        + shell_quote(input.string()) + " > /dev/null 2>&1";
    return std::system(command.c_str());
}

} // namespace

TEST_CASE("syntax examples have their expected result", "[syntax]")
{
    const auto files = example_files();
    REQUIRE_FALSE(files.empty());

    for (const auto &file : files) {
        DYNAMIC_SECTION(file.filename().string()) {
            const std::string name = file.filename().string();
            const bool should_parse = name.rfind("valid_", 0) == 0;
            const bool should_fail = name.rfind("invalid_", 0) == 0;

            REQUIRE((should_parse || should_fail));
            if (should_parse)
                REQUIRE(parse(file) == 0);
            else
                REQUIRE(parse(file) != 0);
        }
    }
}
