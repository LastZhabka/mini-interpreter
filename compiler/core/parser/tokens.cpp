#include <string>
#include <typeinfo>
#include <cassert>
#include <memory>
using namespace std;

class Token {
    private:
        int position;
    public:
        Token(int position) : position(position) {}

        virtual ~Token() = default;

        virtual string to_string() {
            assert(0);
        }
        
        int getPosition() {
            return position;
        }
};

template<typename T>
class GenericToken  : public Token {
    private:
        T data;
    public:
        GenericToken(T value, int position) : Token(position), data(value)  {}
        ~GenericToken() override {
            HERE
        }
       
        T getValue() {
            return data;
        }
        string to_string() override {
            if (constexpr(is_same_v<T, string>::value)) {
                return string(typeid(*this).name()) + "(" + data + ")(" + std::to_string(getPosition()) + ")";
            }
            else if (constexpr(is_same_v<T, string>::value)) {
                return string(typeid(*this).name()) + "(" + (data == 0 ? "false" : "true") + ")(" + std::to_string(getPosition()) + ")";
            }
            else {
                return string(typeid(*this).name()) + "(" + std::to_string(data) + ")(" + std::to_string(getPosition()) + ")";
            }
        }   
};

class EmptyToken : public Token {
public:
    EmptyToken(int position) : Token(position) {}

    string to_string() override {
        return string(typeid(*this).name()) + "()(" + std::to_string(getPosition()) +")";
    }
    
};

using KeywordToken = GenericToken<string>;
using IdentifierToken = GenericToken<string>;
using StringLitToken = GenericToken<string>;
using DelimiterToken = GenericToken<string>;
using ErrorToken = GenericToken<string>;
using IntLitToken = GenericToken<int>;
using BoolLitToken = GenericToken<bool>;
using NullLitToken = EmptyToken;
using SpaceToken = EmptyToken;

// Useless?
//using EOFToken = EmptyToken; 
//using OperatorToken
//using PrimTypeToken = GenericToken<string>;


class TokenCreator {
    public:
        TokenCreator() {

        }
        unique_ptr<Token> generate_token(string tokenType, int data, int pos) {
            if (tokenType == "IntLitToken") {
                return make_unique<IntLitToken>(data, pos);                
            }
            assert(0);
            return make_unique<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
        }
        unique_ptr<Token> generate_token(string tokenType, string data, int pos) {
            if (tokenType == "StringLitToken") {
                return make_unique<StringLitToken>(data, pos);                
            }
            else if (tokenType == "DelimiterToken") {
                return make_unique<DelimiterToken>(data, pos);                
            }
            else if (tokenType == "KeywordToken") {
                return make_unique<KeywordToken>(data, pos);                
            }
            else if (tokenType == "IdentifierToken") {
                return make_unique<IdentifierToken>(data, pos);
            }
            else if (tokenType == "ErrorToken") {
                return make_unique<ErrorToken>(data, pos);                
            }
            assert(0);
            return make_unique<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
        }

        unique_ptr<Token> generate_token(string tokenType, bool data, int pos ) {
            if (tokenType == "BoolLitToken") {
                return make_unique<BoolLitToken>(data, pos); 
            }      
            assert(0);
            return make_unique<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
        }

        unique_ptr<Token> generate_token(string tokenType, int pos = 0) {
            if (tokenType == "NullLitToken") {
                return make_unique<NullLitToken>(pos);
            }
            else if (tokenType == "SpaceToken") {
                return make_unique<SpaceToken>(pos);
            }
            assert(0);
            return make_unique<ErrorToken>("INTERNAL ERROR: Incorrect Token created", pos);
        }
};