/*
    Visitor Pattern  ->  Represents an operation to be performed on the elements of an object structure.
    It lets you define a new operation without changing the classes of the elements on which it operates.
*/

#include <iostream>

// Forward declaration of concrete elements
class NumberExpression;
class AdditionExpression;
class SubtractionExpression;

// Visitor interface
class ExpressionVisitor
{
public:
    virtual void visit(NumberExpression *expression) = 0;
    virtual void visit(AdditionExpression *expression) = 0;
    virtual void visit(SubtractionExpression *expression) = 0;
};

// Abstract expression base class
class Expression
{
public:
    virtual void accept(ExpressionVisitor *visitor) = 0;
};

// Concrete expression classes
class NumberExpression : public Expression
{
public:
    NumberExpression(int value) : value_(value) {}

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
    }

    int getValue() const
    {
        return value_;
    }

private:
    int value_;
};

class AdditionExpression : public Expression
{
public:
    AdditionExpression(Expression *left, Expression *right)
        : left_(left), right_(right) {}

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
    }

    Expression *getLeft() const
    {
        return left_;
    }

    Expression *getRight() const
    {
        return right_;
    }

private:
    Expression *left_;
    Expression *right_;
};

class SubtractionExpression : public Expression
{
public:
    SubtractionExpression(Expression *left, Expression *right)
        : left_(left), right_(right) {}

    void accept(ExpressionVisitor *visitor) override
    {
        visitor->visit(this);
    }

    Expression *getLeft() const
    {
        return left_;
    }

    Expression *getRight() const
    {
        return right_;
    }

private:
    Expression *left_;
    Expression *right_;
};

// Concrete visitor implementation
class Evaluator : public ExpressionVisitor
{
public:
    void visit(NumberExpression *expression) override
    {
        result_ = expression->getValue();
    }

    void visit(AdditionExpression *expression) override
    {
        expression->getLeft()->accept(this);
        int left = result_;
        expression->getRight()->accept(this);
        int right = result_;
        result_ = left + right;
    }

    void visit(SubtractionExpression *expression) override
    {
        expression->getLeft()->accept(this);
        int left = result_;
        expression->getRight()->accept(this);
        int right = result_;
        result_ = left - right;
    }

    int getResult() const
    {
        return result_;
    }

private:
    int result_;
};

int main()
{
    // Build an expression: (10 + (5 - 3))
    Expression *expression =
        new AdditionExpression(new NumberExpression(10),
                               new SubtractionExpression(new NumberExpression(5),
                                                         new NumberExpression(3)));

    // Evaluate the expression using the Evaluator visitor
    Evaluator evaluator;
    expression->accept(&evaluator);
    std::cout << "Result: " << evaluator.getResult() << std::endl;

    // Clean up
    delete expression;

    return 0;
}
