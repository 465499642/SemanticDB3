#include <iostream>
#include <string>

#include "SimpleOp.h"
#include "ContextList.h"
#include "Sequence.h"
#include "KetMap.h"
#include "BaseRule.h"
#include "Ket.h"


Sequence SimpleOp::Compile(ContextList& context, Sequence& seq) { // make more elaborate later.
    Sequence result;
    for (auto sp: seq) {
        Superposition sp2;
        for (auto k: sp) {
            Superposition sp3 = context.recall(op_idx, k.label_idx())->to_sp();
            sp3.multiply(k.value());
            sp2.add(sp3);
        }
        result.append(sp2);
    }
    return result;
}

std::string SimpleOp::to_string() {
    return ket_map.get_str(op_idx);
}

