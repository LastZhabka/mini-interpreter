#include <memory>
#include <cassert>

#include "tree_module.h"
#include<iostream>



Expr::~Expr() = default;

std::vector<std::shared_ptr<Expr>> Expr::get_kids() {
    return target;
}

void Expr::push_back(std::shared_ptr<Expr> element) {
    target.push_back(element);
}

void Expr::modify(int index, std::shared_ptr<Expr> elem) {
    target[index] = elem;
}

void Expr::reassign_children(std::vector<std::shared_ptr<Expr>> target_) {
    target = target_;
}

// CONSTRUCTORS


Puts::Puts(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

ErrorExpr::ErrorExpr(std::string value) : value(value) { }

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

IntLiteral::IntLiteral(int value) : value(value) { }

FloatLiteral::FloatLiteral(float value) : value(value) { }

StringLiteral::StringLiteral(std::string value) : value(value) { }

BoolLiteral::BoolLiteral(bool value) : value(value) { }

NullLiteral::NullLiteral() { }

ParseTempExpr::ParseTempExpr(std::string parse_type) : parse_type(parse_type) { }

std::string ParseTempExpr::get_parse_type() {
    return parse_type;
}

// CREATOR i.e. FACTORY METHOD

ExprCreator::ExprCreator() = default;

std::shared_ptr<Expr> ExprCreator::operator()(std::string expr_type) {
    if (expr_type == "Keyword(add)") {
        return std::make_shared<Addition>(std::vector<std::shared_ptr<Expr>>(0));
    }
    else if (expr_type == "Keyword(subtract)") {
        return std::make_shared<Subtraction>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(multiply)") {
        return std::make_shared<Multiplication>(std::vector<std::shared_ptr<Expr>>(0));
    }
    else if (expr_type == "Keyword(divide)") {
        return std::make_shared<Division>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(gt)") {
        return std::make_shared<GreaterThan>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(lt)") {
        return std::make_shared<LowerThan>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(equal)") {
        return std::make_shared<Equal>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(not_equal)") {
        return std::make_shared<NotEqual>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(min)") {
        return std::make_shared<Min>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(abs)") {
        return std::make_shared<Abs>(nullptr);
    }
    else if (expr_type == "Keyword(set)") {
        return std::make_shared<Assignment>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(concat)") {
        return std::make_shared<Concatenation>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(replace)") {
        return std::make_shared<Replacement>(nullptr, nullptr, nullptr);
    }
    else if (expr_type == "Keyword(substring)") {
        return std::make_shared<Substring>(nullptr, nullptr, nullptr);
    }
    else if (expr_type == "Keyword(lowercase)") {
        return std::make_shared<Lowercase>(nullptr);
    }
    else if (expr_type == "Keyword(uppercase)") {
        return std::make_shared<Uppercase>(nullptr);
    }
    else if (expr_type == "Identifier") {
        return std::make_shared<Identifier>(nullptr); //??????????
    }
    else if (expr_type == "IntLit") {
        return std::make_shared<IntLiteral>(0);
    }
    else if (expr_type == "FloatLit") {
        return std::make_shared<FloatLiteral>(0);
    }
    else if (expr_type == "StringLit") {
        return std::make_shared<StringLiteral>("");
    }
    else if (expr_type == "BoolLit") {
        return std::make_shared<BoolLiteral>(false);
    }
    else if (expr_type == "NullLit") {
        return std::make_shared<NullLiteral>();
    }
    else if (expr_type == "Error") {
        return std::make_shared<ErrorExpr>("Dummy Error");
    }
    else if (expr_type == "Keyword") {
        return std::make_shared<ParseTempExpr>("");
    }
    else if (expr_type == "Space" || expr_type == "EOF" || expr_type == "ParseTempExpr" || expr_type.substr(0, 14) == "DelimiterToken") {
        return std::make_shared<ParseTempExpr>("");
    }
    else if (expr_type == "ParseTempExpr(Params)") {
        return std::make_shared<ParseTempExpr>("Params");
    }
    else if (expr_type == "ParseTempExpr(Params\')") {
        return std::make_shared<ParseTempExpr>("Params\'");
    }
    else if (expr_type == "ParseTempExpr(Literal)") {
        return std::make_shared<ParseTempExpr>("Literal");
    }
    else if (expr_type == "ParseTempExpr(Program)") {
        return std::make_shared<ParseTempExpr>("Program");
    }
    else if (expr_type == "ParseTempExpr(Program\')") {
        return std::make_shared<ParseTempExpr>("Program\'");
    }
    else if (expr_type == "ParseTempExpr(Expr)") {
        return std::make_shared<ParseTempExpr>("Expr");
    }
    else {
        std::cerr << expr_type << "\n";
        assert(0);
    }
}



// VISITOR

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

void ErrorExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}


void ParseTempExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    (visitor->visit(*this));
}


// Visitor

ExprVisitor::~ExprVisitor() = default;

void ExprVisitor::visit(Puts& expr) { }

void ExprVisitor::visit(Addition& expr) { }

void ExprVisitor::visit(Subtraction& expr) { }

void ExprVisitor::visit(Multiplication& expr) { }

void ExprVisitor::visit(Division& expr) { }

void ExprVisitor::visit(GreaterThan& expr) { }

void ExprVisitor::visit(LowerThan& expr) { }

void ExprVisitor::visit(Equal& expr) { }

void ExprVisitor::visit(NotEqual& expr) { }

void ExprVisitor::visit(Min& expr) { }

void ExprVisitor::visit(Abs& expr) { }

void ExprVisitor::visit(Assignment& expr) { }

void ExprVisitor::visit(Concatenation& expr) { }

void ExprVisitor::visit(Replacement& expr) { }

void ExprVisitor::visit(Substring& expr) { }

void ExprVisitor::visit(Lowercase& expr) { }

void ExprVisitor::visit(Uppercase& expr) { }

void ExprVisitor::visit(Identifier& expr) { }

void ExprVisitor::visit(IntLiteral& expr) { }

void ExprVisitor::visit(FloatLiteral& expr) { }

void ExprVisitor::visit(StringLiteral& expr) { }

void ExprVisitor::visit(BoolLiteral& expr) { }

void ExprVisitor::visit(NullLiteral& expr) { }

void ExprVisitor::visit(ErrorExpr& expr) { }

void ExprVisitor::visit(ParseTempExpr& expr) { }


void ParserTempTypeVisitor::visit(ParseTempExpr& expr) {
    last_type = "(" + expr.get_parse_type() + ")";
}
void ParserTempTypeVisitor::clear() {
    last_type = "";
}

std::string ParserTempTypeVisitor::get_type_of_visited_expr() {
    return last_type;
}