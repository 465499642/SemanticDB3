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
        unsigned int op_type;
        std::vector<BaseOp*> op_seq;

    public:
        OpSeq() { op_type = SPLUS; }
        OpSeq(unsigned int type) { op_type = type; }
        OpSeq(BaseOp* b_op);
        OpSeq(unsigned int type, BaseOp* b_op);

        void append(BaseOp* b_op);
        Sequence Compile(ContextList& context, Sequence& seq);
        std::string to_string();

};

#endif
