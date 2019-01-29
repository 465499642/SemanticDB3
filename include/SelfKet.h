#ifndef SELFKET_H
#define SELFKET_H

#include <string>
#include "BaseRule.h"
#include "KetMap.h"

#define SELFKET 7

class Ket;
class Superposition;
class Sequence;
class ContextList;

class SelfKet : public BaseRule {
    private:
        unsigned int idx;
        double value;

    public:
        SelfKet() { idx = 1; value = 1;}
        SelfKet(const unsigned int idx2) { idx = idx2; value = 1;}
        SelfKet(const unsigned int idx2, const double d) { idx = idx2; value = d; }
        int type() { return SELFKET; }
        std::string to_string();
        const ulong size() { return 1; }
        void multiply(const double d) { value *= d; }
        Ket to_ket();
        Superposition to_sp();
        Sequence to_seq();
        BaseRule* b_add(BaseRule* brule) { return this; }
        BaseRule* b_append(BaseRule* brule) { return this; }
        Sequence Compile(ContextList& context);
        Sequence Compile(ContextList& context, const ulong label_idx);
};

#endif

