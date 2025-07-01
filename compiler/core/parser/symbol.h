#ifndef SYMBOL_H
#define SYMBOL_H

#include <cassert>
#include <vector>
#include <memory>
#include <unordered_map>
#include "../lexer/tokens.h"


// We use symbols only for parsing, tree will use another abstraction.

// Base Symbol class and operator classes for unordered_map usage
class Symbol {
    private:
        std::string symbol; // On this stage we'll just store symbol's name, since we don't need any additional information. 
    public:
        Symbol(std::string symbol);

        virtual ~Symbol() = default;

        std::string get_symbol_str() const;

        size_t get_hash();

        bool operator==(const Symbol& other) const;

        virtual bool is_terminal() = 0;
};

class SymbolHash { // for polymorphism
    public:
        size_t operator()(const std::shared_ptr<Symbol>& obj) const;
};

class SymbolEqual { // for polymorphism
    public:
        bool operator()(const std::shared_ptr<Symbol>& lhs, const std::shared_ptr<Symbol>& rhs) const;
};

class TerminalSymbol : public Symbol {
    private:
    public:

        TerminalSymbol(std::shared_ptr<Token> token); 

        TerminalSymbol(std::string symbol);

        bool is_terminal() override;
};

class ProductionRules;

class NonTerminalSymbol : public Symbol {
    private:
        ProductionRules production_rules;
    public:
        NonTerminalSymbol(std::string symbol, ProductionRules production_rules); 
        
        // split function?

        bool is_terminal() override;
};

class ProductionRules {
    private:
        std::unordered_map<
            std::shared_ptr<Symbol>, 
            std::vector<std::shared_ptr<Symbol>>, 
            SymbolHash,
            SymbolEqual
        > production_rules;
    public:
        ProductionRules();

        ProductionRules(std::vector<std::pair<std::shared_ptr<Symbol>, std::vector<std::shared_ptr<Symbol>>>> rules);

        std::vector<std::shared_ptr<Symbol>> get_rule(std::shared_ptr<Symbol> target);
};

#endif // TOKENS_H