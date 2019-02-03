#include <iostream>
#include <string>
#include <vector>
#include "KetMap.h"
#include "Sequence.h"
#include "FnOp.h"

Sequence FnOp::Compile(ContextList& context, Sequence& seq) {
    std::vector<Sequence> args;
    args.push_back(seq);
    for (auto op_rule: op_rules) {
        Sequence tmp = op_rule->Compile(context);
        args.push_back(tmp);
        std::cout << "arg: " << tmp.to_string() << std::endl;
    }
    BaseRule *brule = context.fn_recall(op_idx, op_rules.size());
    std::cout << "brule: " << brule->to_string() << std::endl;
    return brule->Compile(context, args);
}

const std::string FnOp::to_string() const {
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
