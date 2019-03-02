#include <string>
#include <iostream>

#include "OpSeq.h"
#include "BaseOp.h"
#include "Sequence.h"

OpSeq::OpSeq(BaseOp* b_op) {
    op_symbol = SPLUS;
    op_seq.push_back(b_op);
}

OpSeq::OpSeq(unsigned int type, BaseOp* b_op) {
    op_symbol = type;
    op_seq.push_back(b_op);
}

void OpSeq::append(BaseOp* b_op) {
    op_seq.push_back(b_op);
}

Sequence OpSeq::Compile(ContextList& context, const Sequence& seq) const {
    Sequence result = seq;
    for (auto it = op_seq.rbegin(); it != op_seq.rend(); ++it) {
        result = (*it)->Compile(context, result);
    }
    if (op_symbol == SMINUS) { result.multiply(-1); } // not 100% sure this should be here.
    return result;
}

Sequence OpSeq::Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const {
    Sequence result = seq;
    for (auto it = op_seq.rbegin(); it != op_seq.rend(); ++it) {
        result = (*it)->Compile(context, result, label_idx);
    }
    if (op_symbol == SMINUS) { result.multiply(-1); } // not 100% sure this should be here.
    return result;
}

Sequence OpSeq::Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const {
    Sequence result = seq;
    for (auto it = op_seq.rbegin(); it != op_seq.rend(); ++it) {
        result = (*it)->Compile(context, result, args);
    }
    if (op_symbol == SMINUS) { result.multiply(-1); } // not 100% sure this should be here.
    return result;
}


const std::string OpSeq::to_string() const {
    std::string s = "";
    switch(op_symbol) {
        case SPLUS: s = " + "; break;
        case SMINUS: s = " - "; break;
        case SSEQ: s = " . "; break;
        case SMERGE: s = " _ "; break;
        case SMERGE2: s = " __ "; break;
    }
    bool first_pass = true;
    for (const auto op: op_seq ) {
        if (first_pass) {
            s += op->to_string();
            first_pass = false;
        } else {
            s += " " + op->to_string();
        }
    }
    return s;
}

