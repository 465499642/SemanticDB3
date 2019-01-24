#ifndef SINGLECOMPOUNDSEQ_H
#define SINGLECOMPOUNDSEQ_H

#include <string>
#include "BaseCompoundSeq.h"
#include "Sequence.h"
#include "ContextList.h"
#include "OpSeq.h"
#include "BaseRule.h"


#define SPLUS 0
#define SMINUS 1
#define SSEQ 2
#define SMERGE 3
#define SMERGE2 4


class SingleCompoundSeq : public BaseCompoundSeq {
    private:
        unsigned int op_type;
        OpSeq* op_seq;
        BaseRule* b_rule;

    public:
        SingleCompoundSeq(OpSeq* op_seq2, BaseRule* b_rule2);
        SingleCompoundSeq(unsigned int type, OpSeq* op_seq2, BaseRule* b_rule2);
        Sequence Compile(ContextList& context);
        std::string to_string();
};

#endif

