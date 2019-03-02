#ifndef BASEOP_H
#define BASEOP_H

#include <string>
#include "Sequence.h"
#include "ContextList.h"

class BaseOp {
    private:

    public:
        virtual const std::string to_string() const = 0;
        virtual Sequence Compile(ContextList& context, const Sequence& seq) const = 0;
        virtual Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const = 0;
        virtual Sequence Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const = 0;
};

#endif

