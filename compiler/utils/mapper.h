#ifndef MAPPER_H
#define MAPPER_H
/*
Mapper from tokens to symbols

And from tokens to AST Nodes
*/

#include <memory>
#include <vector>

#include "../core/lexer/tokens.h"
#include "../core/parser/symbol.h"
#include "../core/ast/tree_module.h"

class TokenToSymbolMapper {
    private:
    public:
        std::shared_ptr<Symbol> operator()(std::shared_ptr<Token> symbol);
};

class SymbolToExprMapper {
    private:
    public:
        std::shared_ptr<Expr> operator()(std::shared_ptr<Symbol> symbol);
};


#endif // MAPPER_H