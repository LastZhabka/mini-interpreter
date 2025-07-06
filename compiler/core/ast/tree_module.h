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


class ExprVisitor;


// abstract syntax tree
class Expr {
    private:
        std::vector<std::shared_ptr<Expr>> target; // Tree structure
    public:
        virtual ~Expr(); //  = default

        virtual void accept(std::shared_ptr<ExprVisitor> visitor) = 0;

        std::vector<std::shared_ptr<Expr>> get_kids();

        void reassign_children(std::vector<std::shared_ptr<Expr>> target_);

        void modify(int index, std::shared_ptr<Expr> elem);

        void push_back(std::shared_ptr<Expr> elem);

};  


// Functions:

class Puts : public Expr {
    private:
    public:
        Puts(std::shared_ptr<Expr> target);

        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Addition : public Expr{
    private:
    public:
        Addition(std::vector<std::shared_ptr<Expr>> operands);

        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Subtraction : public Expr{
    private:
    public:
        Subtraction(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Multiplication : public Expr{
    private:
    public:
        Multiplication(std::vector<std::shared_ptr<Expr>> operands);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Division : public Expr{
    private:
    public:
        Division(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class GreaterThan : public Expr{
    private:
    public:
        GreaterThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class LowerThan : public Expr{
    private:
    public:
        LowerThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Equal : public Expr{
    private:
    public:
        Equal(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class NotEqual : public Expr{
    private:
    public:
        NotEqual(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Min : public Expr{
    private:
    public:
        Min(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Abs : public Expr{
    private:
    public:
        Abs(std::shared_ptr<Expr> target);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

// Assignment  x := 1
class Assignment : public Expr{
    private:
    public:
        Assignment(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

// String Ops
class Concatenation : public Expr{
    private:
    public:
        Concatenation(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Replacement : public Expr{
    private:
    public:
        Replacement(std::shared_ptr<Expr> source, std::shared_ptr<Expr> target, std::shared_ptr<Expr> replacement);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Substring : public Expr{
    private:
    public:
        Substring(std::shared_ptr<Expr> source, std::shared_ptr<Expr> l, std::shared_ptr<Expr> r);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Lowercase : public Expr{
    private:
    public:
        Lowercase(std::shared_ptr<Expr> target);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class Uppercase : public Expr{
    private:
    public:
        Uppercase(std::shared_ptr<Expr> target);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

// Identifier

class Identifier : public Expr {
    private:
    public:
        Identifier(std::shared_ptr<Expr> name);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

// Literals
class IntLiteral : public Expr {
    private:
        int value;
    public:
        IntLiteral(int value);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class FloatLiteral : public Expr {
    private:
        float value;
    public:
        FloatLiteral(float value);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class StringLiteral : public Expr {
    private:
        std::string value;
    public:
        StringLiteral(std::string value);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class BoolLiteral : public Expr {
    private:
        bool value;
    public:
        BoolLiteral(bool value);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class NullLiteral : public Expr {
    private:
    public:
        NullLiteral();
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class ErrorExpr : public Expr {
    private:
        std::string value;
    public:
        ErrorExpr(std::string value);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

// expr for the parse tree (dummy)

class ParseTempExpr : public Expr {
    private:
        std::string parse_type;
    public:
        ParseTempExpr(std::string parse_type);

        std::string get_parse_type();

        void accept(std::shared_ptr<ExprVisitor> visitor) override;
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


class ExprVisitor {
    public:
        virtual ~ExprVisitor();

        virtual void visit(Puts& expr);

        virtual void visit(Addition& expr);
        
        virtual void visit(Subtraction& expr);
        
        virtual void visit(Multiplication& expr);
        
        virtual void visit(Division& expr);
        
        virtual void visit(GreaterThan& expr);
        
        virtual void visit(LowerThan& expr);
        
        virtual void visit(Equal& expr);
        
        virtual void visit(NotEqual& expr);

        virtual void visit(Min& expr);
        
        virtual void visit(Abs& expr);

        virtual void visit(Assignment& expr);
        
        virtual void visit(Concatenation& expr);
        
        virtual void visit(Replacement& expr);
        
        virtual void visit(Substring& expr);

        virtual void visit(Lowercase& expr);
        
        virtual void visit(Uppercase& expr);

        virtual void visit(Identifier& expr);
        
        virtual void visit(IntLiteral& expr);

        virtual void visit(FloatLiteral& expr);
        
        virtual void visit(StringLiteral& expr);

        virtual void visit(BoolLiteral& expr);
        
        virtual void visit(NullLiteral& expr);

        virtual void visit(ErrorExpr& expr);

        virtual void visit(ParseTempExpr& expr);
};

class ExprTypeVisitor : public ExprVisitor {
    private:
        std::string last_type;
    public:
        
        void clear();

        std::string get_type_of_visited_expr();

        void visit(Puts& expr);

        void visit(Addition& expr);
        
        void visit(Subtraction& expr);
        
        void visit(Multiplication& expr);
        
        void visit(Division& expr);
        
        void visit(GreaterThan& expr);
        
        void visit(LowerThan& expr);
        
        void visit(Equal& expr);
        
        void visit(NotEqual& expr);

        void visit(Min& expr);
        
        void visit(Abs& expr);

        void visit(Assignment& expr);
        
        void visit(Concatenation& expr);
        
        void visit(Replacement& expr);
        
        void visit(Substring& expr);

        void visit(Lowercase& expr);
        
        void visit(Uppercase& expr);

        void visit(Identifier& expr);
        
        void visit(IntLiteral& expr);

        void visit(FloatLiteral& expr);
        
        void visit(StringLiteral& expr);

        void visit(BoolLiteral& expr);
        
        void visit(NullLiteral& expr);

        void visit(ErrorExpr& expr);

        void visit(ParseTempExpr& expr);
};


class ParserTempTypeVisitor : public ExprVisitor {
    private:
        std::string last_type;
    public:
        
        void clear();

        std::string get_type_of_visited_expr();

        void visit(ParseTempExpr& expr) override;
};

#endif // TREE_MODULE_H