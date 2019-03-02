#ifndef BRACKETOP_H
#define BRACKETOP_H

#include <string>
#include <vector>

#include "BaseOp.h"
#include "Sequence.h"
#include "ContextList.h"
#include "OpSeq.h"


class BracketOp : public BaseOp {
    private:
        std::vector<OpSeq> op_seq_vec;

    public:
        BracketOp(OpSeq &op_seq) { op_seq_vec.push_back(op_seq); }
        void push(OpSeq &op_seq) { op_seq_vec.push_back(op_seq); }
        Sequence Compile(ContextList& context, const Sequence& seq) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const;
        const std::string to_string() const;

};

#endif

