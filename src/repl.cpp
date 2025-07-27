#include "core/interpreter/interpreter.h"

int main() {
    std::string input;
    Interpreter interpreter;
    std::shared_ptr<Context> context = std::make_shared<Context>();
    std::shared_ptr<Printer> printer = std::make_shared<Printer>();

    while (std::getline(std::cin, input)) {
        interpreter.repl_iteration(input, context, printer);
    }
}