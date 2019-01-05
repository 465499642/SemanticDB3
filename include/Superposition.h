#ifndef SUPERPOSITION_H
#define SUPERPOSITION_H

#define SUPERPOSITION 1

#include <unordered_map>
#include <string>

#include "KetMap.h"
#include "Ket.h"

class Superposition {
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
        std::string to_string();

};

#endif
