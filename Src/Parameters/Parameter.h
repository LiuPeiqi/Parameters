#ifndef LPQ_PARAMETERS_PARAMETER_H
#define LPQ_PARAMETERS_PARAMETER_H
#include <memory>
#include <string>

#include "Factor.h"

namespace LPQ {
    class Parameter;
    typedef std::shared_ptr<Parameter> ParameterPtr;
    class Parameter :
        public Factor {
    public:
        Parameter();
        Parameter(const std::string& name);
        Parameter(const std::string& name, const Factor& factor);
        Parameter(const std::string& name, const Parameter& param);
        Parameter(const std::string& name, const FactorPtr factor_p);
        Parameter(const std::string& name, const ParameterPtr param_p);
        Parameter(const Parameter& param);
        Parameter& operator= (const Factor&);
        Parameter& operator= (const FactorPtr);
        bool IsAssigned() const;
        bool IsAnonymous()const;
        void Assign(const Factor&);
        void Assign(const FactorPtr);
        double Eval()const override;
        std::string Dump()const override;
        const std::string& Name() const;
    private:
        std::string name;
        FactorPtr factor;
        bool anonymous;
    };
}
#endif // !LPQ_PARAMETERS_PARAMETER_H#pragma once
