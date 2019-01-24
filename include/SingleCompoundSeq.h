#ifndef SINGLECOMPOUNDSEQ_H
#define SINGLECOMPOUNDSEQ_H

#include <string>
#include "BaseCompoundSeq.h"
#include "Sequence.h"
#include "ContextList.h"
#include "OpSeq.h"
#include "BaseRule.h"


class SingleCompoundSeq : public BaseCompoundSeq {
    private:
        OpSeq* op_seq;
        BaseRule* b_rule;

    public:
        SingleCompoundSeq(OpSeq* op_seq2, BaseRule* b_rule2);
        unsigned int type() { return op_seq->type(); };
        Sequence Compile(ContextList& context);
        std::string to_string();
};

#endif

