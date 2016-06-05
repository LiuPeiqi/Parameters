#include <memory>
#include <string>
#include <typeinfo>

#include "Binary.h"
#include "Expression.h"
#include "Factor.h"
#include "Parameter.h"
namespace LPQ {
    BinaryOperator::BinaryOperator(const BinaryFunction & func, const std::string & sig):
        f(func),
        sign(sig){}

    double BinaryOperator::operator()(const FactorPtr left, const FactorPtr right) const
    {
        return f(left,right);
    }

    const std::string & BinaryOperator::GetSign() const
    {
        return sign;
    }

    const BinaryFunction ADD_func = [](const FactorPtr l, const FactorPtr r)->double {
        return l->Eval() + r->Eval();
    };

    const BinaryOperator ADD(ADD_func, "+");

    const BinaryFunction MINUS_func = [](const FactorPtr l, const FactorPtr r) {
        return l->Eval() - r->Eval();
    };

    const BinaryOperator MINUS(MINUS_func, "-");

    Binary::Binary(const BinaryOperator & op, const FactorPtr _left, const FactorPtr _right):
        bi_op(op),
        left(_left),
        right(_right){}
    Binary::Binary(const BinaryOperator & op, const FactorPtr _left, const Factor & _right):
        bi_op(op),
        left(_left)
    {
        right = CreateAndDefaultCopy(_right);
    }
    Binary::Binary(const BinaryOperator & op, const Factor & _left, const FactorPtr _right):
        bi_op(op),
        right(_right)
    {
        left = CreateAndDefaultCopy(_left);
    }
    Binary::Binary(const BinaryOperator & op, const Factor & _left, const Factor & _right):
        bi_op(op)
    {
        left = CreateAndDefaultCopy(_left);
        right = CreateAndDefaultCopy(_right);
    }
    Binary::Binary(const Binary & r):
        bi_op(r.bi_op),
        left(r.left),
        right(r.right){}

    double Binary::Eval() const
    {
        return bi_op(left,right);
    }

    std::string Binary::Dump() const
    {
        std::string dump;
        auto left_parameter = std::dynamic_pointer_cast<Parameter>(left);
        auto left_express = std::dynamic_pointer_cast<Expression>(left);
        if (left_parameter != nullptr) {
            dump = left_parameter->Name();
        }
        else if (left_express != nullptr) {
            dump = std::string("(") + left_express->Dump() + ")";
        }
        else {
            dump = left->Dump();
        }

        dump += (std::string(" ") + bi_op.GetSign() + " ");

        auto right_parameter = std::dynamic_pointer_cast<Parameter>(right);
        auto right_express = std::dynamic_pointer_cast<Expression>(right);
        if (right_parameter != nullptr) {
            dump += right_parameter->Name();
        }
        else if (right_express != nullptr) {
            dump += (std::string("(") + right_express->Dump() + ")");
        }
        else{
            dump += right->Dump();
        }
        return dump;
    }
}
