#include <regex>
#include <cassert>
#include <iostream>
#include "tokens.h"
using namespace std;

/*
Rules:

    (|)  => DelimiterToken(pos, symb)

    add|set|puts|concat|lowercase|uppercase|lowercase +
    replace|substring|subtract|multiply|divide|abs +
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


class Rule {
    private:
        regex premise;
        string token_type;
    public:
        Rule(regex premise, string token_type) : premise(premise), token_type(token_type) {
            return;
        }
        
        regex get_regex() {
            return premise;
        }

        string get_token_type() {
            return token_type;
        }
};

// Brzozowski derivatives later if Lexer will be too slow
class Lexer {
    private:
        vector<Rule> lexer_rules;
        TokenCreator token_creator;
    public:

        Lexer() {            
            
            lexer_rules.push_back(Rule(regex("^(\\(|\\))"), "DelimiterToken"));
            
            regex keywords("^((add)|(set)|(puts)|(concat)|(lowercase)"
                           "|(uppercase)|(lowercase)|(replace)"
                           "|(substring)|(subtract)|(multiply)"
                           "|(divide)|(abs)|(min)|(gt)|(lt)|(equal)|(not_equal))");
            lexer_rules.push_back(Rule(keywords, "KeywordToken"));
            
            lexer_rules.push_back(Rule(regex("^null"), "NullLitToken"));
            lexer_rules.push_back(Rule(regex("^(0)|(-?[1-9][0-9]*)"), "IntLitToken"));
            lexer_rules.push_back(Rule(regex("^(0)|(-?[1-9][0-9]*)\\.([0-9]*)"), "FloatLitToken"));
            lexer_rules.push_back(Rule(regex("^\"(\\w)*\""), "StringLitToken"));
            lexer_rules.push_back(Rule(regex("^(false)|(true)"), "BoolLitToken"));
            
            lexer_rules.push_back(Rule(regex("^[a-z]([a-z]|[A-Z])*"), "IdentifierToken"));
            lexer_rules.push_back(Rule(regex("^ "), "SpaceToken"));
            lexer_rules.push_back(Rule(regex("^\n"), "SpaceToken"));                    
        }

        

        vector<unique_ptr<Token>> run(string input) {
            // works in O(|Rules| * n^2), we can do it faster
            vector<unique_ptr<Token>> tokens;  
            while(input.size()) {
                pair<string, int> longest_match = {"None", -1};
                for(auto rule : lexer_rules) {
                    smatch rule_match;
                    if (regex_search(input, rule_match, rule.get_regex()) && int(rule_match.str().size()) > longest_match.second) {
                        longest_match = make_pair(rule.get_token_type(), rule_match.str().size());
                    }
                }
                if (longest_match.first == "None") {
                    assert(0);
                }
                else if (longest_match.first == "IntLitToken") {
                    string value = input.substr(0, longest_match.second);
                    tokens.push_back(token_creator.generate_token(longest_match.first, 1, 0));//TODO
                } 
                else if (longest_match.first == "BoolLitToken") {
                    string value = input.substr(0, longest_match.second);
                    tokens.push_back(token_creator.generate_token(longest_match.first, bool(value == "true"), 0));//TODO
                }
                else if (longest_match.first == "FloatLitToken") {
                    string value = input.substr(0, longest_match.second);
                    tokens.push_back(token_creator.generate_token(longest_match.first, float(1.0), 0));//TODO
                } 
                else if(longest_match.first == "SpaceToken" || longest_match.first == "NullLitToken") {
                    tokens.push_back(token_creator.generate_token(longest_match.first, 0));//TODO
                }
                else {
                    tokens.push_back(token_creator.generate_token(longest_match.first, input.substr(0, longest_match.second), 0));
                }

                input = input.substr(longest_match.second, input.size() - longest_match.second);
            }
            return tokens;
        }      
};

int main() {
    Lexer lexer = Lexer();
    for(auto &u : lexer.run("(uppercase \"abc\")")) {
        std::cout << u->to_string() << "\n";
    }

}

/*
g++ -std=c++17 -c compiler/core/parser/tokens.cpp -o compiler/core/parser/tokens.o
g++ -std=c++17 compiler/core/parser/tokens.o compiler/core/parser/lexer.cpp
a.exe
*/