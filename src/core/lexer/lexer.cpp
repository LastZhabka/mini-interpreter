#include <regex>
#include <cassert>
#include <stdexcept>
#include <iostream>
#include "lexer.h"
#include "tokens.h"


Rule::Rule(std::regex premise, std::string token_type) : premise(std::move(premise)), token_type(std::move(token_type)) {
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
                    "|(uppercase)|(replace)"
                    "|(substring)|(subtract)|(multiply)"
                    "|(divide)|(abs)|(min)|(max)|(gt)|(lt)|(equal)|(not_equal)|(str))");
    lexer_rules.push_back(Rule(keywords, "KeywordToken"));
    
    lexer_rules.push_back(Rule(std::regex("^(null)"), "NullLitToken"));
    lexer_rules.push_back(Rule(std::regex("^((0)|(-?[1-9][0-9]*))"), "IntLitToken"));
    lexer_rules.push_back(Rule(std::regex("^((0)|(-?[1-9][0-9]*)\\.([0-9]*))"), "FloatLitToken"));
    lexer_rules.push_back(Rule(std::regex("^(\"([^\"])*\")"), "StringLitToken"));
    lexer_rules.push_back(Rule(std::regex("^((false)|(true))"), "BoolLitToken"));
    
    lexer_rules.push_back(Rule(std::regex("^([a-z]([a-z]|[A-Z])*)"), "IdentifierToken"));
    lexer_rules.push_back(Rule(std::regex("^\\s"), "SpaceToken"));                
}

std::vector<std::shared_ptr<Token>> Lexer::run(std::string input) {
    // works in O(|Rules| * n^2), we can do it faster
    std::vector<std::shared_ptr<Token>> tokens;  
    while(input.size()) {
        std::string longest_match_name = "None";
        int longest_match_size = -1;
        for(auto& rule : lexer_rules) {
            std::smatch rule_match;
            if (regex_search(input, rule_match, rule.get_regex(), std::regex_constants::match_continuous) 
                && int(rule_match.length()) > longest_match_size) {
                longest_match_name = rule.get_token_type();
                longest_match_size = rule_match.length();
            }
        }
        if (longest_match_name == "None")
            throw std::runtime_error("Incorrect program.");
        
        
        if (longest_match_name  == "IntLitToken") {
            std::string value = input.substr(0, longest_match_size);
            tokens.push_back(token_creator(longest_match_name , std::stoi(value), 0));//TODO
        } 
        else if (longest_match_name  == "BoolLitToken") {
            std::string value = input.substr(0, longest_match_size);
            tokens.push_back(token_creator(longest_match_name , bool(value == "true"), 0));//TODO
        }
        else if (longest_match_name  == "FloatLitToken") {
            std::string value = input.substr(0, longest_match_size);
            tokens.push_back(token_creator(longest_match_name , std::stof(value), 0));//TODO
        }
        else if (longest_match_name  == "NullLitToken") {
            tokens.push_back(token_creator(longest_match_name , 0)); //TODO
        }
        else if (longest_match_name  == "StringLitToken") {
            tokens.push_back(token_creator(longest_match_name , input.substr(1, longest_match_size - 2), 0)); // TODO    
        }        
        else if(longest_match_name  == "SpaceToken") {
            if(tokens.size() && tokens.back()->get_type() != "SpaceToken") {
                tokens.push_back(token_creator(longest_match_name , 0)); //TODO
            }
        }
        else {
            tokens.push_back(token_creator(longest_match_name , input.substr(0, longest_match_size), 0)); // TODO
        }

        input = input.substr(longest_match_size, input.size() - longest_match_size);
    }
    while(tokens.size() && tokens.back()->get_type() == "SpaceToken")
        tokens.pop_back();
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