#ifndef SUPERPOSITION_H
#define SUPERPOSITION_H

#include <map>
#include <string>

#include "KetMap.h"
#include "Ket.h"

class Superposition {
    private:
        std::map<ulong, double> sp;
        std::vector<ulong> sort_order;

    public:
        Superposition() {};
        ~Superposition() {};
        Superposition(const ulong idx);
        Superposition(const std::string& s);
        Superposition(const std::string&s, const double v);
        Superposition(const ulong idx, const double v);
        // Superposition Superposition::operator+(const Ket& a, const Ket& b);
        //Superposition::operator+(const Superposition& b);
        Superposition operator+(Ket& b);
        // Superposition operator+(Ket& a, Ket& b);
        // void add(const Ket& a); // bugs out for now
        void add(Ket& a);
        void add(Superposition& a);
        std::string to_string();

};

#endif
