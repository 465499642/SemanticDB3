#include <iostream>
#include <string>
#include <utility>
#include "KetMap.h"
#include "BaseRule.h"
#include "NewContext.h"
#include "Superposition.h"
#include "Sequence.h"
#include "Frame.h"
#include "StoredRule.h"
#include "MemoizingRule.h"


NewContext::NewContext(const std::string& s) {
    name = s;
}

void NewContext::learn(const std::string& op, const std::string& label, BaseRule* brule){
    if (op == "supported-ops") { return;}
    if (brule->size() == 0) {return; }
    ulong op_idx, label_idx;
    op_idx = ket_map.get_idx("op: " + op);
    label_idx = ket_map.get_idx(label);
    Frame frame;

    if (rules_dict.find(label_idx) == rules_dict.end()) {
        sort_order.push_back(label_idx);
        rules_dict[label_idx] = frame;
    }
    rules_dict[label_idx].learn(op_idx, brule);
}


void NewContext::learn(const std::string& op, const std::string& label, const std::string& srule){
    if (op == "supported-ops") { return;}
    if (srule == "") {return; }
    ulong op_idx, label_idx;
    op_idx = ket_map.get_idx("op: " + op);
    label_idx = ket_map.get_idx(label);
    Frame frame;

//    Sequence seq_rule(srule);
    Superposition *rule = new Superposition(srule);
    BaseRule* brule;
    brule = rule;

    if (rules_dict.find(label_idx) == rules_dict.end()) {
        sort_order.push_back(label_idx);
        rules_dict[label_idx] = frame;
    }
    rules_dict[label_idx].learn(op_idx, brule);
}

/*
BaseRule* NewContext::recall(const std::string& op, const std::string& label) {
    BaseRule* result;
    ulong op_idx, label_idx;
    op_idx = ket_map.get_idx("op: " + op);
    label_idx = ket_map.get_idx(label);

    if (rules_dict.find(label_idx) == rules_dict.end()) {
        Superposition *sp = new Superposition();
        result = sp;
        return result;
    }
    result = rules_dict[label_idx].recall(op_idx);
    return result;
}
*/

BaseRule* NewContext::recall(const std::string& op, const std::string& label) {
    BaseRule* result;
    ulong op_idx, star_idx, trial_label_idx;
    op_idx = ket_map.get_idx("op: " + op);
    trial_label_idx = ket_map.get_idx(label);

    if (rules_dict.find(trial_label_idx) != rules_dict.end()) {
        result = rules_dict[trial_label_idx].recall(op_idx);
        if (result->size() != 0) { return result; };
    }

    star_idx = ket_map.get_idx("*");  // implement label descent, not sure cost of this vs just splitting strings approach
    auto label_split_idx = ket_map.get_split_idx(trial_label_idx);
    while (!label_split_idx.empty()) {
        label_split_idx.pop_back();
        label_split_idx.push_back(star_idx);
        trial_label_idx = ket_map.get_idx(label_split_idx);
        // std::cout << "trial_label: " << ket_map.get_str(trial_label_idx) << std::endl;

        if (rules_dict.find(trial_label_idx) != rules_dict.end()) {
            result = rules_dict[trial_label_idx].recall(op_idx);
            if (result->size() != 0) { return result; };
        }
        label_split_idx.pop_back();
    }

    Superposition *sp = new Superposition();
    result = sp;

    return result;
}

void NewContext::print_universe() {
    std::string s, op, label;
    ulong supported_ops_idx;
    Frame frame;
    BaseRule* rule;

    supported_ops_idx = ket_map.get_idx("op: supported-ops");

    s += "------------------------------------------\n";
    s += "|context> => |context: " + name + ">\n\n";

    for (const ulong label_idx: sort_order) {
        label = ket_map.get_str(label_idx);
        frame = rules_dict[label_idx];
        rule = frame.recall(supported_ops_idx);
        s += "supported-ops |" + label + "> => " + rule->to_string() + "\n";
        for (const ulong op_idx: frame.supported_ops()) {
            ulong op_split_idx = ket_map.get_split_idx(op_idx).back();
            op = ket_map.get_str(op_split_idx);
            rule = frame.recall(op_idx);
            std::string rule_type;
            if (rule->type() == STOREDRULE) {
                rule_type = "#";
            }
            else if (rule->type() == MEMOIZINGRULE) {
                rule_type = "!";
            }
            s += op + " |" + label + "> " + rule_type + "=> " + rule->to_string() + "\n";
        }
        s += "\n";
    }

    s += "------------------------------------------\n";

    std::cout << s;
}
