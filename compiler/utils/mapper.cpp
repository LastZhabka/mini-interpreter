#include <memory>

#include "mapper.h"




std::shared_ptr<Expr> SymbolToExprMapper::operator()(std::shared_ptr<Symbol> symbol) {
    ExprCreator expr_creator;
    std::string symbol_str = symbol->get_symbol_str();
    if (symbol_str == "Params" || symbol_str == "Params\'") {
        return expr_creator("ParseTempExpr");
    }
    else if (symbol_str == "Literal") {
        return expr_creator("ParseTempExpr(Literal)");
    } 
    else if (symbol_str == "Program" || symbol_str == "Program\'") {
        return expr_creator("ParseTempExpr(Program)");
    }
    else if( symbol_str == "Expr") {
        return expr_creator("ParseTempExpr(Expr)");
    }
    return expr_creator(symbol->get_symbol_str());
}


std::shared_ptr<Symbol> TokenToSymbolMapper::operator()(std::shared_ptr<Token> token) {
    std::string token_type = token->get_type();
    
    if (token_type == "DelimiterToken") {
        return std::make_shared<TerminalSymbol>(token->to_string()); // TODO FIX LATER IMPLEMENT SEPARATE MODEL FOR IT
    }
    
    return std::make_shared<TerminalSymbol>(token_type.substr(0, token_type.size() - 5)); // Remove "Token"
}


std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<Token> token) {
    if (token->get_type() == "KeywordToken") {
        return (*this)(std::dynamic_pointer_cast<KeywordToken>(token));
    }
    else if (token->get_type() == "IdentifierToken") {
        return (*this)(std::dynamic_pointer_cast<IdentifierToken>(token));
    }
    else if (token->get_type() == "StringLitToken") {
        return (*this)(std::dynamic_pointer_cast<StringLitToken>(token));
    }
    else if (token->get_type() == "DelimiterToken") {
        return (*this)(std::dynamic_pointer_cast<DelimiterToken>(token));
    }
    else if (token->get_type() == "ErrorToken") {
        return (*this)(std::dynamic_pointer_cast<ErrorToken>(token));
    }
    else if (token->get_type() == "IntLitToken") {
        return (*this)(std::dynamic_pointer_cast<IntLitToken>(token));
    }
    else if (token->get_type() == "FloatLitToken") {
        return (*this)(std::dynamic_pointer_cast<FloatLitToken>(token));
    }
    else if (token->get_type() == "BoolLitToken") {
        return (*this)(std::dynamic_pointer_cast<BoolLitToken>(token));
    }
    else if (token->get_type() == "NullLitToken") {
        return (*this)(std::dynamic_pointer_cast<NullLitToken>(token));
    }
    else if (token->get_type() == "SpaceToken") {
        return (*this)(std::dynamic_pointer_cast<SpaceToken>(token));
    }
    else if (token->get_type() == "EOFToken") {
        return (*this)(std::dynamic_pointer_cast<EOFToken>(token));
    } else {
        assert(0);
    }
}


std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<KeywordToken> token) {
    ExprCreator expr_creator;
    return ExprCreator()("Keyword(" + token->get_value() + ")");
}

std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<IdentifierToken> token) {
    std::shared_ptr<Expr> expr = ExprCreator()("Identifier");
    expr->push_back(std::make_shared<StringLiteral>(token->get_value()));
    return expr;
}

std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<StringLitToken> token){
    return std::make_shared<StringLiteral>(token->get_value());
}

std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<DelimiterToken> token) {
    return ExprCreator()("ParseTempExpr");
}

std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<ErrorToken> token) {
    return std::make_shared<ErrorExpr>(token->get_value());
}

std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<IntLitToken> token) {
    return std::make_shared<IntLiteral>(token->get_value());
}

std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<FloatLitToken> token) {
    return std::make_shared<FloatLiteral>(token->get_value());
}

std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<BoolLitToken> token) {
    return std::make_shared<BoolLiteral>(token->get_value());
}

std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<NullLitToken> token) {
    return std::make_shared<NullLiteral>();
}

std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<SpaceToken> token) {
    return ExprCreator()("ParseTempExpr");
}

std::shared_ptr<Expr> TokenToExprMapper::operator()(std::shared_ptr<EOFToken> token) {
    return ExprCreator()("ParseTempExpr");
}