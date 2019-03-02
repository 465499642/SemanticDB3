#ifndef OPSEQ_H
#define OPSEQ_H

#include <string>
#include "BaseOp.h"

#define SPLUS 0
#define SMINUS 1
#define SSEQ 2
#define SMERGE 3
#define SMERGE2 4

class OpSeq : public BaseOp {
    private:
        unsigned int op_symbol;
        std::vector<BaseOp*> op_seq;

    public:
        OpSeq() { op_symbol = SPLUS; }
        OpSeq(unsigned int type) { op_symbol = type; }
        OpSeq(BaseOp* b_op);
        OpSeq(unsigned int type, BaseOp* b_op);

        const unsigned int symbol_type() const { return op_symbol; }
        void append(BaseOp* b_op);
        Sequence Compile(ContextList& context, const Sequence& seq) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const;
        const std::string to_string() const;

};

#endif
