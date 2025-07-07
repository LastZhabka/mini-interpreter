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


void Expr::visualize(int tabs) {
    std::shared_ptr<ToStringVisitor> to_string_visitor = std::make_shared<ToStringVisitor>();
    this->accept(to_string_visitor);
    std::string result;
    for(int j = 0; j < tabs; j++)
        result += "|    ";
    result += to_string_visitor->get_result_of_visited_expr();
    std::cout << result << "\n";
    for(auto kid : this->get_kids()) {
        kid->visualize(tabs + 1);
    }
}


// CONSTRUCTORS


PutsExpr::PutsExpr(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

ToStrExpr::ToStrExpr(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

ErrorExpr::ErrorExpr(std::string value) : value(value) { }

std::string ErrorExpr::get_value() {
    return value;
}

AdditionExpr::AdditionExpr(std::vector<std::shared_ptr<Expr>> operands) {
    for (auto operand : operands)
        this->push_back(operand);
}  

SubtractionExpr::SubtractionExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

MultiplicationExpr::MultiplicationExpr(std::vector<std::shared_ptr<Expr>> operands) {
    for (auto operand : operands)
        this->push_back(operand);
}  

DivisionExpr::DivisionExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

GreaterThanExpr::GreaterThanExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

LowerThanExpr::LowerThanExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

EqualExpr::EqualExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

NotEqualExpr::NotEqualExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

MinExpr::MinExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

MaxExpr::MaxExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

AbsExpr::AbsExpr(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

SetExpr::SetExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

ConcatExpr::ConcatExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs) {
    this->push_back(lhs);
    this->push_back(rhs);
}

ReplaceExpr::ReplaceExpr(std::shared_ptr<Expr> source, std::shared_ptr<Expr> target, std::shared_ptr<Expr> replacement) {
    this->push_back(source);
    this->push_back(target);
    this->push_back(replacement);
}

SubstrExpr::SubstrExpr(std::shared_ptr<Expr> source, std::shared_ptr<Expr> l, std::shared_ptr<Expr> r) {
    this->push_back(source);
    this->push_back(l);
    this->push_back(r);
}

LowercaseExpr::LowercaseExpr(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

UppercaseExpr::UppercaseExpr(std::shared_ptr<Expr> target) {
    this->push_back(target);
}

IdentifierExpr::IdentifierExpr(std::string name) : name(name) { }

std::string IdentifierExpr::get_name() {
    return name;
}

IntLiteral::IntLiteral(int value) : value(value) { }

int IntLiteral::get_value() {
    return value;
}

FloatLiteral::FloatLiteral(float value) : value(value) { }

float FloatLiteral::get_value() {
    return value;
}

StringLiteral::StringLiteral(std::string value) : value(value) { }

std::string StringLiteral::get_value() {
    return value;
}

BoolLiteral::BoolLiteral(bool value) : value(value) { }

bool BoolLiteral::get_value() {
    return value;
}

NullLiteral::NullLiteral() { }

ParseTempExpr::ParseTempExpr(std::string parse_type) : parse_type(parse_type) { }

std::string ParseTempExpr::get_parse_type() {
    return parse_type;
}

// CREATOR i.e. FACTORY METHOD

ExprCreator::ExprCreator() = default;

std::shared_ptr<Expr> ExprCreator::operator()(std::string expr_type) {
    if (expr_type == "Keyword(add)") {
        return std::make_shared<AdditionExpr>(std::vector<std::shared_ptr<Expr>>(0));
    }
    else if (expr_type == "Keyword(puts)") {
        return std::make_shared<PutsExpr>(nullptr);
    }
    else if (expr_type == "Keyword(str)") {
        return std::make_shared<ToStrExpr>(nullptr);
    }    
    else if (expr_type == "Keyword(subtract)") {
        return std::make_shared<SubtractionExpr>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(multiply)") {
        return std::make_shared<MultiplicationExpr>(std::vector<std::shared_ptr<Expr>>(0));
    }
    else if (expr_type == "Keyword(divide)") {
        return std::make_shared<DivisionExpr>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(gt)") {
        return std::make_shared<GreaterThanExpr>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(lt)") {
        return std::make_shared<LowerThanExpr>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(equal)") {
        return std::make_shared<EqualExpr>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(not_equal)") {
        return std::make_shared<NotEqualExpr>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(min)") {
        return std::make_shared<MinExpr>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(max)") {
        return std::make_shared<MaxExpr>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(abs)") {
        return std::make_shared<AbsExpr>(nullptr);
    }
    else if (expr_type == "Keyword(set)") {
        return std::make_shared<SetExpr>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(concat)") {
        return std::make_shared<ConcatExpr>(nullptr, nullptr);
    }
    else if (expr_type == "Keyword(replace)") {
        return std::make_shared<ReplaceExpr>(nullptr, nullptr, nullptr);
    }
    else if (expr_type == "Keyword(substring)") {
        return std::make_shared<SubstrExpr>(nullptr, nullptr, nullptr);
    }
    else if (expr_type == "Keyword(lowercase)") {
        return std::make_shared<LowercaseExpr>(nullptr);
    }
    else if (expr_type == "Keyword(uppercase)") {
        return std::make_shared<UppercaseExpr>(nullptr);
    }
    else if (expr_type == "Identifier") {
        return std::make_shared<IdentifierExpr>(""); 
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

void PutsExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void ToStrExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void AdditionExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void SubtractionExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void MultiplicationExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void DivisionExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void GreaterThanExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void LowerThanExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void EqualExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void NotEqualExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void MinExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void MaxExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void AbsExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void SetExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void ConcatExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void ReplaceExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void SubstrExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void LowercaseExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void UppercaseExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
    visitor->visit(*this);
}

void IdentifierExpr::accept(std::shared_ptr<ExprVisitor> visitor) {
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

void ExprVisitor::visit(PutsExpr& expr) { }

void ExprVisitor::visit(ToStrExpr& expr) { }

void ExprVisitor::visit(AdditionExpr& expr) { }

void ExprVisitor::visit(SubtractionExpr& expr) { }

void ExprVisitor::visit(MultiplicationExpr& expr) { }

void ExprVisitor::visit(DivisionExpr& expr) { }

void ExprVisitor::visit(GreaterThanExpr& expr) { }

void ExprVisitor::visit(LowerThanExpr& expr) { }

void ExprVisitor::visit(EqualExpr& expr) { }

void ExprVisitor::visit(NotEqualExpr& expr) { }

void ExprVisitor::visit(MinExpr& expr) { }

void ExprVisitor::visit(MaxExpr& expr) { }

void ExprVisitor::visit(AbsExpr& expr) { }

void ExprVisitor::visit(SetExpr& expr) { }

void ExprVisitor::visit(ConcatExpr& expr) { }

void ExprVisitor::visit(ReplaceExpr& expr) { }

void ExprVisitor::visit(SubstrExpr& expr) { }

void ExprVisitor::visit(LowercaseExpr& expr) { }

void ExprVisitor::visit(UppercaseExpr& expr) { }

void ExprVisitor::visit(IdentifierExpr& expr) { }

void ExprVisitor::visit(IntLiteral& expr) { }

void ExprVisitor::visit(FloatLiteral& expr) { }

void ExprVisitor::visit(StringLiteral& expr) { }

void ExprVisitor::visit(BoolLiteral& expr) { }

void ExprVisitor::visit(NullLiteral& expr) { }

void ExprVisitor::visit(ErrorExpr& expr) { }

void ExprVisitor::visit(ParseTempExpr& expr) { }

//ParserTempTypeVisitor:

void ParserTempTypeVisitor::visit(ParseTempExpr& expr) {
    last_type = "(" + expr.get_parse_type() + ")";
}
void ParserTempTypeVisitor::clear() {
    last_type = "";
}

std::string ParserTempTypeVisitor::get_type_of_visited_expr() {
    return last_type;
}

//ExprTypeVisitor:

void ExprTypeVisitor::clear() {
    last_type = "";
}

std::string ExprTypeVisitor::get_type_of_visited_expr() {
    return last_type;
}

void ExprTypeVisitor::visit(PutsExpr& expr) {
    last_type = "PutsExpr";
}

void ExprTypeVisitor::visit(ToStrExpr& expr) {
    last_type = "ToStrExpr";
}

void ExprTypeVisitor::visit(AdditionExpr& expr) {
    last_type = "AdditionExpr";
}

void ExprTypeVisitor::visit(SubtractionExpr& expr) {
    last_type = "SubtractionExpr";
}

void ExprTypeVisitor::visit(MultiplicationExpr& expr) {
    last_type = "MultiplicationExpr";
}

void ExprTypeVisitor::visit(DivisionExpr& expr) {
    last_type = "DivisionExpr";
}

void ExprTypeVisitor::visit(GreaterThanExpr& expr) {
    last_type = "GreaterThanExpr";
}

void ExprTypeVisitor::visit(LowerThanExpr& expr) {
    last_type = "LowerThanExpr";
}

void ExprTypeVisitor::visit(EqualExpr& expr) {
    last_type = "EqualExpr";
}

void ExprTypeVisitor::visit(NotEqualExpr& expr) {
    last_type = "NotEqualExpr";
}

void ExprTypeVisitor::visit(MinExpr& expr) {
    last_type = "MinExpr";
}

void ExprTypeVisitor::visit(MaxExpr& expr) {
    last_type = "MaxExpr";
}

void ExprTypeVisitor::visit(AbsExpr& expr) {
    last_type = "AbsExpr";
}

void ExprTypeVisitor::visit(SetExpr& expr) {
    last_type = "SetExpr";
}

void ExprTypeVisitor::visit(ConcatExpr& expr) {
    last_type = "ConcatenationExpr";
}

void ExprTypeVisitor::visit(ReplaceExpr& expr) {
    last_type = "ReplacementExpr";
}

void ExprTypeVisitor::visit(SubstrExpr& expr) {
    last_type = "SubstringExpr";
}

void ExprTypeVisitor::visit(LowercaseExpr& expr) {
    last_type = "LowercaseExpr";
}

void ExprTypeVisitor::visit(UppercaseExpr& expr) {
    last_type = "UppercaseExpr";
}

void ExprTypeVisitor::visit(IdentifierExpr& expr) {
    last_type = "IdentifierExpr";
}

void ExprTypeVisitor::visit(IntLiteral& expr) {
    last_type = "IntLiteralExpr";
}

void ExprTypeVisitor::visit(FloatLiteral& expr) {
    last_type = "FloatLiteralExpr";
}

void ExprTypeVisitor::visit(StringLiteral& expr) {
    last_type = "StringLiteralExpr";
}

void ExprTypeVisitor::visit(BoolLiteral& expr) {
    last_type = "BoolLiteralExpr";
}

void ExprTypeVisitor::visit(NullLiteral& expr) {
    last_type = "NullLiteralExpr";
}

void ExprTypeVisitor::visit(ErrorExpr& expr) {
    last_type = "ErrorExpr";
}

void ExprTypeVisitor::visit(ParseTempExpr& expr) {
    last_type = "ParseTempExpr";
}

//ToStringVisitor:

void ToStringVisitor::clear() {
    last_result = "";
}

std::string ToStringVisitor::get_result_of_visited_expr() {
    return last_result;
}

void ToStringVisitor::visit(PutsExpr& expr) {
    last_result = "PutsExpr";
}

void ToStringVisitor::visit(ToStrExpr& expr) {
    last_result = "ToStrExpr";
}

void ToStringVisitor::visit(AdditionExpr& expr) {
    last_result = "AdditionExpr";
}

void ToStringVisitor::visit(SubtractionExpr& expr) {
    last_result = "SubtractionExpr";
}

void ToStringVisitor::visit(MultiplicationExpr& expr) {
    last_result = "MultiplicationExpr";
}

void ToStringVisitor::visit(DivisionExpr& expr) {
    last_result = "DivisionExpr";
}

void ToStringVisitor::visit(GreaterThanExpr& expr) {
    last_result = "GreaterThanExpr";
}

void ToStringVisitor::visit(LowerThanExpr& expr) {
    last_result = "LowerThanExpr";
}

void ToStringVisitor::visit(EqualExpr& expr) {
    last_result = "EqualExpr";
}

void ToStringVisitor::visit(NotEqualExpr& expr) {
    last_result = "NotEqualExpr";
}

void ToStringVisitor::visit(MinExpr& expr) {
    last_result = "MinExpr";
}

void ToStringVisitor::visit(MaxExpr& expr) {
    last_result = "MaxExpr";
}

void ToStringVisitor::visit(AbsExpr& expr) {
    last_result = "AbsExpr";
}

void ToStringVisitor::visit(SetExpr& expr) {
    last_result = "SetExpr";
}

void ToStringVisitor::visit(ConcatExpr& expr) {
    last_result = "ConcatenationExpr";
}

void ToStringVisitor::visit(ReplaceExpr& expr) {
    last_result = "ReplacementExpr";
}

void ToStringVisitor::visit(SubstrExpr& expr) {
    last_result = "SubstringExpr";
}

void ToStringVisitor::visit(LowercaseExpr& expr) {
    last_result = "LowercaseExpr";
}

void ToStringVisitor::visit(UppercaseExpr& expr) {
    last_result = "UppercaseExpr";
}

void ToStringVisitor::visit(IdentifierExpr& expr) {
    last_result = "IdentifierExpr(" + (expr.get_name()) + ")";
}

void ToStringVisitor::visit(IntLiteral& expr) {
    last_result = "IntLiteralExpr(" + std::to_string(expr.get_value()) + ")";
}

void ToStringVisitor::visit(FloatLiteral& expr) {
    last_result = "FloatLiteralExpr(" + std::to_string(expr.get_value()) + ")";
}

void ToStringVisitor::visit(StringLiteral& expr) {
    last_result = "StringLiteralExpr(" + (expr.get_value()) + ")";
}

void ToStringVisitor::visit(BoolLiteral& expr) {
    last_result = "BoolLiteralExpr(" + std::to_string(expr.get_value()) + ")";
}

void ToStringVisitor::visit(NullLiteral& expr) {
    last_result = "NullLiteralExpr(null)";
}

void ToStringVisitor::visit(ErrorExpr& expr) {
    last_result = "ErrorExpr(" + (expr.get_value()) + ")";
}

void ToStringVisitor::visit(ParseTempExpr& expr) {
    last_result = "ParseTempExpr(" + expr.get_parse_type() + ")";
}