#ifndef MEMOIZING_RULE_H
#define MEMOIZING_RULE_H

#define MEMOIZINGRULE 4

#include <string>
#include "BaseRule.h"
#include "OpRule.h"

class MemoizingRule : public BaseRule {
    private:
        OpRule *m_rule;

    public:
        MemoizingRule(const std::string& s) {m_rule = new OpRule(); }; // do something better here later.
        MemoizingRule(OpRule *op_rule) { m_rule = op_rule; };
        int type() { return MEMOIZINGRULE; };
        const ulong size() { return m_rule->size(); };
        std::string to_string() { return m_rule->to_string(); };

        BaseRule* b_add(BaseRule* brule) { return this; }; // do something better here later.
        BaseRule* b_append(BaseRule* brule) { return this; };

        Ket to_ket() { Ket tmp; return tmp; };
        Superposition to_sp() { Superposition tmp; return tmp; };
        Sequence to_seq() { Sequence tmp; return tmp; };

        Sequence Compile(ContextList& context) { return m_rule->Compile(context); };
        Sequence Compile(ContextList& context, const ulong label_idx) { return m_rule->Compile(context, label_idx); }
};

#endif
