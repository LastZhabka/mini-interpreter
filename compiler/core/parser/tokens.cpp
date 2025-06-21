#include <string>
#include <typeinfo>
#include <cassert>
#include <memory>
#include "tokens.h"

const std::string Token::token_names[10] = {
    "KeywordToken", "IdentifierToken", "StringLitToken",
    "DelimiterToken", "ErrorToken", "IntLitToken",
    "FloatLitToken", "BoolLitToken", "NullLitToken",
    "SpaceToken"
}; 

Token::Token(int position) : position(position) { }

Token::~Token() = default;

// std::string Token::to_string() = 0;

int Token::get_position() { 
    return position;
}

TokenCreator::TokenCreator() { }

std::unique_ptr<Token> TokenCreator::generate_token(std::string tokenType, int data, int pos) {
    if (tokenType == "IntLitToken") {
        return std::make_unique<IntLitToken>(data, pos);                
    }
    assert(0);
    return std::make_unique<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
}

std::unique_ptr<Token> TokenCreator::generate_token(std::string tokenType, float data, int pos) {
    if (tokenType == "FloatLitToken") {
        return std::make_unique<FloatLitToken>(data, pos);                
    }
    assert(0);
    return std::make_unique<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
}

std::unique_ptr<Token> TokenCreator::generate_token(std::string tokenType, std::string data, int pos) {
    if (tokenType == "StringLitToken") {
        return std::make_unique<StringLitToken>(data, pos);                
    }
    else if (tokenType == "DelimiterToken") {
        return std::make_unique<DelimiterToken>(data, pos);                
    }
    else if (tokenType == "KeywordToken") {
        return std::make_unique<KeywordToken>(data, pos);                
    }
    else if (tokenType == "IdentifierToken") {
        return std::make_unique<IdentifierToken>(data, pos);
    }
    else if (tokenType == "ErrorToken") {
        return std::make_unique<ErrorToken>(data, pos);                
    }
    assert(0);
    return std::make_unique<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
}

std::unique_ptr<Token> TokenCreator::generate_token(std::string tokenType, bool data, int pos ) {
    if (tokenType == "BoolLitToken") {
        return std::make_unique<BoolLitToken>(data, pos); 
    }      
    assert(0);
    return std::make_unique<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
}

std::unique_ptr<Token> TokenCreator::generate_token(std::string tokenType, int pos = 0) {
    if (tokenType == "NullLitToken") {
        return std::make_unique<NullLitToken>(pos);
    }
    else if (tokenType == "SpaceToken") {
        return std::make_unique<SpaceToken>(pos);
    }
    assert(0);
    return std::make_unique<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
}
