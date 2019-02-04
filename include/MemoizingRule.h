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
        const int type() const { return MEMOIZINGRULE; };
        const ulong size() const { return m_rule->size(); };
        const std::string to_string() const { return m_rule->to_string(); };

        BaseRule* b_add(BaseRule* brule) { return this; }; // do something better here later.
        BaseRule* b_append(BaseRule* brule) { return this; };

        Ket to_ket() const { Ket tmp; return tmp; };
        Superposition to_sp() const { Superposition tmp; return tmp; };
        Sequence to_seq() const { Sequence tmp; return tmp; };

        Sequence Compile(ContextList& context) const { return m_rule->Compile(context); };
        Sequence Compile(ContextList& context, const ulong label_idx) const { return m_rule->Compile(context, label_idx); }
        Sequence Compile(ContextList& context, const std::vector<Sequence>& args) const { return m_rule->Compile(context, args); }
};

#endif
