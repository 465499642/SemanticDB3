#include <string>
#include <iostream>

#include "OpSeq.h"
#include "BaseOp.h"
#include "Sequence.h"

OpSeq::OpSeq(BaseOp* b_op) {
    op_type = SPLUS;
    op_seq.push_back(b_op);
}

OpSeq::OpSeq(unsigned int type, BaseOp* b_op) {
    op_type = type;
    op_seq.push_back(b_op);
}

void OpSeq::append(BaseOp* b_op) {
    op_seq.push_back(b_op);
}

Sequence OpSeq::Compile(ContextList& context, Sequence& seq) {
    Sequence result = seq;
    while (!op_seq.empty()) {
        result = op_seq.back()->Compile(context, result);
        op_seq.pop_back();
    }
    return result;
}

std::string OpSeq::to_string() {
    std::string s = "";
    switch(op_type) {
        case SPLUS: s = " + "; break;
        case SMINUS: s = " - "; break;
        case SSEQ: s = " . "; break;
        case SMERGE: s = " _ "; break;
        case SMERGE2: s = " __ "; break;
    }
    bool first_pass = true;
    for (auto op: op_seq ) {
        if (first_pass) {
            s += op->to_string();
            first_pass = false;
        } else {
            s += " " + op->to_string();
        }
    }
    return s;
}

