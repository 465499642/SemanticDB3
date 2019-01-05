#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include <string>

#include "Ket.h"

#define SEQUENCE 2

class Superposition;

class Sequence {
    private:
        std::vector<Superposition> seq;

    public:
        Sequence() {};
        ~Sequence() {};
        Sequence(const std::string& s);
        Sequence(Ket& k);
        Sequence(Superposition& sp);
        Sequence operator+(Sequence& b);
        int type() { return SEQUENCE; };
        ulong size();
        void add(Ket& k);
        void add(Superposition& sp);
        void add(Sequence& seq);
        std::string to_string();
};

#endif
