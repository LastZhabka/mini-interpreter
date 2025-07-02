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
class Substraction;
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


/*
Through visitor we will implement other functions of AST Nodes
For example we can implement get_node_type 
Or we can implement get_expr_type
Or we can implement printer for the AST

TODO: Implement things above
      Implement Parse Tree Intermediate Node
*/

class ExprVisitor {
    public:
        virtual ~ExprVisitor();

        virtual void visit(const Puts& expr);

        virtual void visit(const Addition& expr);
        
        virtual void visit(const Substraction& expr);
        
        virtual void visit(const Multiplication& expr);
        
        virtual void visit(const Division& expr);
        
        virtual void visit(const GreaterThan& expr);
        
        virtual void visit(const LowerThan& expr);
        
        virtual void visit(const Equal& expr);
        
        virtual void visit(const NotEqual& expr);

        virtual void visit(const Min& expr);
        
        virtual void visit(const Abs& expr);

        virtual void visit(const Assignment& expr);
        
        virtual void visit(const Concatenation& expr);
        
        virtual void visit(const Replacement& expr);
        
        virtual void visit(const Substring& expr);

        virtual void visit(const Lowercase& expr);
        
        virtual void visit(const Uppercase& expr);

        virtual void visit(const Identifier& expr);
        
        virtual void visit(const IntLiteral& expr);

        virtual void visit(const FloatLiteral& expr);
        
        virtual void visit(const StringLiteral& expr);

        virtual void visit(const BoolLiteral& expr);
        
        virtual void visit(const NullLiteral& expr);
};

// abstract syntax tree
class Expr {
    private:
        std::vector<std::shared_ptr<Expr>> target; // Tree structure
    public:
        virtual ~Expr() = default;
        virtual void accept(std::shared_ptr<ExprVisitor> visitor) = 0;
};  


// Mutation:
class Puts : public Expr {
    private:
    public:
        Puts(std::shared_ptr<Expr> target);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

// Functions:

class Addition : public Expr{
    private:
    public:
        Addition(std::vector<std::shared_ptr<Expr>> operands);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class Subtraction : public Expr{
    private:
    public:
        Subtraction(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class Multiplication : public Expr{
    private:
    public:
        Multiplication(std::vector<std::shared_ptr<Expr>> operands);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class Division : public Expr{
    private:
    public:
        Division(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};


class GreaterThan : public Expr{
    private:
    public:
        GreaterThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class LowerThan : public Expr{
    private:
    public:
        LowerThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class Equal : public Expr{
    private:
    public:
        Equal(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class NotEqual : public Expr{
    private:
    public:
        NotEqual(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class Min : public Expr{
    private:
    public:
        Min(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class Abs : public Expr{
    private:
    public:
        Abs(std::shared_ptr<Expr> target);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

// Assignment  x := 1
class Assignment : public Expr{
    private:
    public:
        Assignment(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};


// String Ops
class Concatenation : public Expr{
    private:
    public:
        Concatenation(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class Replacement : public Expr{
    private:
    public:
        Replacement(std::shared_ptr<Expr> source, std::shared_ptr<Expr> target, std::shared_ptr<Expr> replacement);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class Substring : public Expr{
    private:
    public:
        Substring(std::shared_ptr<Expr> source, std::shared_ptr<Expr> l, std::shared_ptr<Expr> r);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class Lowercase : public Expr{
    private:
    public:
        Lowercase(std::shared_ptr<Expr> target);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class Uppercase : public Expr{
    private:
    public:
        Uppercase(std::shared_ptr<Expr> target);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};



// Identifier

class Identifier : public Expr {
    private:
    public:
        Identifier(std::shared_ptr<Expr> name);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};




// Literals
class IntLiteral : public Expr {
    private:
        int value;
    public:
        IntLiteral(int value);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class FloatLiteral : public Expr {
    private:
        float value;
    public:
        FloatLiteral(float value);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class StringLiteral : public Expr {
    private:
        std::string value;
    public:
        StringLiteral(std::string value);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class BoolLiteral : public Expr {
    private:
        bool value;
    public:
        BoolLiteral(bool value);

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

class NullLiteral : public Expr {
    private:
    public:
        NullLiteral();

        void accept(std::shared_ptr<ExprVisitor> visitor);
};

#endif TREE_MODULE_H