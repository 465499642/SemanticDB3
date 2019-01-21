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
        ulong size() { return srule.length(); };
        std::string to_string() { return srule; };

        Ket to_ket() { Ket tmp; return tmp; };
        Superposition to_sp() { Superposition tmp; return tmp; };
};

#endif
