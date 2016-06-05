#ifndef LPQ_PARAMETERS_FACTOR_H
#define LPQ_PARAMETERS_FACTOR_H
#include <iosfwd>
#include <memory>
namespace LPQ {
    class Factor {
    public:
        virtual double Eval()const = 0;
        virtual std::string Dump()const = 0;
    };
    typedef std::shared_ptr<Factor> FactorPtr;
    FactorPtr CreateAndDefaultCopy(const Factor& f);
    FactorPtr LoadParameter(std::istream&);
    void ResetParameters();
}
#endif // !LPQ_PARAMETERS_FACTOR_H#pragma once
