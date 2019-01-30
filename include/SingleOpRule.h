#ifndef SINGLEOPRULE_H
#define SINGLEOPRULE_H

#define SINGLEOPRULE 5

#include <string>
#include "BaseRule.h"
#include "Sequence.h"
#include "Ket.h"
#include "Superposition.h"
#include "ContextList.h"
#include "OpSeq.h"


class SingleOpRule : public BaseRule {
    private:
        OpSeq* op_seq;
        BaseRule* b_rule;

    public:
        SingleOpRule(BaseRule* b_rule2);
        SingleOpRule(OpSeq* op_seq2, BaseRule* b_rule2);
        unsigned int symbol_type() { return op_seq->symbol_type(); };
        Sequence Compile(ContextList& context);
        Sequence Compile(ContextList& context, const ulong label_idx);
        Sequence Compile(ContextList& context, std::vector<Sequence>& args);

        int type() { return SINGLEOPRULE; };
        const ulong size() { return 1; };
        std::string to_string();

        BaseRule* b_add(BaseRule* brule) { return this; }; // do something better here later.
        BaseRule* b_append(BaseRule* brule) { return this; };

        Ket to_ket() { Ket tmp; return tmp; };
        Superposition to_sp() { Superposition tmp; return tmp; };
        Sequence to_seq() { Sequence tmp; return tmp; };

};

#endif

