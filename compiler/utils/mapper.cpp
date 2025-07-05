#include <memory>

#include "mapper.h"




std::shared_ptr<Expr> SymbolToExprMapper::operator()(std::shared_ptr<Symbol> symbol) {
    ExprCreator expr_creator;
    std::string symbol_str = symbol->get_symbol_str();
    if (
        symbol_str == "Literal" || 
        symbol_str == "Params" || 
        symbol_str == "Params\'" ||
        symbol_str == "Program\'" ||
        symbol_str == "Expr" ||
        symbol_str == "Program"
    ) {
        return expr_creator("ParseTempExpr");
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