#ifndef PARSER_H
#define PARSER_H

#include <memory>
#include <cassert>
#include <vector>
#include <functional>
#include <stack>

#include "../lexer/tokens.h"
#include "symbol.h"

class Parser {
    private:
        std::shared_ptr<Symbol> start_symbol;
    public:
        Parser();

        void parse(std::vector<std::shared_ptr<Token>> input);
};




// class ParseTable {
//   //TODO  
// };

// class Parser {
//     ParseTable x;
// };


#endif // PARSER_H