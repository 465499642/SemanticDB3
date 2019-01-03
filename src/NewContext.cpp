#include <iostream>
#include <string>
#include <utility>
#include "KetMap.h"
#include "NewContext.h"
#include "Superposition.h"
#include "Sequence.h"


NewContext::NewContext(const std::string& s) {
    name = s;
}

void NewContext::learn(const std::string& op, const std::string& label, const std::string& srule){
    if (op == "supported-ops") { return;}
    if (srule == "") {return; }
    ulong op_idx, label_idx, supported_ops_idx;
    op_idx = ket_map.get_idx(op);
    label_idx = ket_map.get_idx(label);
    std::pair<ulong, ulong> op_label_idx;

    supported_ops_idx = ket_map.get_idx("supported-ops");
    Superposition empty;

//    Sequence seq_rule(srule);
    Superposition rule(srule);

    op_label_idx = std::make_pair(supported_ops_idx, label_idx);
    if (ket_rules_dict.find(op_label_idx) == ket_rules_dict.end()) {
        ket_rules_dict[op_label_idx] = empty;
    }
    ket_rules_dict[op_label_idx].add("op: " + op);

    op_label_idx = std::make_pair(op_idx, label_idx);
    ket_rules_dict[op_label_idx] = rule;
}

Superposition NewContext::recall(const std::string& op, const std::string& label) {
    Superposition result;
    ulong op_idx, label_idx;
    op_idx = ket_map.get_idx(op);
    label_idx = ket_map.get_idx(label);

    std::pair<ulong, ulong> op_label_idx;
    op_label_idx = std::make_pair(op_idx, label_idx);

    result = ket_rules_dict[op_label_idx];
    return result;
}

void NewContext::print_universe() {
    std::string s, op, label;
    std::pair<ulong, ulong> op_label_idx;
    ulong op_idx, label_idx;
    Superposition rule;

    s += "------------------------------------------\n";
    s += "|context> => |context: " + name + ">\n\n";

    for (auto rule_pair: ket_rules_dict) {
        op_label_idx = rule_pair.first;
        op_idx = op_label_idx.first;
        label_idx = op_label_idx.second;
        rule = rule_pair.second;
        op = ket_map.get_str(op_idx);
        label = ket_map.get_str(label_idx);
        s += op + " |" + label + "> => " + rule.to_string() + "\n";
    }
    s += "\n------------------------------------------\n";

    std::cout << s;
}
