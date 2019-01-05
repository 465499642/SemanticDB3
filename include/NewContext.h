#ifndef NEWCONTEXT_H
#define NEWCONTEXT_H

#include <string>
#include <unordered_map>
#include "Superposition.h"
#include "Frame.h"

class NewContext {
    private:
        std::string name;
        std::unordered_map<ulong, Frame> rules_dict;
        std::vector<ulong> sort_order;

    public:
        NewContext(const std::string& s);
        void learn(const std::string& op, const std::string& label, const std::string& rule);
        BaseRule* recall(const std::string& op, const std::string& label);
        void print_universe();
};

#endif
