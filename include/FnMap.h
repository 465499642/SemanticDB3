#ifndef FNMAP_H
#define FNMAP_H

#include <unordered_map>
#include <functional>
#include "ContextList.h"
#include "Sequence.h"
#include "Superposition.h"


class FnMap {
    private:
    public:
        FnMap();  // this is where we register our functions and operators.

        // below are our tables:
        std::unordered_map<ulong, std::function<Sequence(const Sequence*)> > built_in;

        std::unordered_map<ulong, std::function<double(const double)> > sigmoids;
        std::unordered_map<ulong, std::function<Sequence(const Ket&)> > ket_fn;
        std::unordered_map<ulong, std::function<Sequence(const Superposition&)> > sp_fn;

        std::unordered_map<ulong, std::function<Sequence(const Sequence&, const Sequence&)> > whitelist_1;
        std::unordered_map<ulong, std::function<Sequence(const Sequence&, const Sequence&, const Sequence&)> > whitelist_2;
        std::unordered_map<ulong, std::function<Sequence(const Sequence&, const Sequence&, const Sequence&, const Sequence&)> > whitelist_3;
        std::unordered_map<ulong, std::function<Sequence(const Sequence&, const Sequence&, const Sequence&, const Sequence&, const Sequence&)> > whitelist_4;

        std::unordered_map<ulong, std::function<Sequence(ContextList&, const Sequence&, const Sequence&)> > context_whitelist_1;
        std::unordered_map<ulong, std::function<Sequence(ContextList&, const Sequence&, const Sequence&, const Sequence&)> > context_whitelist_2;
        std::unordered_map<ulong, std::function<Sequence(ContextList&, const Sequence&, const Sequence&, const Sequence&, const Sequence&)> > context_whitelist_3;
        std::unordered_map<ulong, std::function<Sequence(ContextList&, const Sequence&, const Sequence&, const Sequence&, const Sequence&, const Sequence&)> > context_whitelist_4;

        void print() const;
};

extern FnMap fn_map;

#endif
