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
        std::unordered_map<ulong, Frame> fn_rules_dict;
        std::vector<ulong> fn_sort_order;

    public:
        NewContext(const std::string& s);
        std::string get_name() const;
        void learn(const ulong op_idx, const ulong label_idx, BaseRule* brule);
        void learn(const std::string& op, const std::string& label, BaseRule* brule);
        void learn(const std::string& op, const std::string& label, const std::string& rule);
        void add_learn(const ulong op_idx, const ulong label_idx, BaseRule* brule);
        void add_learn(const std::string& op, const std::string& label, BaseRule* brule);
        void seq_learn(const ulong op_idx, const ulong label_idx, BaseRule* brule);
        void seq_learn(const std::string& op, const std::string& label, BaseRule* brule);

        BaseRule* recall(const std::string& op, const std::string& label);
        BaseRule* recall(const ulong op_idx, const ulong label_idx);
//        BaseRule* active_recall(const ulong op_idx, const ulong label_idx);

        void fn_learn(const ulong op_idx, const ulong param_size, BaseRule* brule);
        BaseRule* fn_recall(const ulong op_idx, const ulong param_size);
        void print_universe() const;
};

#endif
