#include <string>

#include "BaseOp.h"
#include "PoweredOp.h"
#include "Sequence.h"

PoweredOp::PoweredOp(BaseOp* base_op, const unsigned int power) {
    b_op = base_op;
    pow = power;
}

Sequence PoweredOp::Compile(ContextList& context, Sequence& seq) {
    Sequence result = seq;
    for (unsigned int i = 0; i < pow; i++) {
        result = b_op->Compile(context, result);
    }
    return result;
}

std::string PoweredOp::to_string() {
    std::string s = "";
    s = b_op->to_string() + "^" + std::to_string(pow);
    return s;
}
