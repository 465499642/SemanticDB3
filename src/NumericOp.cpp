#include <string>

#include "NumericOp.h"
#include "ContextList.h"
#include "Sequence.h"

Sequence NumericOp::Compile(ContextList& context, const Sequence& seq) const {
    Sequence result(seq);
    result.multiply(value);
    return result;
}

Sequence NumericOp::Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const {
    Sequence result(seq);
    result.multiply(value);
    return result;
}

Sequence NumericOp::Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const {
    Sequence result(seq);
    result.multiply(value);
    return result;
}


const std::string NumericOp::to_string() const {
    return std::string(std::to_string(value));  // why?
}
