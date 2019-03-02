#ifndef SIMPLEOP_H
#define SIMPLEOP_H

#include <string>

#include "BaseOp.h"
#include "Sequence.h"
#include "ContextList.h"
#include "KetMap.h"


class SimpleOp : public BaseOp {
    private:
        ulong op_idx;

    public:
        SimpleOp(const ulong idx) { op_idx = idx; }
        SimpleOp(const std::string& s) { op_idx = ket_map.get_idx(s); }
        Sequence Compile(ContextList& context, const Sequence& seq) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const;
        const std::string to_string() const;

};

#endif

