#ifndef LPQ_PARAMETERS_BINARY_H
#define LPQ_PARAMETERS_BINARY_H
#include <functional>
#include <memory>

#include "Factor.h"
#include "Expression.h"
namespace LPQ {
    typedef std::function<double(const FactorPtr, const FactorPtr)> BinaryFunction;
    class BinaryOperator {
    public :
        BinaryOperator(const BinaryFunction& func, const std::string& sig);
        double operator()(const FactorPtr, const FactorPtr)const;
        const std::string& GetSign()const;
    private:
        const BinaryFunction& f;
        std::string sign;
    };
    extern const BinaryOperator ADD;
    extern const BinaryOperator MINUS;
    class Binary :
        public Expression {
    public:
        Binary(const BinaryOperator & op, const FactorPtr left, const FactorPtr right);
        Binary(const BinaryOperator & op, const FactorPtr left, const Factor& right);
        Binary(const BinaryOperator & op, const Factor& left, const FactorPtr right);
        Binary(const BinaryOperator & op, const Factor& left, const Factor& right);
        Binary(const Binary& r);
        double Eval()const override;
        std::string Dump()const override;
    private:
        const BinaryOperator & bi_op;
        FactorPtr left;
        FactorPtr right;
    };
}
#endif // !LPQ_PARAMETERS_BINARY_H#pragma once
