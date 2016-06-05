#include <iostream>
#include <memory>
#include <unordered_map>
#include <regex>
#include <sstream>
#include <string>
#include <typeinfo>

#include "Binary.h"
#include "Factor.h"
#include "Number.h"
#include "Parameter.h"
#include "Parameters.h"
using namespace std;
namespace LPQ {
    FactorPtr CreateAndDefaultCopy(const Factor & f)
    {
        auto& f_t = typeid(f);
        static auto& number_type = typeid(Number);
        static auto& binary_type = typeid(Binary);
        static auto& parameter_type = typeid(Parameter);
        if (f_t == number_type) {
            return make_shared<Number>(dynamic_cast<const Number&>(f));
        }
        else if (f_t == binary_type) {
            return make_shared<Binary>(dynamic_cast<const Binary&>(f));
        }
        else if(f_t == parameter_type){
            return make_shared<Parameter>(dynamic_cast<const Parameter&>(f));
        }
        else {
            return nullptr;
        }
    }
    static void PutBackString(istream& in, const string& s)
    {
        for (auto i = rbegin(s); i != rend(s); ++i) {
            in.putback(*i);
        }
    }

    static unordered_map<string, ParameterPtr> parameter_pool;
    FactorPtr LoadParameter(istream &in)
    {
        static const regex number_re("^[-\\+]?\\d+(\\.\\d+([eE][-\\+]?\\d+)?)?");
        static const regex name_re("^[a-zA-Z_]\\w*");
        static const regex equal_re("^\\=");
        static const regex sign_re("^[-\\+]");
        static const regex lp("^\\(");
        static const regex rp("^\\)");
        string buf;
        FactorPtr left = nullptr;
        while (in) {
            in >> buf;
            smatch result;
            while(buf.size()) {
                regex_search(buf, result, name_re);
                if (result.size()&&(left==nullptr)) {
                    auto iter = parameter_pool.find(result.str());
                    if (iter == end(parameter_pool)) {
                        auto param= make_shared<Parameter>(result.str());
                        parameter_pool[result.str()] = param;
                        left = param;
                    }
                    else {
                        left = iter->second;
                    }
                   goto CONTINUE_LOOP;
                }
                regex_search(buf, result, number_re);
                if (result.size() && (left == nullptr)) {
                    stringstream s(result.str());
                    double d;
                    s >> d;
                    left = make_shared<Number>(d);
                    goto CONTINUE_LOOP;
                }
                regex_search(buf, result, lp);
                if (result.size()) {
                    PutBackString(in, result.suffix().str());
                    left = LoadParameter(in);
                }
                regex_search(buf, result, rp);
                if (result.size()) {
                    return left;
                }
                regex_search(buf, result, equal_re);
                if (result.size()) {
                    PutBackString(in, result.suffix().str());
                    (*dynamic_pointer_cast<Parameter>(left)) = LoadParameter(in);
                    return left;
                }
                regex_search(buf, result, sign_re);
                if (result.size()) {
                    const BinaryOperator *op;
                    if (result.str() == "+") {
                        op = &ADD;
                    }
                    else {
                        op = &MINUS;
                    }
                    PutBackString(in, result.suffix().str());
                    return make_shared<Binary>(*op, left, LoadParameter(in));
                }
            CONTINUE_LOOP:
                buf = result.suffix().str();
            };
        }
        return left;
    }
    void ResetParameters()
    {
        parameter_pool.clear();
    }
}
