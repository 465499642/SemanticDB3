#include <iostream>
#include <string>

#include "SimpleOp.h"
#include "ContextList.h"
#include "Sequence.h"
#include "KetMap.h"
#include "BaseRule.h"
#include "Ket.h"


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

Sequence SimpleOp::Compile(ContextList& context, Sequence& seq) {
    Sequence result;
    for (auto sp: seq) {
        Sequence seq2;
        for (auto k: sp) {
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


std::string SimpleOp::to_string() {
    return ket_map.get_str(op_idx);
}

