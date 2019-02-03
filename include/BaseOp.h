#ifndef BASEOP_H
#define BASEOP_H

#include <string>
#include "Sequence.h"
#include "ContextList.h"

class BaseOp {
    private:

    public:
        virtual const std::string to_string() const = 0;
        virtual Sequence Compile(ContextList& context, Sequence& seq) = 0;

};

#endif

