#ifndef COMPOUNDSEQ_H
#define COMPOUNDSEQ_H

#include <string>
#include <vector>
#include "BaseCompoundSeq.h"
#include "Sequence.h"
#include "ContextList.h"
#include "SingleCompoundSeq.h"


class CompoundSeq : public BaseCompoundSeq {
    private:
        std::vector<SingleCompoundSeq> compound_seq_vec;

    public:
        CompoundSeq() {};
        void append(SingleCompoundSeq &single_compound_seq);
        Sequence Compile(ContextList& context);
        std::string to_string();
};

#endif

