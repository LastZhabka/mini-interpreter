#include <memory>
#include <cassert>
#include <vector>
#include <functional>
#include <stack>
#include <algorithm>
#include <iostream>

#include "../lexer/tokens.h"
#include "parser.h"

Parser::Parser() {
    // HERE WE NEED TO WRITE PARSING RULES FOR OUR LANGUAGE
    using namespace std;
    // TERMINALS:

    shared_ptr<Symbol> eof_ = make_shared<TerminalSymbol>(make_shared<EOFToken>(0));
    shared_ptr<Symbol> space_ = make_shared<TerminalSymbol>(make_shared<SpaceToken>(0));
    shared_ptr<Symbol> null_lit_ = make_shared<TerminalSymbol>(make_shared<NullLitToken>(0));
    shared_ptr<Symbol> bool_lit_ = make_shared<TerminalSymbol>(make_shared<BoolLitToken>(false, 0));
    shared_ptr<Symbol> float_lit_ = make_shared<TerminalSymbol>(make_shared<FloatLitToken>(0.0, 0));
    shared_ptr<Symbol> int_lit_ = make_shared<TerminalSymbol>(make_shared<IntLitToken>(0, 0));
    shared_ptr<Symbol> error_ = make_shared<TerminalSymbol>(make_shared<ErrorToken>("", 0));
    
    shared_ptr<Symbol> delimiter_ob_ = make_shared<TerminalSymbol>(DelimiterToken("(", 0).get_type() + "(()");
    shared_ptr<Symbol> delimiter_cb_ = make_shared<TerminalSymbol>(DelimiterToken(")", 0).get_type() + "())");
    
    shared_ptr<Symbol> string_lit_ = make_shared<TerminalSymbol>(make_shared<StringLitToken>("", 0));
    shared_ptr<Symbol> identifier_ = make_shared<TerminalSymbol>(make_shared<IdentifierToken>("a", 0));
    shared_ptr<Symbol> keyword_ = make_shared<TerminalSymbol>(make_shared<KeywordToken>("", 0));
    
    // it can be a bad design decision, but...
    // Problem : The production rule X are stored inside the symbolA,
    //           sometimes production rule X can contain the symbolA
    //           itself, but to create symbolA and add it to X we need
    //           to create production rule X, ...
    // So there are 2 ways to resolve the problem
    // 1. Move the production rules from symbols, for example create some
    //    production rule table, but it's not too convenient for me
    // 2. Using the shared_ptr properties just update the rules after symbol
    //    creation. I'll use this one.

    shared_ptr<ProductionRules> literal_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> literal = make_shared<NonTerminalSymbol>("Literal", literal_rules);

    shared_ptr<ProductionRules> params_prime_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> params_prime = make_shared<NonTerminalSymbol>("Params\'", params_prime_rules);

    shared_ptr<ProductionRules> params_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> params = make_shared<NonTerminalSymbol>("Params", params_rules);

    shared_ptr<ProductionRules> program_prime_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> program_prime = make_shared<NonTerminalSymbol>("Program\'", program_prime_rules);

    shared_ptr<ProductionRules> expr_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> expression = make_shared<NonTerminalSymbol>("Expr", expr_rules);
    
    shared_ptr<ProductionRules> program_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> program = make_shared<NonTerminalSymbol>("Program", program_rules);


    // Rules
    literal_rules->add_rules({
            make_pair(null_lit_, vector<shared_ptr<Symbol>>{null_lit_}), 
            make_pair(bool_lit_, vector<shared_ptr<Symbol>>{bool_lit_}),
            make_pair(float_lit_, vector<shared_ptr<Symbol>>{float_lit_}), 
            make_pair(int_lit_, vector<shared_ptr<Symbol>>{int_lit_}),
            make_pair(string_lit_, vector<shared_ptr<Symbol>>{string_lit_})
        }
    );

    expr_rules->add_rules({
            make_pair(
                delimiter_ob_, 
                vector<shared_ptr<Symbol>>{
                    delimiter_ob_, keyword_, space_, params
                }
            ), 
            make_pair(null_lit_, vector<shared_ptr<Symbol>>{literal}), 
            make_pair(bool_lit_, vector<shared_ptr<Symbol>>{literal}),
            make_pair(float_lit_, vector<shared_ptr<Symbol>>{literal}), 
            make_pair(int_lit_, vector<shared_ptr<Symbol>>{literal}),
            make_pair(string_lit_, vector<shared_ptr<Symbol>>{literal}),
            make_pair(identifier_, vector<shared_ptr<Symbol>>{identifier_}) // maybe provide better interface in prod_rules? TODO
        }
    );

    program_rules->add_rules({
            make_pair(delimiter_ob_, vector<shared_ptr<Symbol>>{expression, program_prime}), 
            make_pair(null_lit_, vector<shared_ptr<Symbol>>{expression, program_prime}), 
            make_pair(bool_lit_, vector<shared_ptr<Symbol>>{expression, program_prime}),
            make_pair(float_lit_, vector<shared_ptr<Symbol>>{expression, program_prime}), 
            make_pair(int_lit_, vector<shared_ptr<Symbol>>{expression, program_prime}),
            make_pair(string_lit_, vector<shared_ptr<Symbol>>{expression, program_prime}),
            make_pair(identifier_, vector<shared_ptr<Symbol>>{expression, program_prime})
        }
    );

    program_prime_rules->add_rules({
            make_pair(space_, vector<shared_ptr<Symbol>>{space_, program}),
            make_pair(eof_, vector<shared_ptr<Symbol>>{eof_})
        }
    );    

    params_rules->add_rules({
            make_pair(delimiter_ob_, vector<shared_ptr<Symbol>>{expression, params_prime}), 
            make_pair(null_lit_, vector<shared_ptr<Symbol>>{expression, params_prime}), 
            make_pair(bool_lit_, vector<shared_ptr<Symbol>>{expression, params_prime}),
            make_pair(float_lit_, vector<shared_ptr<Symbol>>{expression, params_prime}), 
            make_pair(int_lit_, vector<shared_ptr<Symbol>>{expression, params_prime}),
            make_pair(string_lit_, vector<shared_ptr<Symbol>>{expression, params_prime}),
            make_pair(identifier_, vector<shared_ptr<Symbol>>{expression, params_prime})
        }
    );

    params_prime_rules->add_rules({
            make_pair(space_, vector<shared_ptr<Symbol>>{space_, params}),
            make_pair(delimiter_cb_, vector<shared_ptr<Symbol>>{delimiter_cb_})
        }
    );   
    this->start_symbol = program;
}

