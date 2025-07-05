#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <cassert>
#include <vector>
#include <functional>
#include <stack>

#include "symbol.h"
#include "../lexer/tokens.h"
#include "../ast/tree_module.h"

class Parser {
    private:
        std::shared_ptr<Symbol> start_symbol;
    public:
        Parser();

        void parse(std::vector<std::shared_ptr<Token>> input);
};

struct ParsingStackElement {
    std::shared_ptr<Symbol> symbol;
    std::shared_ptr<Expr> expr;
    std::shared_ptr<Expr> expr_ancestor;
    int order;
    ParsingStackElement(std::shared_ptr<Symbol> symbol, std::shared_ptr<Expr> expr, std::shared_ptr<Expr> expr_ancestor, int order);
};



// class ParseTable {
//   //TODO  
// };

// class Parser {
//     ParseTable x;
// };


#endif // PARSER_H