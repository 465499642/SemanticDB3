#include <string>
#include <vector>
#include "OpRule.h"
#include "SingleOpRule.h"
#include "ContextList.h"
#include "Sequence.h"
#include "OpSeq.h"


void OpRule::push(SingleOpRule &single_op_rule) {
    op_rule_vec.push_back(single_op_rule);
}

Sequence OpRule::Compile(ContextList& context) const {
    Sequence seq2;
    for (const auto &seq: op_rule_vec) {
        Sequence compiled_seq = seq.Compile(context);
        switch (seq.symbol_type()) {  // should this be in the parser??
            case SPLUS: { seq2.add(compiled_seq); break; }
            // case SMINUS: { compiled_seq.multiply(-1); seq2.add(compiled_seq); break; }
            case SMINUS: { seq2.add(compiled_seq); break; } // the SMINUS branch is now handled inside OpSeq
            case SSEQ: { seq2.append(compiled_seq); break; } // I don't think it makes sense to do the same with SSEQ, SMERGE, SMERGE2 though.
            case SMERGE: { seq2.merge(compiled_seq); break; }
            case SMERGE2: { seq2.merge(compiled_seq, " "); break; }
        }
    }
    return seq2;
}

Sequence OpRule::Compile(ContextList& context, const ulong label_idx) const {
    Sequence seq2;
    for (const auto &seq: op_rule_vec) {
        Sequence compiled_seq = seq.Compile(context, label_idx);
        switch (seq.symbol_type()) {  // should this be in the parser??
            case SPLUS: { seq2.add(compiled_seq); break; }
            case SMINUS: { seq2.add(compiled_seq); break; } // the SMINUS branch is now handled inside OpSeq
            case SSEQ: { seq2.append(compiled_seq); break; } // I don't think it makes sense to do the same with SSEQ, SMERGE, SMERGE2 though.
            case SMERGE: { seq2.merge(compiled_seq); break; }
            case SMERGE2: { seq2.merge(compiled_seq, " "); break; }
        }
    }
    return seq2;
}

Sequence OpRule::Compile(ContextList& context, const std::vector<Sequence>& args) const {
    Sequence seq2;
    for (const auto &seq: op_rule_vec) {
        Sequence compiled_seq = seq.Compile(context, args);
        switch (seq.symbol_type()) {  // should this be in the parser??
            case SPLUS: { seq2.add(compiled_seq); break; }
            case SMINUS: { seq2.add(compiled_seq); break; } // the SMINUS branch is now handled inside OpSeq
            case SSEQ: { seq2.append(compiled_seq); break; } // I don't think it makes sense to do the same with SSEQ, SMERGE, SMERGE2 though.
            case SMERGE: { seq2.merge(compiled_seq); break; }
            case SMERGE2: { seq2.merge(compiled_seq, " "); break; }
        }
    }
    return seq2;
}

const std::string OpRule::to_string() const {
    std::string s = "";
    for (const auto &seq: op_rule_vec) {
        s += seq.to_string();
    }
    return s;
}

