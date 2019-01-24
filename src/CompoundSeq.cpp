#include <string>
#include <vector>
#include "CompoundSeq.h"
#include "SingleCompoundSeq.h"
#include "ContextList.h"
#include "Sequence.h"


void CompoundSeq::append(SingleCompoundSeq &single_compound_seq) {
    compound_seq_vec.push_back(single_compound_seq);
}

Sequence CompoundSeq::Compile(ContextList& context) {
    Sequence seq2;
    for (auto seq: compound_seq_vec) {
        seq2.add(seq.Compile(context)); // the other operators - . _ and __ later.
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

