#include <iostream>
#include <string>

#include "SimpleOp.h"
#include "ContextList.h"
#include "Sequence.h"
#include "KetMap.h"
#include "BaseRule.h"
#include "Ket.h"


Sequence SimpleOp::Compile(ContextList& context, Sequence& seq) {
    Sequence result;
    for (auto sp: seq) {
        std::cout << sp.to_string() << std::endl;
        Ket k = sp.to_ket();  // for now, as we don't have an iterator for Superposition class.
        auto rule = context.recall(op_idx, k.label_idx());
        Superposition sp2 = rule->to_sp();
        sp2.multiply(k.value());
        result.append(sp2);
    }
    return result;
}

std::string SimpleOp::to_string() {
    return ket_map.get_str(op_idx);
}

