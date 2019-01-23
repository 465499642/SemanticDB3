#ifndef FRAME_H
#define FRAME_H

#include <unordered_map>
#include <vector>

#include "KetMap.h"
#include "BaseRule.h"
#include "Superposition.h"


class Frame {
    private:
        std::vector<ulong> supported_operators;
        std::unordered_map<ulong, BaseRule*> rules;

    public:
        Frame() {};
        std::vector<ulong> supported_ops();
        void learn(const ulong op_idx, BaseRule* brule);
        void add_learn(const ulong op_idx, BaseRule* brule);
        void seq_learn(const ulong op_idx, BaseRule* brule);
        BaseRule* recall(const ulong op_idx);
        void print();
};

#endif
