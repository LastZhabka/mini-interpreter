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


// Abstract syntax tree
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

class PutsExpr : public Expr {
    private:
    public:
        PutsExpr(std::shared_ptr<Expr> target);

        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class AdditionExpr : public Expr{
    private:
    public:
        AdditionExpr(std::vector<std::shared_ptr<Expr>> operands);

        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class SubtractionExpr : public Expr{
    private:
    public:
        SubtractionExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class MultiplicationExpr : public Expr{
    private:
    public:
        MultiplicationExpr(std::vector<std::shared_ptr<Expr>> operands);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class DivisionExpr : public Expr{
    private:
    public:
        DivisionExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class GreaterThanExpr : public Expr{
    private:
    public:
        GreaterThanExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class LowerThanExpr : public Expr{
    private:
    public:
        LowerThanExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class EqualExpr : public Expr{
    private:
    public:
        EqualExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class NotEqualExpr : public Expr{
    private:
    public:
        NotEqualExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class MinExpr : public Expr{
    private:
    public:
        MinExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class AbsExpr : public Expr{
    private:
    public:
        AbsExpr(std::shared_ptr<Expr> target);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

// SetExpr  x := 1
class SetExpr : public Expr{
    private:
    public:
        SetExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

// String Ops
class ConcatExpr : public Expr{
    private:
    public:
        ConcatExpr(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class ReplaceExpr : public Expr{
    private:
    public:
        ReplaceExpr(std::shared_ptr<Expr> source, std::shared_ptr<Expr> target, std::shared_ptr<Expr> ReplaceExpr);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class SubstrExpr : public Expr{
    private:
    public:
        SubstrExpr(std::shared_ptr<Expr> source, std::shared_ptr<Expr> l, std::shared_ptr<Expr> r);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class LowercaseExpr : public Expr{
    private:
    public:
        LowercaseExpr(std::shared_ptr<Expr> target);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

class UppercaseExpr : public Expr{
    private:
    public:
        UppercaseExpr(std::shared_ptr<Expr> target);
        
        void accept(std::shared_ptr<ExprVisitor> visitor) override;
};

// Identifier
class IdentifierExpr : public Expr {
    private:
    public:
        IdentifierExpr(std::shared_ptr<Expr> name);
        
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

        virtual void visit(PutsExpr& expr);

        virtual void visit(AdditionExpr& expr);
        
        virtual void visit(SubtractionExpr& expr);
        
        virtual void visit(MultiplicationExpr& expr);
        
        virtual void visit(DivisionExpr& expr);
        
        virtual void visit(GreaterThanExpr& expr);
        
        virtual void visit(LowerThanExpr& expr);
        
        virtual void visit(EqualExpr& expr);
        
        virtual void visit(NotEqualExpr& expr);

        virtual void visit(MinExpr& expr);
        
        virtual void visit(AbsExpr& expr);

        virtual void visit(SetExpr& expr);
        
        virtual void visit(ConcatExpr& expr);
        
        virtual void visit(ReplaceExpr& expr);
        
        virtual void visit(SubstrExpr& expr);

        virtual void visit(LowercaseExpr& expr);
        
        virtual void visit(UppercaseExpr& expr);

        virtual void visit(IdentifierExpr& expr);
        
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

        void visit(PutsExpr& expr);

        void visit(AdditionExpr& expr);
        
        void visit(SubtractionExpr& expr);
        
        void visit(MultiplicationExpr& expr);
        
        void visit(DivisionExpr& expr);
        
        void visit(GreaterThanExpr& expr);
        
        void visit(LowerThanExpr& expr);
        
        void visit(EqualExpr& expr);
        
        void visit(NotEqualExpr& expr);

        void visit(MinExpr& expr);
        
        void visit(AbsExpr& expr);

        void visit(SetExpr& expr);
        
        void visit(ConcatExpr& expr);
        
        void visit(ReplaceExpr& expr);
        
        void visit(SubstrExpr& expr);

        void visit(LowercaseExpr& expr);
        
        void visit(UppercaseExpr& expr);

        void visit(IdentifierExpr& expr);
        
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