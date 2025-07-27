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

float ReturnValue::as_numerical() const {
    assert(type == Type::float_type || type == Type::int_type);
    if (type == Type::float_type)
        return this->as_float();
    return this->as_int();
}

bool ReturnValue::is_numerical() const {
    return (type == Type::float_type || type == Type::int_type);
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
    output.push_back(text + "\n");
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
    std::shared_ptr<ExprTypeVisitor> expr_type_visitor = std::make_shared<ExprTypeVisitor>();
    std::string type = expr_type_visitor->get_type(expr, expr_type_visitor);
    std::vector<std::shared_ptr<Expr>> args = expr->get_kids();
    std::vector<std::shared_ptr<ReturnValue>> args_val;
    if(type == "SetExpr") {
        assert(args.size() == 2);
        std::shared_ptr<IdentifierExpr> var = std::dynamic_pointer_cast<IdentifierExpr>(args[0]);
        context->insert_var(var->get_name(), this->evaluate(args[1], context, printer));
        return std::make_shared<ReturnValue>();
    }
    for(auto arg : args)
        args_val.push_back(this->evaluate(arg, context, printer));

    if (type == "PutsExpr") {
        assert(args_val.size() == 1);
        assert(args_val[0]->get_type() == Type::string_type);
        printer->add_output(args_val[0]->as_string());
        return std::make_shared<ReturnValue>();
    }
    else if(type == "ToStrExpr") {
        assert(args_val.size() == 1);
        if (args_val[0]->get_type() == Type::int_type) {
            return std::make_shared<ReturnValue>(
                std::to_string(args_val[0]->as_int())
            );
        }
        else if (args_val[0]->get_type() == Type::float_type) {
            std::string str_repr = std::to_string(args_val[0]->as_float());
            str_repr = str_repr.substr(0, str_repr.find(".") + 5);
            return std::make_shared<ReturnValue>(str_repr);
        }
        else if (args_val[0]->get_type() == Type::bool_type) {
            std::string bool_to_str = (args_val[0]->as_bool() == true ? "true" : "false");
            return std::make_shared<ReturnValue>(bool_to_str);
        }
        else if (args_val[0]->get_type() == Type::string_type) {
            return args_val[0];
        }
        else if (args_val[0]->get_type() == Type::null_type) {
            return std::make_shared<ReturnValue>(
                std::string("null")
            ); 
        }
    }
    else if(type == "AdditionExpr") {
        assert(args_val.size() != 0);
        Type resultant_type = Type::int_type;
        float result = 0;
        for(auto val : args_val) {
            Type v_type = val->get_type();
            assert(v_type == Type::float_type || v_type == Type::int_type);
            if (v_type == Type::float_type)
                resultant_type = Type::float_type;
            result += val->as_numerical();
        }
        if (resultant_type == Type::int_type) {
            int result_ = result;
            return std::make_shared<ReturnValue>(result_); 
        }
        return std::make_shared<ReturnValue>(result);
    }
    else if(type == "SubtractionExpr") {
        assert(args_val.size() == 2);
        Type resultant_type = Type::int_type;
        for(auto val : args_val) {
            Type v_type = val->get_type();
            assert(v_type == Type::float_type || v_type == Type::int_type);
            if (v_type == Type::float_type)
                resultant_type = Type::float_type;
        }
        float result = args_val[0]->as_numerical() - args_val[1]->as_numerical();
        if (resultant_type == Type::int_type) {
            int result_ = result;
            return std::make_shared<ReturnValue>(result_); 
        }
        return std::make_shared<ReturnValue>(result);
    }
    else if(type == "MultiplicationExpr") {
        assert(args_val.size() != 0);
        Type resultant_type = Type::int_type;
        float result = 1.0;
        for(auto val : args_val) {
            Type v_type = val->get_type();
            assert(v_type == Type::float_type || v_type == Type::int_type);
            if (v_type == Type::float_type)
                resultant_type = Type::float_type;
            result *= val->as_numerical();
        }
        if (resultant_type == Type::int_type) {
            int result_ = result;
            return std::make_shared<ReturnValue>(result_); 
        }
        return std::make_shared<ReturnValue>(result);
    }
    else if(type == "DivisionExpr") {
        assert(args_val.size() == 2);
        Type resultant_type = Type::int_type;
        for(auto val : args_val) {
            Type v_type = val->get_type();
            assert(v_type == Type::float_type || v_type == Type::int_type);
            if (v_type == Type::float_type)
                resultant_type = Type::float_type;
        }
        assert(fabs(args_val[1]->as_numerical()) >= 0.0000001);
        float result = args_val[0]->as_numerical() / args_val[1]->as_numerical();
        if (resultant_type == Type::int_type) {
            int result_ = result;
            return std::make_shared<ReturnValue>(result_); 
        }
        return std::make_shared<ReturnValue>(result);
    }
    else if(type == "GreaterThanExpr") {
        assert(args_val.size() == 2);
        for(auto val : args_val) {
            Type v_type = val->get_type();
            assert(v_type == Type::float_type || v_type == Type::int_type);
        }
        bool result = args_val[0]->as_numerical() > args_val[1]->as_numerical();
        return std::make_shared<ReturnValue>((bool)(result));
    }
    else if(type == "LowerThanExpr") {
        assert(args_val.size() == 2);
        for(auto val : args_val) {
            Type v_type = val->get_type();
            assert(v_type == Type::float_type || v_type == Type::int_type);
        }
        bool result = args_val[0]->as_numerical() < args_val[1]->as_numerical();
        return std::make_shared<ReturnValue>((bool)(result));
    }
    else if(type == "EqualExpr") {
        assert(args_val.size() == 2);
        std::shared_ptr<ReturnValue> left_operand = args_val[0];
        std::shared_ptr<ReturnValue> right_operand = args_val[1];
        bool result = false;
        if (left_operand->is_numerical() && right_operand->is_numerical()) {
            result = (fabs(left_operand->as_numerical() - right_operand->as_numerical()) < 0.000001);
        }
        else if (left_operand->get_type() == right_operand->get_type()) {
            if (left_operand->get_type() == Type::string_type) {
                result = (left_operand->as_string() == right_operand->as_string());
            }
            else if(left_operand->get_type() == Type::null_type) {
                result = true;
            }
            else if(left_operand->get_type() == Type::bool_type) {
                result = (left_operand->as_bool() == right_operand->as_bool());
            }
            else {
                assert(0); 
            }
        }
        else {
            result = false;
        }
        return std::make_shared<ReturnValue>((bool)(result));
    }
    else if(type == "NotEqualExpr") {
        assert(args_val.size() == 2);
        std::shared_ptr<ReturnValue> left_operand = args_val[0];
        std::shared_ptr<ReturnValue> right_operand = args_val[1];
        bool result = false;
        if (left_operand->is_numerical() && right_operand->is_numerical()) {
            result = (fabs(left_operand->as_numerical() - right_operand->as_numerical()) < 0.000001);
        }
        else if (left_operand->get_type() == right_operand->get_type()) {
            if (left_operand->get_type() == Type::string_type) {
                result = (left_operand->as_string() == right_operand->as_string());
            }
            else if(left_operand->get_type() == Type::null_type) {
                result = true;
            }
            else if(left_operand->get_type() == Type::bool_type) {
                result = (left_operand->as_bool() == right_operand->as_bool());
            }
            else {
                assert(0); 
            }
        }
        else {
            result = false;
        }
        return std::make_shared<ReturnValue>((bool)(!result));        
    }
    else if(type == "MinExpr") {
        assert(args_val.size() > 0);
        Type resultant_type = Type::int_type;
        float result = 2e9;
        for(auto val : args_val) {
            Type v_type = val->get_type();
            assert(v_type == Type::float_type || v_type == Type::int_type);
            if (v_type == Type::float_type)
                resultant_type = Type::float_type;
            result = std::min(result, val->as_numerical());
        }
        if (resultant_type == Type::int_type) {
            int result_ = result;
            return std::make_shared<ReturnValue>(result_); 
        }
        return std::make_shared<ReturnValue>(result);
    }
    else if(type == "MaxExpr") {
        assert(args_val.size() > 0);
        Type resultant_type = Type::int_type;
        float result = -2e9;
        for(auto val : args_val) {
            Type v_type = val->get_type();
            assert(v_type == Type::float_type || v_type == Type::int_type);
            if (v_type == Type::float_type)
                resultant_type = Type::float_type;
            result = std::max(result, val->as_numerical());
        }
        if (resultant_type == Type::int_type) {
            int result_ = result;
            return std::make_shared<ReturnValue>(result_); 
        }
        return std::make_shared<ReturnValue>(result);   
    }
    else if(type == "AbsExpr") {
        assert(args_val.size() == 1);
        std::shared_ptr<ReturnValue> operand = args_val[0];
        Type resultant_type = Type::int_type;
        for(auto val : args_val) {
            assert(val->is_numerical());
            if (val->get_type() == Type::float_type)
                resultant_type = Type::float_type;
        }
        float result = std::fabs(operand->as_numerical());
        if (resultant_type == Type::int_type) {
            int result_ = result;
            return std::make_shared<ReturnValue>(result_); 
        }
        return std::make_shared<ReturnValue>(result);      
    } 
    else if(type == "ConcatenationExpr") {
        assert(args_val.size() == 2);
        std::shared_ptr<ReturnValue> left_operand = args_val[0];
        std::shared_ptr<ReturnValue> right_operand = args_val[1];
        assert(left_operand->get_type() == Type::string_type);
        assert(right_operand->get_type() == Type::string_type);
        std::string result = left_operand->as_string() + right_operand->as_string();
        return std::make_shared<ReturnValue>(result);  
    }
    else if(type == "ReplacementExpr") {
        assert(args_val.size() == 3);
        std::shared_ptr<ReturnValue> target = args_val[0];
        std::shared_ptr<ReturnValue> replaced = args_val[1];
        std::shared_ptr<ReturnValue> replacement = args_val[2];
        assert(target->get_type() == Type::string_type);
        assert(replaced->get_type() == Type::string_type);
        assert(replacement->get_type() == Type::string_type);
        std::string target_str = target->as_string(), replaced_str = replaced->as_string();
        std::string replacement_str = replacement->as_string();        
        std::string result;
        for(int i = 0; i < target->as_string().size();) {
            if(target_str.substr(i, replaced_str.size()) == replaced_str) {
                result += replacement_str;
                i += replaced_str.size();
            }
            else {
                result += target_str[i];
                i++;
            }
        }
        return std::make_shared<ReturnValue>(result); 
    }
    else if(type == "SubstringExpr") {
        assert(args_val.size() == 3);
        std::shared_ptr<ReturnValue> target = args_val[0];
        std::shared_ptr<ReturnValue> left_pos = args_val[1];
        std::shared_ptr<ReturnValue> right_pos = args_val[2];
        assert(target->get_type() == Type::string_type);
        assert(left_pos->get_type() == Type::int_type);
        assert(right_pos->get_type() == Type::int_type);
        std::string result = target->as_string().substr(left_pos->as_int(), right_pos->as_int() - left_pos->as_int());
        return std::make_shared<ReturnValue>(result);   
    }
    else if(type == "LowercaseExpr") {
        assert(args_val.size() == 1);
        std::shared_ptr<ReturnValue> target = args_val[0];
        assert(target->get_type() == Type::string_type);
        std::string result;
        for(auto u : target->as_string()) {
            result += std::tolower(u);
        }
        return std::make_shared<ReturnValue>(result);     
    }
    else if(type == "UppercaseExpr") {
        assert(args_val.size() == 1);
        std::shared_ptr<ReturnValue> target = args_val[0];
        assert(target->get_type() == Type::string_type);
        std::string result;
        for(auto u : target->as_string()) {
            result += std::toupper(u);
        }
        return std::make_shared<ReturnValue>(result);
    }
    else if(type == "IntLiteralExpr") {
        std::shared_ptr<IntLiteral> int_expr = std::dynamic_pointer_cast<IntLiteral>(expr);
        return std::make_shared<ReturnValue>((int)(int_expr->get_value()));
    }
    else if(type == "FloatLiteralExpr") {
        std::shared_ptr<FloatLiteral> float_expr = std::dynamic_pointer_cast<FloatLiteral>(expr);
        return std::make_shared<ReturnValue>((float)(float_expr->get_value()));
    }
    else if(type == "StringLiteralExpr") {    
        std::shared_ptr<StringLiteral> string_expr = std::dynamic_pointer_cast<StringLiteral>(expr);
        return std::make_shared<ReturnValue>(string_expr->get_value());
    }
    else if(type == "BoolLiteralExpr") {
        std::shared_ptr<BoolLiteral> bool_expr = std::dynamic_pointer_cast<BoolLiteral>(expr);
        return std::make_shared<ReturnValue>((bool)(bool_expr->get_value()));       
    }
    else if(type == "NullLiteralExpr") {
        return std::make_shared<ReturnValue>();
    }  
    else if(type == "IdentifierExpr") {
        std::shared_ptr<IdentifierExpr> var = std::dynamic_pointer_cast<IdentifierExpr>(expr);
        return context->get_val(var->get_name());
    } 
    else if(type == "ErrorExpr") {
        assert(0);
    }
    else if(type == "ParseTempExpr") {
        return std::make_shared<ReturnValue>();
    }             
    assert(0);
}

std::string Interpreter::interpret(std::string input) {
    std::shared_ptr<Context> context = std::make_shared<Context>();
    std::shared_ptr<Printer> printer = std::make_shared<Printer>();
    std::vector<std::shared_ptr<Token>> tokens = lexer.run(input);
    std::shared_ptr<Expr> ast_root = parser.parse(tokens);
    evaluate(ast_root, context, printer);
    return printer->to_string();
}

void Interpreter::repl_iteration(std::string input, std::shared_ptr<Context> context, std::shared_ptr<Printer> printer) {
    std::vector<std::shared_ptr<Token>> tokens = lexer.run(input);
    std::shared_ptr<Expr> ast_root = parser.parse(tokens);
    evaluate(ast_root, context, printer);
    std::cout << printer->to_string();
    printer->clear_buffer();
}

