#include <string>
#include "KetMap.h"
#include "FnOp.h"

Sequence FnOp::Compile(ContextList& context, Sequence& seq) {
    return seq;
}

std::string FnOp::to_string() {
    std::string s = ket_map.get_str(op_idx) + "(";
    bool first_pass = true;
    for (auto op_rule : op_rules) {
        if (first_pass) {
            s += op_rule->to_string();
            first_pass = false;
        } else {
            s += "," + op_rule->to_string();
        }
    }
    s += ")";
    return s;
}
