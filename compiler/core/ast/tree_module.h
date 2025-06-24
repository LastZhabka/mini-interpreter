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


// abstract syntax tree
class Expr {
    private:
        Type expr_type;
    public:
        Expr(); // Initialize it as unresolved type, we will run type_check later
        
        virtual ~Expr() = default;
        
        virtual Type get_type();
};  


// Mutation:
class Puts : public Expr {
    private:
        std::shared_ptr<Expr> target;
    public:
        Puts(std::shared_ptr<Expr> target);
};

// Functions:

class Addition : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        Addition(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Subtraction : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        Subtraction(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Multiplication : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        Multiplication(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Division : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        Division(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};


class GreaterThan : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        GreaterThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class LowerThan : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        LowerThan(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Equal : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        Equal(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class NotEqual : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        NotEqual(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Min : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        Min(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Abs : public Expr{
    private:
        std::shared_ptr<Expr> target; 
    public:
        Abs(std::shared_ptr<Expr> target);
};

// Assignment  x := 1
class Assignment : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        Assignment(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};


// String Ops
class Concatenation : public Expr{
    private:
        std::shared_ptr<Expr> lhs, rhs; 
    public:
        Concatenation(std::shared_ptr<Expr> lhs, std::shared_ptr<Expr> rhs);
};

class Replacement : public Expr{
    private:
        std::shared_ptr<Expr> source, target, replacement; 
    public:
        Replacement(std::shared_ptr<Expr> source, std::shared_ptr<Expr> target, std::shared_ptr<Expr> replacement);
};

class Substring : public Expr{
    private:
        std::shared_ptr<Expr> source, l, r; 
    public:
        Substring(std::shared_ptr<Expr> source, std::shared_ptr<Expr> l, std::shared_ptr<Expr> r);
};

class Lowercase : public Expr{
    private:
        std::shared_ptr<Expr> target; 
    public:
        Lowercase(std::shared_ptr<Expr> target);
};

class Uppercase : public Expr{
    private:
        std::shared_ptr<Expr> target; 
    public:
        Uppercase(std::shared_ptr<Expr> target);
};



// Identifier

class Identifier : public Expr {
    // idk
    private:
        std::string name;
    public:
        Identifier(std::string name);
};




// Literals
class IntLiteral : public Expr {
    private:
        int value;
    public:
        IntLiteral(int value);
    
        Type get_type() override;
        
        int get_value();
};

class FloatLiteral : public Expr {
    private:
        float value;
    public:
        FloatLiteral(float value);
    
        Type get_type() override;
        
        float get_value();
};

class StringLiteral : public Expr {
    private:
        std::string value;
    public:
        StringLiteral(std::string value);
    
        Type get_type() override;
        
        std::string get_value();
};

class BoolLiteral : public Expr {
    private:
        bool value;
    public:
        BoolLiteral(bool value);
    
        Type get_type() override;
        
        bool get_value();
};

class NullLiteral : public Expr {
    private:
    public:
        NullLiteral();

        Type get_type() override;
};





#endif TREE_MODULE_H