/*

Program -> Expression Program'
Program' -> \SpaceToken Program | \EOFToken

Expression -> \DelimiterToken(() Function \SpaceToken Params | Literal //  \DelimiterToken()) is handled by Params!!
Function -> \KeywordToken(add)|...|\KeywordToken(not_equal)
Params -> Expression Params'
Params' -> \SpaceToken Params | \DelimiterToken())
Literal -> \IntLitToken(...) | \BoolLitToken(...) | \FloatLitToken(...) | \StringLitToken(...) | \IdentifierToken


First(Literal) = {\IntLitTOken(...), \BoolLitToken(...), \FloatLitToken(...), \StringLitToken(...), \IdentifierToken}

First(Expression) = {\DelimiterToken((), \IntLitToken(...), \BoolLitToken(...), 
                     \FloatLitToken(...), \StringLitToken(...), \IdentifierToken}

First(Function) = {\KeywordToken(...)}

First(Params) = {\DelimiterToken((), \IntLitToken(...), \BoolLitToken(...), 
                 \FloatLitToken(...), \StringLitToken(...), \IdentifierToken}

First(Program) = {\DelimiterToken((), \IntLitToken(...), \BoolLitToken(...), {\SpaceToken},
                  \FloatLitToken(...), \StringLitToken(...), \IdentifierToken}

First(Program') = {\SpaceToken, \EOFToken}

*/

std::shared_ptr<Symbol> tokenToParserSymbol(std::shared_ptr<Token> token) {
    if (token->get_type() == "DelimiterToken") {
        return std::make_shared<TerminalSymbol>(token->to_string()); // TODO FIX LATER IMPLEMENT SEPARATE MODEL FOR IT
    }
    return std::make_shared<TerminalSymbol>(token);
}

void Parser::parse(std::vector<std::shared_ptr<Token>> input)  {
    if (input.size() == 0)
        return;
    int input_pos = 0;
    std::shared_ptr<Symbol> cur_input_symb = tokenToParserSymbol(input[0]);

    std::stack<std::shared_ptr<Symbol>> parsing_stack;
    parsing_stack.push(start_symbol);

    while (parsing_stack.size()) {
        std::cerr << parsing_stack.top()->get_symbol_str() << " " << cur_input_symb->get_symbol_str() << "\n";
        if (*parsing_stack.top() == *cur_input_symb) {
            // do something
            parsing_stack.pop();
            input_pos += 1;
            if (input_pos == input.size()) {
                assert(parsing_stack.size() == 0);
                break;
            }
            cur_input_symb = tokenToParserSymbol(input[input_pos]);
        }  
        else {
            std::vector<std::shared_ptr<Symbol>> decomposed_top = parsing_stack.top()->decompose(cur_input_symb);
            // DO SOMETHING
            reverse(decomposed_top.begin(), decomposed_top.end());
            parsing_stack.pop();
            for(auto symb : decomposed_top) {
                parsing_stack.push(symb);
            }
        }
    }

}


