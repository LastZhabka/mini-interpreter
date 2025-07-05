#ifndef TREE_MODULE_H
#define TREE_MODULE_H

#include <string>
#include <memory>
#include <vector>

enum class Type {
    int_type,
    string_type,
    null_type,
    bool_type,
    float_type,
    unresolved
};


class Puts;
class Addition;
class Subtraction;
class Multiplication;
class Division;
class GreaterThan;
class LowerThan;
class Equal;
class NotEqual;
class Min;
class Abs;
class Assignment;
class Concatenation;
class Replacement;
class Substring;
class Lowercase;
class Uppercase;
class Identifier;
class IntLiteral;
class FloatLiteral;
class StringLiteral;
class BoolLiteral;
class NullLiteral;
class ParseTempFunctionExpr;
class ErrorExpr;
class ParseTempExpr;


// abstract syntax tree
class Expr {
    private:
        std::vector<std::shared_ptr<Expr>> target; // Tree structure
    public:
        virtual ~Expr(); //  = default

        void push_back(std::shared_ptr<Expr> elem);
};  


// Functions:

class Puts : public Expr {
    private:
    public:
        Puts(std::shared_ptr<Expr> target);
};

class Addition : public Expr{
    private:
    public:
        Addition(std::vector<std::shared_ptr<Expr>> operands);
};

class Subtraction : public Expr{
    private:
    public:
        Subtraction(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Multiplication : public Expr{
    private:
    public:
        Multiplication(std::vector<std::shared_ptr<Expr>> operands);
};

class Division : public Expr{
    private:
    public:
        Division(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class GreaterThan : public Expr{
    private:
    public:
        GreaterThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class LowerThan : public Expr{
    private:
    public:
        LowerThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Equal : public Expr{
    private:
    public:
        Equal(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class NotEqual : public Expr{
    private:
    public:
        NotEqual(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Min : public Expr{
    private:
    public:
        Min(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Abs : public Expr{
    private:
    public:
        Abs(std::shared_ptr<Expr> target);
};

// Assignment  x := 1
class Assignment : public Expr{
    private:
    public:
        Assignment(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

// String Ops
class Concatenation : public Expr{
    private:
    public:
        Concatenation(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Replacement : public Expr{
    private:
    public:
        Replacement(std::shared_ptr<Expr> source, std::shared_ptr<Expr> target, std::shared_ptr<Expr> replacement);
};

class Substring : public Expr{
    private:
    public:
        Substring(std::shared_ptr<Expr> source, std::shared_ptr<Expr> l, std::shared_ptr<Expr> r);
};

class Lowercase : public Expr{
    private:
    public:
        Lowercase(std::shared_ptr<Expr> target);
};

class Uppercase : public Expr{
    private:
    public:
        Uppercase(std::shared_ptr<Expr> target);
};

// Identifier

class Identifier : public Expr {
    private:
    public:
        Identifier(std::shared_ptr<Expr> name);
};

// Literals
class IntLiteral : public Expr {
    private:
        int value;
    public:
        IntLiteral(int value);
};

class FloatLiteral : public Expr {
    private:
        float value;
    public:
        FloatLiteral(float value);
};

class StringLiteral : public Expr {
    private:
        std::string value;
    public:
        StringLiteral(std::string value);
};

class BoolLiteral : public Expr {
    private:
        bool value;
    public:
        BoolLiteral(bool value);
};

class NullLiteral : public Expr {
    private:
    public:
        NullLiteral();
};

class ErrorExpr : public Expr {
    private:
    public:
        ErrorExpr();
};

// expr for the parse tree (dummy)

class ParseTempFunctionExpr : public Expr {
    private:
    public:
        ParseTempFunctionExpr ();
};

class ParseTempExpr : public Expr {
    private:
    public:
        ParseTempExpr();
};



class ExprCreator {
    public:
        ExprCreator();

        /*
            We always initialize AST node with some dummy value, during the parsing we will inject
            the real value into the node.
        */

        std::shared_ptr<Expr> operator()(std::string expr_type);
};

#endif // TREE_MODULE_H