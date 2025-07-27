#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() function
#include <vector>
#include <utility>
#include <memory>
#include <fstream>

#include "../external/catch2/catch_amalgamated.hpp"
#include "../external/nlohman/json.hpp"
#include "../src/core/lexer/lexer.h"
#include "../src/core/interpreter/interpreter.h"

using json = nlohmann::json;

std::vector<std::vector<std::string>> read_all_test_data(std::string test_group_name) {
    std::ifstream file_stream("tests/tests_input.json");
    json jsonData;
    file_stream >> jsonData;
    std::vector<std::vector<std::string>> tests;
    for (auto &[name, data] : jsonData.items()) {
        tests.push_back({
            data["in"].get<std::string>(),
            data[test_group_name + "_out"].get<std::string>(),
        });
    }

    return tests;
}

std::string run_lexer(const std::string& input) {
    Lexer lexer = Lexer();
    std::string output;
    for (auto &token : lexer.run(input)) {
        output += (token->to_string() + " ");
    }
    return output;
}

std::string run_interpreter(const std::string& input) {
    return Interpreter().interpret(input);
}

TEST_CASE("Lexer test on all test cases", "[lexer]") {
    std::vector<std::vector<std::string>> tests = read_all_test_data("lexer");
    for (auto &test : tests) {
        REQUIRE(run_lexer(test[0]) == test[1]);
    }
}

TEST_CASE("Interpreter test on all test cases", "[interpreter]") {
    std::vector<std::vector<std::string>> tests = read_all_test_data("interpreter");
    for (auto &test : tests) {
        REQUIRE(run_interpreter(test[0]) == test[1]);
    }
}