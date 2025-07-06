#include <regex>
#include <cassert>
#include <iostream>
#include "lexer.h"
#include "tokens.h"


Rule::Rule(std::regex premise, std::string token_type) : premise(premise), token_type(token_type) {
    return;
}

std::regex Rule::get_regex() {
    return premise;
}

std::string Rule::get_token_type() {
    return token_type;
}


Lexer::Lexer() {     
    lexer_rules.push_back(Rule(std::regex("^(\\(|\\))"), "DelimiterToken"));
    
    std::regex keywords("^((add)|(set)|(puts)|(concat)|(lowercase)"
                    "|(uppercase)|(lowercase)|(replace)"
                    "|(substring)|(subtract)|(multiply)"
                    "|(divide)|(abs)|(min)|(gt)|(lt)|(equal)|(not_equal))");
    lexer_rules.push_back(Rule(keywords, "KeywordToken"));
    
    lexer_rules.push_back(Rule(std::regex("^null"), "NullLitToken"));
    lexer_rules.push_back(Rule(std::regex("^(0)|(-?[1-9][0-9]*)"), "IntLitToken"));
    lexer_rules.push_back(Rule(std::regex("^(0)|(-?[1-9][0-9]*)\\.([0-9]*)"), "FloatLitToken"));
    lexer_rules.push_back(Rule(std::regex("^\"(\\w)*\""), "StringLitToken"));
    lexer_rules.push_back(Rule(std::regex("^(false)|(true)"), "BoolLitToken"));
    
    lexer_rules.push_back(Rule(std::regex("^[a-z]([a-z]|[A-Z])*"), "IdentifierToken"));
    lexer_rules.push_back(Rule(std::regex("^ "), "SpaceToken"));
    lexer_rules.push_back(Rule(std::regex("^\n"), "SpaceToken"));                    
}

std::vector<std::shared_ptr<Token>> Lexer::run(std::string input) {
    // works in O(|Rules| * n^2), we can do it faster
    std::vector<std::shared_ptr<Token>> tokens;  
    while(input.size()) {
        std::pair<std::string, int> longest_match = {"None", -1};
        for(auto rule : lexer_rules) {
            std::smatch rule_match;
            if (regex_search(input, rule_match, rule.get_regex()) && int(rule_match.str().size()) > longest_match.second) {
                longest_match = make_pair(rule.get_token_type(), rule_match.str().size());
            }
        }
        if (longest_match.first == "None") {
            assert(0);
        }
        else if (longest_match.first == "IntLitToken") {
            std::string value = input.substr(0, longest_match.second);
            tokens.push_back(token_creator(longest_match.first, 1, 0));//TODO
        } 
        else if (longest_match.first == "BoolLitToken") {
            std::string value = input.substr(0, longest_match.second);
            tokens.push_back(token_creator(longest_match.first, bool(value == "true"), 0));//TODO
        }
        else if (longest_match.first == "FloatLitToken") {
            std::string value = input.substr(0, longest_match.second);
            tokens.push_back(token_creator(longest_match.first, float(1.0), 0));//TODO
        } 
        else if(longest_match.first == "SpaceToken" || longest_match.first == "NullLitToken") {
            tokens.push_back(token_creator(longest_match.first, 0));//TODO
        }
        else {
            tokens.push_back(token_creator(longest_match.first, input.substr(0, longest_match.second), 0));
        }

        input = input.substr(longest_match.second, input.size() - longest_match.second);
    }
    
    tokens.push_back(token_creator("EOFToken", 0)); // Add EOF Token at the end
    
    return tokens;
}


/*
Rules:

    (|)  => DelimiterToken(pos, symb)

    add|set|puts|concat|lowercase|uppercase|lowercase|
    replace|substring|subtract|multiply|divide|abs|
    min|gt|lt|equal|not_equal 
    => KeywordToken

    null 
    => NullLitToken

    (0) | ((1 | 2 | ... | 9) + (0 | 1 | 2 | ... | 9)*) 
    => IntLitToken

    (") + (not("))* + (") 
    => StringLitToken

    false | true 
    => BoolLitToken

    ((0) | ((1 | 2 | ... | 9) + (0 | 1 | 2 | ... | 9)*)) 
    + '.' + ((0) | ((1 | 2 | ... | 9) + (0 | 1 | 2 | ... | 9)*) 
    => FloatLitToken

    (a | b | ... | z) + ((a | ... | z | A | ... | Z)*) => IdentifierToken
*/

// longest match, first rule