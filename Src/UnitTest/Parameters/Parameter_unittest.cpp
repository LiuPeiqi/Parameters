#include <memory>
#include <string>
#include <iostream>

#include "gtest/gtest.h"

#include "Parameters.h"
using namespace LPQ;
using namespace std;
TEST(Parameters, Number)
{
    const double PI = 3.1415926;
    const double ABS_ERROR = 0.00000001;
    Number pi(PI);
    NumberPtr pi_p = dynamic_pointer_cast<Number>(CreateAndDefaultCopy(pi));
    EXPECT_NEAR(pi.Eval(), PI, ABS_ERROR);
    EXPECT_EQ(pi.Dump(), to_string(PI));
}

TEST(Parameters, Parameter)
{
    const double PI = 3.1415926;
    Number adapter(PI);
    Parameter pi("pi", adapter);
    cout << pi.Dump() << endl;
    Number PI_2(PI * 2);
    Parameter pi_2("2Pi");
    EXPECT_EQ(pi_2.IsAssigned(), false);
    pi_2.Assign(PI_2);
    EXPECT_EQ(pi_2.IsAssigned(), true);
    EXPECT_EQ(pi_2.IsAnonymous(), false);
    EXPECT_EQ(pi_2.Name(), "2Pi");
    pi = PI_2;
    EXPECT_NEAR(pi.Eval(), PI_2.Eval(), 0.000000001);
    Parameter anonymous;
    EXPECT_EQ(anonymous.IsAnonymous(), true);
    cout << anonymous.Dump() << endl;
    auto pi_p = CreateAndDefaultCopy(adapter);
    anonymous = pi_p;
    EXPECT_NEAR(anonymous.Eval(), PI, 0.000000001);
    Parameter other_pi(anonymous);
    cout << other_pi.Dump() << endl;
    EXPECT_EQ(other_pi.IsAnonymous(), true);
    EXPECT_EQ(other_pi.IsAssigned(), true);
    EXPECT_NEAR(other_pi.Eval(), PI, 0.000000001);
    auto p_p = CreateAndDefaultCopy(pi_2);
    Parameter pp("ptr ref", p_p);
    EXPECT_EQ(pp.Eval(), pi_2.Eval());
    Parameter ppp("ppp", pi_p);
    EXPECT_EQ(ppp.Eval(), pi_p->Eval());
}

TEST(Parameters, Binary)
{
    NumberPtr op7=make_shared<Number>(0.7);
    Number op1(0.1);
    auto vt=make_shared<Parameter>("vt", op7);
    cout << vt->Dump() << endl;
    Binary bias_exp1(ADD, vt, op1);
    Binary bias_exp2(MINUS, vt, op7);
    Parameter bias1("v1", bias_exp1);
    cout << bias1.Dump() << endl;
    Parameter bias2("v2", bias_exp2);
    cout << bias2.Dump() << endl;
    EXPECT_NEAR(bias1.Eval(), 0.8, 0.000001);
    EXPECT_NEAR(bias2.Eval(), 0,0.000001);
    Binary bias3_expr(ADD,bias_exp1, bias_exp2);
    Parameter bias3;
    bias3 = bias3_expr;
    cout << bias3.Dump()<<endl;
}
