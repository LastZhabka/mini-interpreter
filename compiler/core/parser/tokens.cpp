 #include <string>
 using namespace std;
 
 

class Token {
    private:
        int position;
    public:
        Token(int position) : position(position) {
        }

        virtual string toString() = 0;
        
        int getPosition() {
            return position;
        }
};

class KeywordToken : public Token {
    private:
        string value;
    public:
        KeywordToken(int position, string value) : Token(position), value(value) {

        }

        string toString() override {
            return "KeywordToken(" + value + ")(" + to_string(getPosition()) + ")";
        }
};

class IdentifierToken : public Token {
    private:
        string name;
    public:
        IdentifierToken(int position, string name) : Token(position), name(name) {
        
        }

        string toString() override {
            return "IdentifierToken(" + name + ")(" + to_string(getPosition()) + ")";
        }
};

class PrimTypeToken : public Token {
    private:
        string value;
    public:
        PrimTypeToken(int position, string value) : Token(position), value(value) {

        }

        string toString() override {
            return "PrimTypeToken(" + value + ")(" + to_string(getPosition()) + ")";
        }
};

class IntLitToken : public Token {
    private:
        int value;
    public:
        IntLitToken(int position, int value) : Token(position), value(value) {

        }

        string toString() override {
            return "IntLitToken(" + to_string(value) + ")(" + to_string(getPosition()) + ")";
        }
};

class StringLitToken : public Token {
    private:
        string value;
    public:
        StringLitToken(int position, string value) : Token(position), value(value) {

        }

        string toString() override {
            return "StringLitToken(" + value + ")(" + to_string(getPosition()) + ")";
        }
};

class BoolLitToken : public Token {
    private:
        bool value;
    public:
        BoolLitToken(int position, bool value) : Token(position), value(value) {

        }

        string toString() override {
            return "BoolLitToken(" + to_string(value) + ")(" + to_string(getPosition()) + ")";
        }
};

class NullLitToken : public Token {
    private:
    public:
        NullLitToken(int position) : Token(position) {
            
        }

        string toString() override {
            return "NullLitToken(null)(" + to_string(getPosition()) + ")";
        }
}

class DelimiterToken : public Token {
    private:
        string value;
    public:
        DelimiterToken(int position, string value) : Token(position), value(value) {

        }

        string toString() override {
            return "DelimiterToken(" + value + ")(" + to_string(getPosition()) + ")";
        }
};

class OperatorToken : public Token {
    private:
        string name;
    public:
        OperatorToken(int position, string name) : Token(position), name(name) {

        }

        string toString() override {
            return "OperatorToken(" + name + ")(" + to_string(getPosition()) + ")";
        }
};

class CommentToken : public Token {
    private:
        string text;
    public:
        CommentToken(int position, string text) : Token(position), text(text) {

        }

        string toString() override {
            return "CommentToken(" + text + ")(" + to_string(getPosition()) + ")";
        }
};

class SpaceToken : public Token {
    private:
    public:
        SpaceToken(int position) : Token(position) {

        }

        string toString() override {
            return "SpaceToken()(" + to_string(getPosition()) + ")";
        }
};

class ErrorToken : public Token {
    private:
        string content;
    public:
        ErrorToken(int position, string content) : Token(position), content(content) {

        }

        string toString() override {
            return "ErrorToken(" + content + ")(" + to_string(getPosition()) + ")";
        }
};

class EOFToken : public Token {
    public:
        EOFToken(int position) : Token(position) {

        }

        string toString() override {
            return "EOFToken()(" + to_string(getPosition()) + ")";
        }
};