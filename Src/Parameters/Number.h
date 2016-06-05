#ifndef LPQ_PARAMETERS_NUMBER_H
#define LPQ_PARAMETERS_NUMBER_H
#include <memory>
#include <string>

#include "Factor.h"

namespace LPQ {
    class Number :
        public Factor {
    public:
        Number(double _v) :v(_v) {}
        Number():v(double()){}
        Number(const Number & r) :v(r.v) {}
        double Eval()const override;
        std::string Dump()const override;
    private:
        double v;
    };
    typedef std::shared_ptr<Number> NumberPtr;
}
#endif // !LPQ_PARAMETERS_NUMBER_H#pragma once
