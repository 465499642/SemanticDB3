#ifndef NEWCONTEXT_H
#define NEWCONTEXT_H

#include <string>
#include <unordered_map>
#include "Superposition.h"
#include "Frame.h"
#include "BaseRule.h"

class NewContext {
    private:
        std::string name;
        std::unordered_map<ulong, Frame> rules_dict;
        std::vector<ulong> sort_order;

    public:
        NewContext(const std::string& s);
        std::string get_name();
        void learn(const std::string& op, const std::string& label, BaseRule* brule);
        void learn(const std::string& op, const std::string& label, const std::string& rule);
        BaseRule* recall(const std::string& op, const std::string& label);
        BaseRule* recall(const ulong op_idx, const ulong label_idx);
        void print_universe();
};

#endif
