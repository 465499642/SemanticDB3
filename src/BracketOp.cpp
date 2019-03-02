#include <iostream>
#include <string>
#include "BracketOp.h"
#include "Sequence.h"
#include "OpSeq.h"

Sequence BracketOp::Compile(ContextList& context, const Sequence& seq) const {
    Sequence seq2;
    for (const auto &op_seq : op_seq_vec) {
        Sequence compiled_seq = op_seq.Compile(context, seq);
        // std::cout << "op_seq: " << op_seq.to_string() << std::endl;
        // std::cout << "op_seq symbol type: " << op_seq.symbol_type() << std::endl;
        // std::cout << "compiled_seq: " << compiled_seq.to_string() << std::endl;
        switch (op_seq.symbol_type()) {
            case SPLUS: { seq2.add(compiled_seq); break; }
            case SMINUS: { seq2.add(compiled_seq); break; }
            case SSEQ: { seq2.append(compiled_seq); break; }
            case SMERGE: { seq2.merge(compiled_seq); break; }
            case SMERGE2: { seq2.merge(compiled_seq, " "); break; }
        }
    }
    std::cout << "BracketOp::seq2: " << seq2.to_string() << std::endl;
    return seq2;
}

Sequence BracketOp::Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const {
    Sequence seq2;
    for (const auto &op_seq : op_seq_vec) {
        Sequence compiled_seq = op_seq.Compile(context, seq, label_idx);
        switch (op_seq.symbol_type()) {
            case SPLUS: { seq2.add(compiled_seq); break; }
            case SMINUS: { seq2.add(compiled_seq); break; }
            case SSEQ: { seq2.append(compiled_seq); break; }
            case SMERGE: { seq2.merge(compiled_seq); break; }
            case SMERGE2: { seq2.merge(compiled_seq, " "); break; }
        }
    }
    std::cout << "BracketOp::seq2: " << seq2.to_string() << std::endl;
    return seq2;
}

Sequence BracketOp::Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const {
    Sequence seq2;
    for (const auto &op_seq : op_seq_vec) {
        Sequence compiled_seq = op_seq.Compile(context, seq, args);
        switch (op_seq.symbol_type()) {
            case SPLUS: { seq2.add(compiled_seq); break; }
            case SMINUS: { seq2.add(compiled_seq); break; }
            case SSEQ: { seq2.append(compiled_seq); break; }
            case SMERGE: { seq2.merge(compiled_seq); break; }
            case SMERGE2: { seq2.merge(compiled_seq, " "); break; }
        }
    }
    std::cout << "BracketOp::seq2: " << seq2.to_string() << std::endl;
    return seq2;
}


const std::string BracketOp::to_string() const {
    std::string s = "(";
    bool first_pass = true;
    for (const auto &op_seq : op_seq_vec) {
        if (first_pass) {
            s += op_seq.to_string();
            first_pass = false;
        } else {
            s += op_seq.to_string();
        }
    }
    return s + ")";
}
