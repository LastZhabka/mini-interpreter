#include "interpreter.h"
#include <cmath>


ReturnValue::ReturnValue() : type(Type::null_type), data(std::nanf("nan")) { }

ReturnValue::ReturnValue(int val) : type(Type::int_type), data(val) { }

ReturnValue::ReturnValue(bool val) : type(Type::bool_type), data(val) { }

ReturnValue::ReturnValue(float val) : type(Type::float_type), data(val) { }

ReturnValue::ReturnValue(std::string val) : type(Type::string_type), data(val) { }

int ReturnValue::as_int() const {
    return std::get<int>(data);
}

float ReturnValue::as_float() const {
    return std::get<float>(data);
}

std::string ReturnValue::as_string() const {
    return std::get<std::string>(data);
}

bool ReturnValue::as_bool() const {
    return std::get<bool>(data);
}

Type ReturnValue::get_type() {
    return type;
}


void SymbolTable::add(std::string var_name, std::shared_ptr<ReturnValue> value) {
    symbol_table[var_name] = value;
}

std::shared_ptr<ReturnValue> SymbolTable::get(std::string var_name) {
    if (!symbol_table.count(var_name)) {
        return nullptr;
    }
    return symbol_table[var_name];
}

Type SymbolTable::get_type(std::string var_name) {
    if (!symbol_table.count(var_name)) {
        return Type::error_type;
    }
    return symbol_table[var_name]->get_type();
}

Type get_type(std::string var_name);

/*
Quite useless context class.
*/
Context::Context() : symbol_table() {}

void Context::insert_var(std::string var_name, std::shared_ptr<ReturnValue> value) {
    symbol_table.add(var_name, value);
}

Type Context::get_type(std::string var_name) {
    return symbol_table.get_type(var_name);
}

std::shared_ptr<ReturnValue> Context::get_val(std::string var_name) {
    return symbol_table.get(var_name);
}

/*
Placeholder printer class, currently this class is quite useless
*/
void Printer::add_output(std::string text) {
    output.push_back(text);
}

void Printer::clear_buffer() {
    output.clear();
}

std::string Printer::to_string() {
    std::string result;
    for(auto text : output)
        result += text;
    return result;
}


Interpreter::Interpreter() : lexer(), parser() { }

ReturnValue Interpreter::evaluate(
    std::shared_ptr<Expr> expr_eval, 
    std::shared_ptr<Context> context, 
    std::shared_ptr<Printer> printer
) {
    // TODO
}

std::string Interpreter::interpret(std::string input) {
    
    std::shared_ptr<Context> context = std::make_shared<Context>();
    std::shared_ptr<Printer> printer = std::make_shared<Printer>();
    std::vector<std::shared_ptr<Token>> tokens = lexer.run(input);
    std::shared_ptr<Expr> ast_root = parser.parse(tokens);
    evaluate(ast_root, context, printer);
    return printer->to_string();
}

