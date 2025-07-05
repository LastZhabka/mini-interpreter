#ifndef MAPPER_H
#define MAPPER_H
/*
Mapper from tokens to symbols

And from tokens to AST Nodes
*/

#include <memory>
#include <vector>

#include "../lexer/tokens.h"
#include "../parser/symbol.h"
#include "../ast/tree_module.h"

class SymbolToExprMapper {
    private:
    public:
        std::shared_ptr<Expr> operator()(std::shared_ptr<Symbol> symbol);
};


#endif // MAPPER_H