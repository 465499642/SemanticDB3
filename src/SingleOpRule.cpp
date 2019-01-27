#include <string>
#include "SingleOpRule.h"
#include "Sequence.h"
#include "Ket.h"

SingleOpRule::SingleOpRule(BaseRule* b_rule2) {
    op_seq = new OpSeq();
    b_rule = b_rule2;
}

SingleOpRule::SingleOpRule(OpSeq* op_seq2, BaseRule* b_rule2) {
    op_seq = op_seq2;
    b_rule = b_rule2;
}

Sequence SingleOpRule::Compile(ContextList& context) {
    Sequence seq;
    // seq = op_seq->Compile(context, b_rule->to_seq()); // fix later, by using const Sequence& seq
    // Sequence b_seq = b_rule->to_seq();
    Sequence b_seq = b_rule->Compile(context);
    seq = op_seq->Compile(context, b_seq);
    return seq;
}

std::string SingleOpRule::to_string() {
    std::string s;
    if (b_rule->type() == KET) {
        s = op_seq->to_string() + " " + b_rule->to_string();
    } else {
        s = op_seq->to_string() + " ( " + b_rule->to_string() + " )";
    }
    return s;
}
