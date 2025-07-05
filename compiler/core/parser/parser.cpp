#include <memory>
#include <cassert>
#include <vector>
#include <functional>
#include <stack>
#include <algorithm>
#include <iostream>
#include <map>

#include "../lexer/tokens.h"
#include "../ast/tree_module.h"
#include "parser.h"
#include "../../utils/mapper.h"

ParsingStackElement::ParsingStackElement(
    std::shared_ptr<Symbol> symbol, std::shared_ptr<Expr> expr, std::shared_ptr<Expr> ancestor, int order
) : symbol(symbol), expr(expr), expr_ancestor(ancestor), order(order){ }

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
Parser::Parser() {
    using namespace std;
    // TERMINALS:
    TokenToSymbolMapper tokens_to_symbol_mapper;
    SymbolCreator symbol_creator;

    shared_ptr<Symbol> eof_ = tokens_to_symbol_mapper(make_shared<EOFToken>(0));
    shared_ptr<Symbol> space_ = tokens_to_symbol_mapper(make_shared<SpaceToken>(0));
    shared_ptr<Symbol> null_lit_ = tokens_to_symbol_mapper(make_shared<NullLitToken>(0));
    shared_ptr<Symbol> bool_lit_ = tokens_to_symbol_mapper(make_shared<BoolLitToken>(false, 0));
    shared_ptr<Symbol> float_lit_ = tokens_to_symbol_mapper(make_shared<FloatLitToken>(0.0, 0));
    shared_ptr<Symbol> int_lit_ = tokens_to_symbol_mapper(make_shared<IntLitToken>(0, 0));
    shared_ptr<Symbol> error_ = tokens_to_symbol_mapper(make_shared<ErrorToken>("", 0));
    
    shared_ptr<Symbol> delimiter_ob_ = symbol_creator(DelimiterToken("(", 0).get_type() + "(()");
    shared_ptr<Symbol> delimiter_cb_ = symbol_creator(DelimiterToken(")", 0).get_type() + "())");
    
    shared_ptr<Symbol> string_lit_ = tokens_to_symbol_mapper(make_shared<StringLitToken>("", 0));
    shared_ptr<Symbol> identifier_ = tokens_to_symbol_mapper(make_shared<IdentifierToken>("a", 0));
    shared_ptr<Symbol> keyword_ = tokens_to_symbol_mapper(make_shared<KeywordToken>("", 0));
    
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
    shared_ptr<Symbol> literal = symbol_creator("Literal", literal_rules);

    shared_ptr<ProductionRules> params_prime_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> params_prime = symbol_creator("Params\'", params_prime_rules);

    shared_ptr<ProductionRules> params_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> params = symbol_creator("Params", params_rules);

    shared_ptr<ProductionRules> program_prime_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> program_prime = symbol_creator("Program\'", program_prime_rules);

    shared_ptr<ProductionRules> expr_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> expression = symbol_creator("Expr", expr_rules);
    
    shared_ptr<ProductionRules> program_rules = make_shared<ProductionRules>(
        vector<pair<shared_ptr<Symbol>, vector<shared_ptr<Symbol>>>>()
    );
    shared_ptr<Symbol> program = symbol_creator("Program", program_rules);


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




void Parser::parse(std::vector<std::shared_ptr<Token>> input)  {
    using namespace std;
    
    
    if (input.size() == 0)
        return;

    // Init concrete syntax tree
    shared_ptr<Expr> parse_tree_root = ExprCreator()("ParseTempExpr");


    // Init parsing stack
    stack<ParsingStackElement> parsing_stack;
    parsing_stack.push(ParsingStackElement{start_symbol, parse_tree_root, nullptr, -1});

    // Init current symbol
    int input_pos = 0;
    shared_ptr<Symbol> cur_input_symb = TokenToSymbolMapper()(input[0]);



    while (parsing_stack.size()) {

        cerr << parsing_stack.top().symbol->get_symbol_str() << " " << cur_input_symb->get_symbol_str() << "\n";

        if (*(parsing_stack.top().symbol) == *cur_input_symb) {
            
            parsing_stack.top().expr_ancestor->modify(parsing_stack.top().order, TokenToExprMapper()(input[input_pos]));
            
            parsing_stack.pop();
            
            input_pos += 1;
            if (input_pos == input.size()) {
                assert(parsing_stack.size() == 0);
                break;
            }
            cur_input_symb = TokenToSymbolMapper()(input[input_pos]);
        }  
        else {
            vector<shared_ptr<Symbol>> decomposed_form = parsing_stack.top().symbol->decompose(cur_input_symb);
            shared_ptr<Expr> cur_expr = parsing_stack.top().expr;
            reverse(decomposed_form.begin(), decomposed_form.end());
            parsing_stack.pop();

            for(int ind = 0; ind < decomposed_form.size(); ind++) {
                parsing_stack.push(
                    ParsingStackElement{decomposed_form[ind], SymbolToExprMapper()(decomposed_form[ind]), cur_expr, ind}
                );
                cur_expr->push_back(parsing_stack.top().expr);
            }
        }
    }

}


