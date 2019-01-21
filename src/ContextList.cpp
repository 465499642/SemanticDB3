#include <iostream>
#include <string>
#include <vector>

#include "NewContext.h"
#include "ContextList.h"

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

void ContextList::learn(const std::string& op, const std::string& label, BaseRule* brule) {
    data[index].learn(op, label, brule);
}

void ContextList::learn(const std::string& op, const std::string& label, const std::string& rule) {
    data[index].learn(op, label, rule);
}

BaseRule* ContextList::recall(const std::string& op, const std::string& label) {
    return data[index].recall(op, label);
}

BaseRule* ContextList::recall(const ulong op_idx, const ulong label_idx) {
    return data[index].recall(op_idx, label_idx);
}


void ContextList::print_multiverse() {
    for (auto context: data) {
        context.print_universe();
        std::cout << std::endl;
    }
}
