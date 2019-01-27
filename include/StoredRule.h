#ifndef STORED_RULE_H
#define STORED_RULE_H

#define STOREDRULE 3

#include <string>
#include "BaseRule.h"

class StoredRule : public BaseRule {
    private:
        std::string srule;

    public:
        StoredRule(const std::string& s) {srule = s; };
        int type() { return STOREDRULE; };
        const ulong size() { return srule.length(); };
        std::string to_string() { return srule; };

        BaseRule* b_add(BaseRule* brule) { return this; }; // do something better here later.
        BaseRule* b_append(BaseRule* brule) { return this; };

        Ket to_ket() { Ket tmp; return tmp; };
        Superposition to_sp() { Superposition tmp; return tmp; };
        Sequence to_seq() { Sequence tmp; return tmp; };

        Sequence Compile(ContextList& context) { Sequence tmp; return tmp; };

};

#endif
