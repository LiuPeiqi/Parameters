#include <string>
#include <typeinfo>

#include "Factor.h"
#include "Parameter.h"
using namespace std;
namespace LPQ {
    Parameter::Parameter() :
        name(string("Param_") + std::to_string(reinterpret_cast<unsigned int>(this))),
        factor(nullptr),
        anonymous(true){}
    Parameter::Parameter(const std::string & _name):
        name(_name),
        factor(nullptr),
        anonymous(false){}

    Parameter::Parameter(const std::string & _name, const Factor &_f):
        name(_name),
        anonymous(false)
    {
        factor = CreateAndDefaultCopy(_f);
    }

    Parameter::Parameter(const std::string & _name, const Parameter &param):
        name(_name),
        factor(param.factor),
        anonymous(false){}

    Parameter::Parameter(const std::string & _name, const FactorPtr _f):
        name(_name),
        factor(_f),
        anonymous(false){}

    Parameter::Parameter(const std::string & _name, const ParameterPtr param_p):
        name(_name),
        factor(param_p->factor),
        anonymous(false){}

    Parameter::Parameter(const Parameter &r):
        factor(r.factor),
        anonymous(r.anonymous)
    {
        if (r.IsAnonymous()) {
            name = string("Param_") + std::to_string(reinterpret_cast<unsigned int>(this));
        }else{
            name = r.name + "_" + std::to_string(reinterpret_cast<unsigned int>(this));
        }
    }

    Parameter & Parameter::operator=(const Factor & _f)
    {
        Assign(_f);
        return *this;
    }

    Parameter & Parameter::operator=(const FactorPtr _f_p)
    {
        Assign(_f_p);
        return *this;
    }

    bool Parameter::IsAssigned() const
    {
        return factor != nullptr;
    }

    bool Parameter::IsAnonymous() const
    {
        return anonymous;
    }

    void Parameter::Assign(const Factor & _f)
    {
        factor = CreateAndDefaultCopy(_f);
    }

    void Parameter::Assign(const FactorPtr _f_p)
    {
        factor = _f_p;
    }

    double Parameter::Eval() const
    {
        return factor == nullptr ? double() : factor->Eval();
    }

    std::string Parameter::Dump() const
    {
        if (factor == nullptr) {
            return name + " is not assigned!";
        }
        static auto& parameter_type = typeid(Parameter);
        if (typeid(*factor) == parameter_type) {
            return name + " = " + dynamic_pointer_cast<Parameter>(factor)->Name();
        }
        else {
            return name + " = " + factor->Dump();
        }
    }

    const std::string & Parameter::Name() const
    {
        return name;
    }

}
