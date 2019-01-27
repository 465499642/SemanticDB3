#ifndef STORED_RULE_H
#define STORED_RULE_H

#define STOREDRULE 3

#include <string>
#include "BaseRule.h"
#include "OpRule.h"


class StoredRule : public BaseRule {
    private:
        OpRule *s_rule;

    public:
        StoredRule(const std::string& s) {s_rule = new OpRule(); }; // do something better here later.
        StoredRule(OpRule *op_rule) {s_rule = op_rule; };
        int type() { return STOREDRULE; };
        const ulong size() { return s_rule->size(); };
        std::string to_string() { return s_rule->to_string(); };

        BaseRule* b_add(BaseRule* brule) { return this; }; // do something better here later.
        BaseRule* b_append(BaseRule* brule) { return this; };

        Ket to_ket() { Ket tmp; return tmp; };
        Superposition to_sp() { Superposition tmp; return tmp; };
        Sequence to_seq() { Sequence tmp; return tmp; };

        Sequence Compile(ContextList& context) { return s_rule->Compile(context); };

};

#endif
