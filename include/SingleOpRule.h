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
        const unsigned int symbol_type() const { return op_seq->symbol_type(); };
        Sequence Compile(ContextList& context) const;
        Sequence Compile(ContextList& context, const ulong label_idx) const;
        Sequence Compile(ContextList& context, const std::vector<Sequence>& args) const;

        const int type() const { return SINGLEOPRULE; };
        const ulong size() const { return 1; };
        const std::string to_string() const;

        BaseRule* b_add(BaseRule* brule) { return this; }; // do something better here later.
        BaseRule* b_append(BaseRule* brule) { return this; };

        Ket to_ket() const { Ket tmp; return tmp; };
        Superposition to_sp() const { Superposition tmp; return tmp; };
        Sequence to_seq() const { Sequence tmp; return tmp; };

};

#endif

