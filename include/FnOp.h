#ifndef FNOP_H
#define FNOP_H

#include <string>
#include <vector>

#include "BaseOp.h"
#include "Sequence.h"
#include "ContextList.h"
#include "KetMap.h"
#include "OpRule.h"

class FnOp : public BaseOp {
    private:
        ulong op_idx;
        std::vector<OpRule*> op_rules;

    public:
        FnOp(const ulong idx) { op_idx = idx; }
        FnOp(const ulong idx, std::vector<OpRule*> *op_rules2) { op_idx = idx; op_rules = *op_rules2; }
        void push(OpRule *op_rule) { op_rules.push_back(op_rule); }
        Sequence Compile(ContextList& context, const Sequence& seq) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const;
        Sequence Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const;
        const std::string to_string() const;

};

#endif

