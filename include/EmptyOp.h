#ifndef EMPTYOP_H
#define EMPTYOP_H

#include <string>

#include "BaseOp.h"
#include "Sequence.h"
#include "ContextList.h"


class EmptyOp : public BaseOp {
    private:

    public:
        EmptyOp() { }
        Sequence Compile(ContextList& context, const Sequence& seq) const { return seq; };
        const std::string to_string() const { std::string s = ""; return s; };

};

#endif

