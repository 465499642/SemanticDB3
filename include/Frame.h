#ifndef FRAME_H
#define FRAME_H

#include <unordered_map>
#include <vector>

#include "KetMap.h"
#include "Superposition.h"

class Frame {
    private:
        std::vector<ulong> supported_operators;
        std::unordered_map<ulong, Superposition> rules;

    public:
        Frame() {};
        std::vector<ulong> supported_ops();
        void learn(const ulong op_idx, const Superposition& sp);
        Superposition recall(const ulong op_idx);
        void print();
};

#endif
