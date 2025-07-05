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

class TokenToExprMapper {
    private:
    public:
        std::shared_ptr<Expr> operator()(std::shared_ptr<KeywordToken> symbol);

        std::shared_ptr<Expr> operator()(std::shared_ptr<IdentifierToken> symbol);

        std::shared_ptr<Expr> operator()(std::shared_ptr<StringLitToken> symbol);

        std::shared_ptr<Expr> operator()(std::shared_ptr<DelimiterToken> symbol);

        std::shared_ptr<Expr> operator()(std::shared_ptr<ErrorToken> symbol);

        std::shared_ptr<Expr> operator()(std::shared_ptr<IntLitToken> symbol);

        std::shared_ptr<Expr> operator()(std::shared_ptr<FloatLitToken> symbol);

        std::shared_ptr<Expr> operator()(std::shared_ptr<BoolLitToken> symbol);

        std::shared_ptr<Expr> operator()(std::shared_ptr<NullLitToken> symbol);

        std::shared_ptr<Expr> operator()(std::shared_ptr<SpaceToken> symbol);

        std::shared_ptr<Expr> operator()(std::shared_ptr<EOFToken> symbol);
        
        std::shared_ptr<Expr> operator()(std::shared_ptr<Token> symbol);
};


class SymbolToExprMapper {
    private:
    public:
        std::shared_ptr<Expr> operator()(std::shared_ptr<Symbol> symbol);
};


#endif // MAPPER_H