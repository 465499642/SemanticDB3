#ifndef NUMERIROP_H
#define NUMERICOP_H

#include <string>

#include "BaseOp.h"
#include "Sequence.h"
#include "ContextList.h"


class NumericOp : public BaseOp {
    private:
        double value;

    public:
        NumericOp(const double d) { value = d; };
        Sequence Compile(ContextList& context, const Sequence& seq) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const;
        const std::string to_string() const;

};

#endif
