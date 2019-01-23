#ifndef MEMOIZING_RULE_H
#define MEMOIZING_RULE_H

#define MEMOIZINGRULE 4

#include <string>
#include "BaseRule.h"

class MemoizingRule : public BaseRule {
    private:
        std::string mrule;

    public:
        MemoizingRule(const std::string& s) {mrule = s; };
        int type() { return MEMOIZINGRULE; };
        const ulong size() { return mrule.length(); };
        std::string to_string() { return mrule; };

        BaseRule* b_add(BaseRule* brule) { return this; }; // do something better here later.
        BaseRule* b_append(BaseRule* brule) { return this; };

        Ket to_ket() { Ket tmp; return tmp; };
        Superposition to_sp() { Superposition tmp; return tmp; };
        Sequence to_seq() { Sequence tmp; return tmp; };
};

#endif
