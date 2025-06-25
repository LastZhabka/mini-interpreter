#include "tree_module.h"
#include <memory>

Expr::Expr( ): expr_type(Type::unresolved) { }

Type Expr::get_type() {
    return this->expr_type;
}


Puts::Puts(std::shared_ptr<Expr> target) : target(target) { }

//functions:

Addition::Addition(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

Subtraction::Subtraction(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

Multiplication::Multiplication(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

Division::Division(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

GreaterThan::GreaterThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

LowerThan::LowerThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

Equal::Equal(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

NotEqual::NotEqual(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

Min::Min(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

Abs::Abs(std::shared_ptr<Expr> target) : target(target) { }

Assignment::Assignment(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }


// string operations

Substring::Substring(std::shared_ptr<Expr> source, std::shared_ptr<Expr> l, std::shared_ptr<Expr> r) : source(source), l(l), r(r) { }

Lowercase::Lowercase(std::shared_ptr<Expr> target) : target(target) { }

Uppercase::Uppercase(std::shared_ptr<Expr> target) : target(target) { }

Identifier::Identifier(std::string name) : name(name) { }

// Literals:

IntLiteral::IntLiteral(int value) : value(value) { }

Type IntLiteral::get_type() {
    return Type::int_type;
}

int IntLiteral::get_value() {
    return value;
}

FloatLiteral::FloatLiteral(float value) : value(value) { }

Type FloatLiteral::get_type() {
    return Type::float_type;
}

float FloatLiteral::get_value() {
    return value;
}

StringLiteral::StringLiteral(std::string value) : value(value) { }

Type StringLiteral::get_type() {
    return Type::string_type;
}

std::string StringLiteral::get_value() {
    return value;
}

BoolLiteral::BoolLiteral(bool value) : value(value) { }

Type BoolLiteral::get_type() {
    return Type::bool_type;
}

bool BoolLiteral::get_value() {
    return value;
}

NullLiteral::NullLiteral() { }

Type NullLiteral::get_type() {
    return Type::null_type;
}

