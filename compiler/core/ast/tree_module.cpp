#include "tree_module.h"
#include <memory>


Expr::~Expr() = default;

void Expr::push_back(std::shared_ptr<Expr> element) {
    target.push_back(element);
}

Puts::Puts(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

Addition::Addition(std::vector<std::shared_ptr<Expr>> operands) {
    for (auto operand : operands)
        this->push_back(operand);
}  

Subtraction::Subtraction(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

Multiplication::Multiplication(std::vector<std::shared_ptr<Expr>> operands) {
    for (auto operand : operands)
        this->push_back(operand);
}  

Division::Division(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

GreaterThan::GreaterThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}


LowerThan::LowerThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

Equal::Equal(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

NotEqual::NotEqual(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

Min::Min(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

Abs::Abs(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

Assignment::Assignment(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

Concatenation::Concatenation(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

Replacement::Replacement(std::shared_ptr<Expr> source, std::shared_ptr<Expr> target, std::shared_ptr<Expr> replacement) {
    this->push_back(source);
    this->push_back(target);
    this->push_back(replacement);
}

Substring::Substring(std::shared_ptr<Expr> source, std::shared_ptr<Expr> l, std::shared_ptr<Expr> r) {
    this->push_back(source);
    this->push_back(l);
    this->push_back(r);
}

Lowercase::Lowercase(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

Uppercase::Uppercase(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

Identifier::Identifier(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

IntLiteral::IntLiteral(int value) : value(value) {

}


FloatLiteral::FloatLiteral(float value) : value(value) {

}


StringLiteral::StringLiteral(std::string value) : value(value) {

}

BoolLiteral::BoolLiteral(bool value) : value(value) {

}

NullLiteral::NullLiteral() { }

ParseTempExpr::ParseTempExpr() { }



void Puts::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Addition::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Subtraction::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Multiplication::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Division::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void GreaterThan::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void LowerThan::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Equal::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void NotEqual::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Min::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Abs::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Assignment::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Concatenation::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Replacement::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Substring::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Lowercase::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Uppercase::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void Identifier::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void IntLiteral::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void FloatLiteral::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void StringLiteral::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void BoolLiteral::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void NullLiteral::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

// #include "tree_module.h"
// #include <memory>

// Expr::Expr( ): expr_type(Type::unresolved) { }

// Type Expr::get_type() {
//     return this->expr_type;
// }


// Puts::Puts(std::shared_ptr<Expr> target) : target(target) { }

// //functions:

// Addition::Addition(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

// Subtraction::Subtraction(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

// Multiplication::Multiplication(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

// Division::Division(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

// GreaterThan::GreaterThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

// LowerThan::LowerThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

// Equal::Equal(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

// NotEqual::NotEqual(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

// Min::Min(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }

// Abs::Abs(std::shared_ptr<Expr> target) : target(target) { }

// Assignment::Assignment(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) : lhs(lhs), rhs(rhs) { }


// // string operations

// Substring::Substring(std::shared_ptr<Expr> source, std::shared_ptr<Expr> l, std::shared_ptr<Expr> r) : source(source), l(l), r(r) { }

// Lowercase::Lowercase(std::shared_ptr<Expr> target) : target(target) { }

// Uppercase::Uppercase(std::shared_ptr<Expr> target) : target(target) { }

// Identifier::Identifier(std::string name) : name(name) { }

// // Literals:

// IntLiteral::IntLiteral(int value) : value(value) { }

// Type IntLiteral::get_type() {
//     return Type::int_type;
// }

// int IntLiteral::get_value() {
//     return value;
// }

// FloatLiteral::FloatLiteral(float value) : value(value) { }

// Type FloatLiteral::get_type() {
//     return Type::float_type;
// }

// float FloatLiteral::get_value() {
//     return value;
// }

// StringLiteral::StringLiteral(std::string value) : value(value) { }

// Type StringLiteral::get_type() {
//     return Type::string_type;
// }

// std::string StringLiteral::get_value() {
//     return value;
// }

// BoolLiteral::BoolLiteral(bool value) : value(value) { }

// Type BoolLiteral::get_type() {
//     return Type::bool_type;
// }

// bool BoolLiteral::get_value() {
//     return value;
// }

// NullLiteral::NullLiteral() { }

// Type NullLiteral::get_type() {
//     return Type::null_type;
// }

