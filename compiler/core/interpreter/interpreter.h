#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <memory>
#include <map>
#include <variant>
#include "../ast/tree_module.h"
#include "../parser/parser.h"
#include "../lexer/lexer.h"


enum class Type {
    int_type,
    string_type,
    null_type,
    bool_type,
    float_type,
    error_type
};

using ValueType = std::variant<int, double, std::string, bool>;


class ReturnValue {
    private:
        Type type;
        ValueType data;
    public:
        ReturnValue();

        ReturnValue(int val);

        ReturnValue(float val);

        ReturnValue(std::string val);

        ReturnValue(bool val);

        int as_int() const;

        float as_float() const;
        
        std::string as_string() const;
        
        bool as_bool() const;

        Type get_type();
};

class SymbolTable {
    private:
        std::map<std::string, std::shared_ptr<ReturnValue>> symbol_table;
        
    public:
        void add(std::string var_name, std::shared_ptr<ReturnValue> value);

        std::shared_ptr<ReturnValue> get(std::string var_name);

        Type get_type(std::string var_name);
};

class Context {
    private:
        SymbolTable symbol_table;
    public:
        Context();

        void insert_var(std::string var_name, std::shared_ptr<ReturnValue> value);

        Type get_type(std::string var_name);

        std::shared_ptr<ReturnValue> get_val(std::string var_name);
};

class Printer {
    private:
        std::vector<std::string> output;
    public:
        void add_output(std::string text);

        void clear_buffer();

        std::string to_string();
};

class Interpreter { // static (?)
    private:
        Lexer lexer;

        Parser parser;
    public:
        Interpreter();

        ReturnValue evaluate(
            std::shared_ptr<Expr> expr_eval, 
            std::shared_ptr<Context> context, 
            std::shared_ptr<Printer> printer
        );

        std::string interpret(std::string input);
};

#endif //INTERPRETER_H