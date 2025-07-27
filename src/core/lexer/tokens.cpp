#include <string>
#include <typeinfo>
#include <cassert>
#include <memory>
#include "tokens.h"

const std::string Token::id_to_token_name[11] = {
    "KeywordToken", "IdentifierToken", "StringLitToken",
    "DelimiterToken", "ErrorToken", "IntLitToken",
    "FloatLitToken", "BoolLitToken", "NullLitToken",
    "SpaceToken", "EOFToken"
}; 

Token::Token(int position) : position(position) { }

Token::~Token() = default;

// std::string Token::to_string() = 0;

int Token::get_position() { 
    return position;
}

TokenCreator::TokenCreator() { }

std::shared_ptr<Token> TokenCreator::operator()(std::string tokenType, int data, int pos) {
    if (tokenType == "IntLitToken") {
        return std::make_shared<IntLitToken>(data, pos);                
    }
    assert(0);
    return std::make_shared<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
}

std::shared_ptr<Token> TokenCreator::operator()(std::string tokenType, float data, int pos) {
    if (tokenType == "FloatLitToken") {
        return std::make_shared<FloatLitToken>(data, pos);                
    }
    assert(0);
    return std::make_shared<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
}

std::shared_ptr<Token> TokenCreator::operator()(std::string tokenType, std::string data, int pos) {
    if (tokenType == "StringLitToken") {
        return std::make_shared<StringLitToken>(data, pos);                
    }
    else if (tokenType == "DelimiterToken") {
        return std::make_shared<DelimiterToken>(data, pos);                
    }
    else if (tokenType == "KeywordToken") {
        return std::make_shared<KeywordToken>(data, pos);                
    }
    else if (tokenType == "IdentifierToken") {
        return std::make_shared<IdentifierToken>(data, pos);
    }
    else if (tokenType == "ErrorToken") {
        return std::make_shared<ErrorToken>(data, pos);                
    }
    assert(0);
    return std::make_shared<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
}

std::shared_ptr<Token> TokenCreator::operator()(std::string tokenType, bool data, int pos ) {
    if (tokenType == "BoolLitToken") {
        return std::make_shared<BoolLitToken>(data, pos); 
    }      
    assert(0);
    return std::make_shared<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
}

std::shared_ptr<Token> TokenCreator::operator()(std::string tokenType, int pos = 0) {
    if (tokenType == "NullLitToken") {
        return std::make_shared<NullLitToken>(pos);
    }
    else if (tokenType == "SpaceToken") {
        return std::make_shared<SpaceToken>(pos);
    }
    else if (tokenType == "EOFToken") {
        return std::make_shared<EOFToken>(pos);
    }
    assert(0);
    return std::make_shared<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
}
