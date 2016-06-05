#include "string"
#include "Number.h"

double LPQ::Number::Eval() const
{
    return v;
}

std::string LPQ::Number::Dump() const
{
    return std::to_string(v);
}
