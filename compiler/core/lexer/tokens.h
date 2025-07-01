#ifndef TOKENS_H
#define TOKENS_H

#include <string>
#include <memory>



class Token {
private:
    int position;

public:
    static const std::string id_to_token_name[11];
    Token(int position);
    virtual ~Token();

    virtual std::string to_string() = 0;
    virtual std::string get_type() = 0;
    int get_position();
};

template <typename T, int type_name>
class GenericToken : public Token {
private:
    T data;

public:
    GenericToken(T value, int position);
    ~GenericToken() override;

    T get_value();
    std::string get_type() override;
    std::string to_string() override;
};

template<typename T, int type_name>
GenericToken<T, type_name>::GenericToken(T value, int position) : Token(position), data(value)  {}

template<typename T, int type_name>
GenericToken<T, type_name>::~GenericToken() {}

template<typename T, int type_name>
T GenericToken<T, type_name>::get_value() {
    return data;
}

template<typename T, int type_name>
std::string GenericToken<T, type_name>::get_type() {
    return id_to_token_name[type_name];
}

template<typename T, int type_name>
std::string GenericToken<T, type_name>::to_string() {
    if constexpr((std::is_same_v<T, std::string>)) {
        return this->get_type() + "(" + data + ")(" + std::to_string(get_position()) + ")";
    }
    else if constexpr((std::is_same_v<T, bool>)) {
        return this->get_type() + "(" + (data ?  "true" : "false") + ")(" + std::to_string(get_position()) + ")";
    }
    else {
        return this->get_type() + "(" + std::to_string(data) + ")(" + std::to_string(get_position()) + ")";
    }
}   

template <int type_name>
class EmptyToken : public Token {
public:
    EmptyToken(int position);
    std::string to_string() override;
    std::string get_type() override;
};

template<int type_name>
EmptyToken<type_name>::EmptyToken(int position) : Token(position) { }

template<int type_name>
std::string EmptyToken<type_name>::get_type() {
    return id_to_token_name[type_name];
}

template<int type_name>
std::string EmptyToken<type_name>::to_string() {
    return this->get_type() + "()(" + std::to_string(get_position()) +")";
}


using KeywordToken = GenericToken<std::string, 0>;
using IdentifierToken = GenericToken<std::string, 1>;
using StringLitToken = GenericToken<std::string, 2>;
using DelimiterToken = GenericToken<std::string, 3>;
using ErrorToken = GenericToken<std::string, 4>;
using IntLitToken = GenericToken<int, 5>;
using FloatLitToken = GenericToken<float, 6>;
using BoolLitToken = GenericToken<bool, 7>;
using NullLitToken = EmptyToken<8>;
using SpaceToken = EmptyToken<9>;
using EOFToken = EmptyToken<10>;

// Useless?
//using EOFToken = EmptyToken; 
//using OperatorToken
//using PrimTypeToken = GenericToken<string>;

class TokenCreator {
public:
    TokenCreator();
    
    std::shared_ptr<Token> generate_token(std::string tokenType, int data, int pos);
    std::shared_ptr<Token> generate_token(std::string tokenType, float data, int pos);
    std::shared_ptr<Token> generate_token(std::string tokenType, std::string data, int pos);
    std::shared_ptr<Token> generate_token(std::string tokenType, bool data, int pos);
    std::shared_ptr<Token> generate_token(std::string tokenType, int pos);
};

#endif // TOKENS_H