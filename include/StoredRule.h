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
        const int type() const { return STOREDRULE; };
        const ulong size() const { return s_rule->size(); };
        const std::string to_string() const { return s_rule->to_string(); };

        BaseRule* b_add(BaseRule* brule) { return this; }; // do something better here later.
        BaseRule* b_append(BaseRule* brule) { return this; };

        Ket to_ket() const { Ket tmp; return tmp; };
        Superposition to_sp() const { Superposition tmp; return tmp; };
        Sequence to_seq() const { Sequence tmp; return tmp; };

        Sequence Compile(ContextList& context) const { return s_rule->Compile(context); };
        Sequence Compile(ContextList& context, const ulong label_idx) const { return s_rule->Compile(context, label_idx); }
        Sequence Compile(ContextList& context, const std::vector<Sequence>& args) const { return s_rule->Compile(context, args); }
};

#endif
