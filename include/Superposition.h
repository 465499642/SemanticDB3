#ifndef SUPERPOSITION_H
#define SUPERPOSITION_H

#define SUPERPOSITION 1

#include <unordered_map>
#include <string>

#include "KetMap.h"
#include "BaseRule.h"
#include "Ket.h"
#include "SuperpositionIter.h"


class Superposition : public BaseRule {
    private:
        std::unordered_map<ulong, double> sp;
        std::vector<ulong> sort_order;

    public:
        Superposition() {};
        ~Superposition() {};
        Superposition(const ulong idx);
        Superposition(const std::string& s);
        Superposition(const std::string&s, const double v);
        Superposition(const ulong idx, const double v);
        Superposition operator+(Ket& b);
        int type() { return SUPERPOSITION; };
        ulong size();
        // void add(const Ket& a); // bugs out for now
        void add(const ulong idx);
        void add(const std::string& s);
        void add(Ket& a);
        void add(Superposition& a);
        void multiply(const double d);
        std::string to_string();

        Ket to_ket();
        Superposition to_sp();
        Sequence to_seq();

        // SuperpositionIter:
        Ket get(ulong idx) const;
        SuperpositionIter begin () const;
        SuperpositionIter end () const;

        Superposition merge(const Superposition& sp2);
        Superposition merge(const Superposition& sp2, const std::string& s);
};

#endif
