#ifndef LEXER_H
#define LEXER_H

#include <regex>
#include <cassert>
#include <iostream>
#include "tokens.h"


class Rule {
    private:
        std::regex premise;
        std::string token_type;
    public:
        Rule(std::regex premise, std::string token_type);
        
        std::regex get_regex();

        std::string get_token_type();
};


class Lexer {
    private:
        std::vector<Rule> lexer_rules;
        TokenCreator token_creator;
    public:

        Lexer();

        std::vector<std::shared_ptr<Token>> run(std::string input);
};
#endif // LEXER_H