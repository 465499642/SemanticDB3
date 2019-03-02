#ifndef POWEREDOP_H
#define POWEREDOP_H

#include "BaseOp.h"

class PoweredOp : public BaseOp {
    private:
        BaseOp* b_op;
        unsigned int pow;

    public:
        PoweredOp(BaseOp* base_op, const unsigned int power);
        Sequence Compile(ContextList& context, const Sequence& seq) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const;
        const std::string to_string() const;
};

#endif
