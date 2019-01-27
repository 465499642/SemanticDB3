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
        Sequence Compile(ContextList& context);

        int type() { return OPRULE; };
        const ulong size() { return op_rule_vec.size(); };
        std::string to_string();

        BaseRule* b_add(BaseRule* brule) { return this; }; // do something better here later.
        BaseRule* b_append(BaseRule* brule) { return this; };

        Ket to_ket() { Ket tmp; return tmp; };
        Superposition to_sp() { Superposition tmp; return tmp; };
        Sequence to_seq() { Sequence tmp; return tmp; };

};

#endif

