#include <string>
#include <vector>
#include "CompoundSeq.h"
#include "SingleCompoundSeq.h"
#include "ContextList.h"
#include "Sequence.h"
#include "OpSeq.h"


void CompoundSeq::append(SingleCompoundSeq &single_compound_seq) {
    compound_seq_vec.push_back(single_compound_seq);
}

Sequence CompoundSeq::Compile(ContextList& context) {
    Sequence seq2;
    for (auto seq: compound_seq_vec) {
        Sequence compiled_seq = seq.Compile(context);
        switch (seq.type()) {  // should this be in the parser??
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

std::string CompoundSeq::to_string() {
    std::string s = "";
    for (auto seq: compound_seq_vec) {
        s += seq.to_string();
    }
    return s;
}

