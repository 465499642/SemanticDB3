#ifndef POWEREDOP_H
#define POWEREDOP_H

#include "BaseOp.h"

class PoweredOp : public BaseOp {
    private:
        BaseOp* b_op;
        unsigned int pow;

    public:
        PoweredOp(BaseOp* base_op, const unsigned int power);
        Sequence Compile(ContextList& context, Sequence& seq);
        const std::string to_string() const;
};

#endif
