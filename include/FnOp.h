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
        void push(OpRule *op_rule) { op_rules.push_back(op_rule); }
        Sequence Compile(ContextList& context, Sequence& seq);
        std::string to_string();

};

#endif

