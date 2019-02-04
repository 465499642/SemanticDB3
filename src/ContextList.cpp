#include <iostream>
#include <string>
#include <vector>

#include "NewContext.h"
#include "ContextList.h"
#include "StoredRule.h"
#include "MemoizingRule.h"


ContextList::ContextList(const std::string& s) {
    name = s;
    index = 0;
    max_index = 1;
    NewContext tmp(name);
    data.push_back(tmp);
}

void ContextList::set(const std::string& s) {
    bool match = false;
    for (ulong k = 0; k < max_index; k++ ) {
        if (data[k].get_name() == s) {
            index = k;
            match = true;
            break;
        }
    }
    if (!match) {
        max_index++;
        index = max_index - 1;
        NewContext tmp(s);
        data.push_back(tmp);
    }
}

void ContextList::learn(const ulong op_idx, const ulong label_idx, BaseRule* brule) {
    data[index].learn(op_idx, label_idx, brule);
}

void ContextList::learn(const std::string& op, const std::string& label, BaseRule* brule) {
    data[index].learn(op, label, brule);
}

void ContextList::learn(const std::string& op, const std::string& label, const std::string& rule) {
    data[index].learn(op, label, rule);
}

void ContextList::add_learn(const ulong op_idx, const ulong label_idx, BaseRule* brule) {
    data[index].add_learn(op_idx, label_idx, brule);
}

void ContextList::add_learn(const std::string& op, const std::string& label, BaseRule* brule) {
    data[index].add_learn(op, label, brule);
}

void ContextList::seq_learn(const ulong op_idx, const ulong label_idx, BaseRule* brule) {
    data[index].seq_learn(op_idx, label_idx, brule);
}

void ContextList::seq_learn(const std::string& op, const std::string& label, BaseRule* brule) {
    data[index].seq_learn(op, label, brule);
}


BaseRule* ContextList::recall(const std::string& op, const std::string& label) {
    return data[index].recall(op, label);
}

BaseRule* ContextList::recall(const ulong op_idx, const ulong label_idx) {
    return data[index].recall(op_idx, label_idx);
}

BaseRule* ContextList::active_recall(const ulong op_idx, const ulong label_idx) {  // not sure this is best place for this code.
    BaseRule* tmp = this->recall(op_idx, label_idx);                               // SimpleOp::Compile is an alternative
    if (tmp->type() == STOREDRULE) {
        Sequence *seq = new Sequence(tmp->Compile(*this, label_idx));
        return seq;
    } else if (tmp->type() == MEMOIZINGRULE) {
        Sequence *seq = new Sequence(tmp->Compile(*this, label_idx));
        this->learn(op_idx, label_idx, seq);
        return seq;
    } else {
        return tmp;
    }
}

void ContextList::fn_learn(const ulong op_idx, const ulong param_size, BaseRule* brule) {
    data[index].fn_learn(op_idx, param_size, brule);
}

BaseRule* ContextList::fn_recall(const ulong op_idx, const ulong param_size) {
    return data[index].fn_recall(op_idx, param_size);
}


void ContextList::print_multiverse() const {
    for (const auto &context: data) {
        context.print_universe();
        std::cout << std::endl;
    }
}

void ContextList::print_universe() const {
    data[index].print_universe();
}
