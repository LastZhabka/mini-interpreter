#include <memory>
#include <cassert>
#include <vector>
#include <functional>

#include "../lexer/tokens.h"
#include "symbol.h"


Symbol::Symbol(std::string symbol) : symbol(symbol) { }

// Symbol::~Symbol() = default;

std::string Symbol::get_symbol_str() const {
    return symbol;
}

size_t Symbol::get_hash() {
    return std::hash<std::string>() (symbol);   
}

bool Symbol::operator==(const Symbol& other) const {
    return this->get_symbol_str() == other.get_symbol_str();
}


// SymbolHash
size_t SymbolHash::operator()(const std::shared_ptr<Symbol>& obj) const {
    return obj->get_hash();
}

//SymbolEqual
bool SymbolEqual::operator()(const std::shared_ptr<Symbol>& lhs, const std::shared_ptr<Symbol>& rhs) const {
    return *lhs == *rhs;
}

//TerminalSymbol

TerminalSymbol::TerminalSymbol(std::string symbol) : Symbol(symbol) { }

bool TerminalSymbol::is_terminal() {
    return true;
}

std::vector<std::shared_ptr<Symbol>> TerminalSymbol::decompose(std::shared_ptr<Symbol> target_first) {
    assert(0);
    return std::vector<std::shared_ptr<Symbol>>();
}

//NonTerminalSymbol

NonTerminalSymbol::NonTerminalSymbol(std::string symbol, std::shared_ptr<ProductionRules> production_rules) : Symbol(symbol), production_rules(production_rules) { }
        
bool NonTerminalSymbol::is_terminal() {
    return false;
}

std::vector<std::shared_ptr<Symbol>> NonTerminalSymbol::decompose(std::shared_ptr<Symbol> target_first) {
    return production_rules->get_rule(target_first);
}
// ProductionRules

ProductionRules::ProductionRules() { }

ProductionRules::ProductionRules(std::vector<std::pair<std::shared_ptr<Symbol>, std::vector<std::shared_ptr<Symbol>>>> rules) { 
    production_rules.reserve(rules.size());
    for (auto rule : rules) {
        production_rules.insert(rule);
    }
}

void ProductionRules::add_rule(std::pair<std::shared_ptr<Symbol>, std::vector<std::shared_ptr<Symbol>>> rule) {
    production_rules.insert(rule);
}

void ProductionRules::add_rules(std::vector<std::pair<std::shared_ptr<Symbol>, std::vector<std::shared_ptr<Symbol>>>> rules) {
    //production_rules.reserve(production_rule.size() + rules.size());?
    for (auto rule : rules) {
        production_rules.insert(rule);
    }
}

std::vector<std::shared_ptr<Symbol>> ProductionRules::get_rule(std::shared_ptr<Symbol> first) {
    if (!production_rules.count(first)) { // Don't create x
        assert(0); // parsing problem
        return std::vector<std::shared_ptr<Symbol>>();
    }
    return production_rules[first];
}


//Factory method for symbol, non-terminal symbol
std::shared_ptr<Symbol> SymbolCreator::operator()(std::string symbol, std::shared_ptr<ProductionRules> production_rules) {
    return std::make_shared<NonTerminalSymbol>(symbol, production_rules);
}

//Factory method for symbol, terminal symbol
std::shared_ptr<Symbol> SymbolCreator::operator()(std::string symbol) {
    return std::make_shared<TerminalSymbol>(symbol);
}

/*

*/