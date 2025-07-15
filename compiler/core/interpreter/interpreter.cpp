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

std::shared_ptr<ReturnValue> Interpreter::evaluate(
    std::shared_ptr<Expr> expr, 
    std::shared_ptr<Context> context, 
    std::shared_ptr<Printer> printer
) {
    std::shared_ptr<ExprTypeVisitor> expr_type_visitor;
    std::string type = expr_type_visitor->get_type(expr, expr_type_visitor);
    std::vector<std::shared_ptr<Expr>> args = expr->get_kids();
    std::vector<std::shared_ptr<ReturnValue>> sub_expr_vals;
    for(auto sub_expr : args)
        sub_expr_vals.push_back(this->evaluate(sub_expr, context, printer));

    if (type == "PutsExpr") {
        assert(sub_expr_vals.size() == 1);
        assert(sub_expr_vals[0]->get_type() == Type::string_type);
        printer->add_output(sub_expr_vals[0]->as_string());
        return std::make_shared<ReturnValue>();
    }
    else if(type == "ToStrExpr") {
        assert(sub_expr_vals.size() == 1);
        if (sub_expr_vals[0]->get_type() == Type::int_type) {
            return std::make_shared<ReturnValue>(
                std::to_string(sub_expr_vals[0]->as_int())
            );
        }
        else if (sub_expr_vals[0]->get_type() == Type::float_type) {
            return std::make_shared<ReturnValue>(
                std::to_string(sub_expr_vals[0]->as_float())
            );
        }
        else if (sub_expr_vals[0]->get_type() == Type::bool_type) {
            return std::make_shared<ReturnValue>(
                sub_expr_vals[0]->as_bool() == true ? "true" : "false" 
            );
        }
        else if (sub_expr_vals[0]->get_type() == Type::string_type) {
            return sub_expr_vals[0];
        }
        else if (sub_expr_vals[0]->get_type() == Type::null_type) {
            return std::make_shared<ReturnValue>(
                "null"
            ); 
        }
    }
    else if(type == "AdditionExpr") {
        assert(sub_expr_vals.size() != 0);
        Type resultant_type = Type::int_type;
        for(auto val : sub_expr_vals) {
            if (val->get_type() == Type::float_type)
                resultant_type = Type::float_type;
            
            assert(
                val->get_type() == Type::float_type || 
                val->get_type() == Type::int_type
            );
        }
        if (resultant_type == Type::float_type) {
            float result = 0;
            for(auto val : sub_expr_vals) {
                result += (val->get_type() == Type::int_type ? val->as_int() : val->as_float());
            }
            return std::make_shared<ReturnValue>((float)result);            
        }
        else if (resultant_type == Type::int_type) {
            int result = 0;
            for(auto val : sub_expr_vals) {
                result += val->as_int();
            }
            return std::make_shared<ReturnValue>((int)result);
        }
    }
    else if(type == "SubtractionExpr") {
        assert(sub_expr_vals.size() == 2);
        Type resultant_type = Type::int_type;
        for(auto val : sub_expr_vals) {
            if (val->get_type() == Type::float_type)
                resultant_type = Type::float_type;
            
            assert(
                val->get_type() == Type::float_type || 
                val->get_type() == Type::int_type
            );
        }
        if (resultant_type == Type::float_type) {
            float result = 0;
            int id = 0;
            for(auto val : sub_expr_vals) {
                result += (id == 0 ? 1 : -1) * (val->get_type() == Type::int_type ? val->as_int() : val->as_float());
                id += 1;
            }
            return std::make_shared<ReturnValue>((float)(result));            
        }
        else if (resultant_type == Type::int_type) {
            int result = 0, id = 0;
            for(auto val : sub_expr_vals) {
                result += (id == 0 ? 1 : -1) * val->as_int();
                id += 1;
            }
            return std::make_shared<ReturnValue>((int)result);
        }
    }
    else if(type == "MultiplicationExpr") {
        assert(sub_expr_vals.size() != 0);
        Type resultant_type = Type::int_type;
        for(auto val : sub_expr_vals) {
            if (val->get_type() == Type::float_type)
                resultant_type = Type::float_type;
            
            assert(
                val->get_type() == Type::float_type || 
                val->get_type() == Type::int_type
            );
        }
        if (resultant_type == Type::float_type) {
            float result = 1.0;
            for(auto val : sub_expr_vals) {
                result *= (val->get_type() == Type::int_type ? val->as_int() : val->as_float());
            }
            return std::make_shared<ReturnValue>((float)result);            
        }
        else if (resultant_type == Type::int_type) {
            int result = 1;
            for(auto val : sub_expr_vals) {
                result *= val->as_int();
            }
            return std::make_shared<ReturnValue>((int)result);
        }
    }
    else if(type == "DivisionExpr") {
        assert(sub_expr_vals.size() == 2);
        Type resultant_type = Type::int_type;
        for(auto val : sub_expr_vals) {
            if (val->get_type() == Type::float_type)
                resultant_type = Type::float_type;
            
            assert(
                val->get_type() == Type::float_type || 
                val->get_type() == Type::int_type
            );
        }
        std::shared_ptr<ReturnValue> opr1 = sub_expr_vals[0];
        std::shared_ptr<ReturnValue> opr2 = sub_expr_vals[1];
        if (resultant_type == Type::float_type) {
            float a = (opr1->get_type() == Type::float_type ? opr1->as_float() : opr1->as_int());
            float b = (opr2->get_type() == Type::float_type ? opr2->as_float() : opr2->as_int());
            return std::make_shared<ReturnValue>((float)(a / b));
        } 
        else if (resultant_type == Type::int_type) {
            int a = (opr1->get_type() == Type::float_type ? opr1->as_float() : opr1->as_int());
            int b = (opr2->get_type() == Type::float_type ? opr2->as_float() : opr2->as_int());
            assert(b != 0);
            return std::make_shared<ReturnValue>((int)(a / b));
        }
    }
}

std::string Interpreter::interpret(std::string input) {
    
    std::shared_ptr<Context> context = std::make_shared<Context>();
    std::shared_ptr<Printer> printer = std::make_shared<Printer>();
    std::vector<std::shared_ptr<Token>> tokens = lexer.run(input);
    std::shared_ptr<Expr> ast_root = parser.parse(tokens);
    evaluate(ast_root, context, printer);
    return printer->to_string();
}

