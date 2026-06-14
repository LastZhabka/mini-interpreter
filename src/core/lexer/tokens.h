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

template <typename T, int type_id>
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

template<typename T, int type_id>
GenericToken<T, type_id>::GenericToken(T value, int position) : Token(position), data(value)  {}

template<typename T, int type_id>
GenericToken<T, type_id>::~GenericToken() {}

template<typename T, int type_id>
T GenericToken<T, type_id>::get_value() {
    return data;
}

template<typename T, int type_id>
std::string GenericToken<T, type_id>::get_type() {
    return id_to_token_name[type_id];
}

template<typename T, int type_id>
std::string GenericToken<T, type_id>::to_string() {
    std::string result;
    if constexpr((std::is_same_v<T, std::string>)) {
        result = this->get_type() + "(" + data + ")";
    }
    else if constexpr((std::is_same_v<T, bool>)) {
        result = this->get_type() + "(" + (data ?  "true" : "false") + ")";
    }
    else {
        result = this->get_type() + "(" + std::to_string(data) + ")";
    }
    return result;
    // + "(" + std::to_string(get_position()) + ")";
}   

template <int type_id>
class EmptyToken : public Token {
public:
    EmptyToken(int position);
    std::string to_string() override;
    std::string get_type() override;
};

template<int type_id>
EmptyToken<type_id>::EmptyToken(int position) : Token(position) { }

template<int type_id>
std::string EmptyToken<type_id>::get_type() {
    return id_to_token_name[type_id];
}

template<int type_id>
std::string EmptyToken<type_id>::to_string() {
    std::string result = this->get_type() + "()";
    return result; 
    //+ (" + std::to_string(get_position()) +")";
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


class TokenCreator {
public:
    TokenCreator();
    
    std::shared_ptr<Token> operator()(std::string tokenType, int data, int pos);
    std::shared_ptr<Token> operator()(std::string tokenType, float data, int pos);
    std::shared_ptr<Token> operator()(std::string tokenType, std::string data, int pos);
    std::shared_ptr<Token> operator()(std::string tokenType, bool data, int pos);
    std::shared_ptr<Token> operator()(std::string tokenType, int pos);
};

#endif // TOKENS_H