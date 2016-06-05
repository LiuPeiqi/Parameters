#include <iostream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Parameters.h"
using namespace LPQ;
using namespace std;
TEST(Parameters, LoadParameters)
{
    double err = 0.000001;
    stringstream vt_s("vt=0.7");
    auto vt = LoadParameter(vt_s);
    EXPECT_NEAR(vt->Eval(), 0.7, err);
    stringstream v1_s("v1=vt-0.1");
    auto v1 = LoadParameter(v1_s);
    EXPECT_NEAR(v1->Eval(), 0.6, err);
    stringstream v2_s("v2=(v1 - (0.4 + (vt -1)))");
    auto v2 = LoadParameter(v2_s);
    EXPECT_NEAR(v2->Eval(), 0.5, err);
    EXPECT_NEAR(LoadParameter(stringstream(vt->Dump()))->Eval(), vt->Eval(), err);
    EXPECT_NEAR(LoadParameter(stringstream(v1->Dump()))->Eval(), v1->Eval(), err);
    EXPECT_NEAR(LoadParameter(stringstream(v2->Dump()))->Eval(), v2->Eval(), err);
}
