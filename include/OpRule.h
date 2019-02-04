#ifndef OPRULE_H
#define OPRULE_H

#define OPRULE 6

#include <string>
#include <vector>
#include "BaseRule.h"
#include "Sequence.h"
#include "ContextList.h"
#include "SingleOpRule.h"


class OpRule : public BaseRule {
    private:
        std::vector<SingleOpRule> op_rule_vec;

    public:
        OpRule() {};
        void push(SingleOpRule &single_op_rule);
        Sequence Compile(ContextList& context) const;
        Sequence Compile(ContextList& context, const ulong label_idx) const;
        Sequence Compile(ContextList& context, const std::vector<Sequence>& args) const;

        const int type() const { return OPRULE; };
        const ulong size() const { return op_rule_vec.size(); };
        const std::string to_string() const;

        BaseRule* b_add(BaseRule* brule) { return this; }; // do something better here later.
        BaseRule* b_append(BaseRule* brule) { return this; };

        Ket to_ket() const { Ket tmp; return tmp; };
        Superposition to_sp() const { Superposition tmp; return tmp; };
        Sequence to_seq() const { Sequence tmp; return tmp; };

};

#endif

