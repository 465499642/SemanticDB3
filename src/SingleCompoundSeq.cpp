#include <string>
#include "SingleCompoundSeq.h"
#include "Sequence.h"


SingleCompoundSeq::SingleCompoundSeq(OpSeq* op_seq2, BaseRule* b_rule2) {
    op_seq = op_seq2;
    b_rule = b_rule2;
}

Sequence SingleCompoundSeq::Compile(ContextList& context) {
    Sequence seq;
    // seq = op_seq->Compile(context, b_rule->to_seq()); // fix later, by using const Sequence& seq
    Sequence b_seq = b_rule->to_seq();
    seq = op_seq->Compile(context, b_seq);
    return seq;
}

std::string SingleCompoundSeq::to_string() {
    std::string s = op_seq->to_string() + " ( " + b_rule->to_string() + " )";
    return s;
}
