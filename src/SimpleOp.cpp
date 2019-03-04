#include <iostream>
#include <string>

#include "SimpleOp.h"
#include "ContextList.h"
#include "Sequence.h"
#include "KetMap.h"
#include "BaseRule.h"
#include "Ket.h"
#include "FnMap.h"


/*
// buggy:
// eg:
//     op |foo> #=> |x> . |y>
//     op |bah> => op |foo>
// we get:
//     op |bah> => |x>
//
Sequence SimpleOp::Compile(ContextList& context, Sequence& seq) { // make more elaborate later.
    Sequence result;
    for (auto sp: seq) {
        Superposition sp2;
        for (auto k: sp) {
            // Superposition sp3 = context.recall(op_idx, k.label_idx())->to_sp();
            BaseRule *b_rule = context.active_recall(op_idx, k.label_idx());
            // std::cout << "b_rule: " << b_rule->to_string() << std::endl;
            // std::cout << "b_rule type: " << b_rule->type() << std::endl;
            Superposition sp3 = b_rule->to_sp();
            sp3.multiply(k.value());
            sp2.add(sp3);
        }
        result.append(sp2);
    }
    return result;
}
*/

Sequence SimpleOp::Compile(ContextList& context, const Sequence& seq) const {
    if (fn_map.sigmoids.find(op_idx) != fn_map.sigmoids.end()) {
        auto sigmoid = fn_map.sigmoids[op_idx];
        return seq.apply_sigmoid(sigmoid);
    } else if (fn_map.built_in.find(op_idx) != fn_map.built_in.end()) {
        auto fn = fn_map.built_in[op_idx];
        return fn(&seq);
    } else if (fn_map.ket_fn.find(op_idx) != fn_map.ket_fn.end()) {
        auto fn = fn_map.ket_fn[op_idx];
        return seq.apply_ket_fn(fn);
    } else if (fn_map.sp_fn.find(op_idx) != fn_map.sp_fn.end()) {
        auto fn = fn_map.sp_fn[op_idx];
        return seq.apply_sp_fn(fn);
    }
    Sequence result;
    for (const auto &sp: seq) {
        Sequence seq2;
        for (const auto &k: sp) {
            BaseRule *b_rule = context.active_recall(op_idx, k.label_idx());
            // std::cout << "b_rule: " << b_rule->to_string() << std::endl;
            // std::cout << "b_rule type: " << b_rule->type() << std::endl;
            Sequence seq3 = b_rule->to_seq();
            seq3.multiply(k.value());
            seq2.add(seq3);
        }
        result.append(seq2);
    }
    return result;
}

Sequence SimpleOp::Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const {
    return this->Compile(context, seq);
}

Sequence SimpleOp::Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& args) const {
    return this->Compile(context, seq);
}


const std::string SimpleOp::to_string() const {
    return ket_map.get_str(op_idx);
}

