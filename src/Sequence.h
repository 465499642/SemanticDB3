#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>

#include "Ket.h"

class Superposition;

class Sequence {
    private:
        std::vector<Superposition> seq;

    public:
        Sequence() {};
        ~Sequence() {};
        Sequence(Ket& k);
        Sequence(Superposition& sp);
        Sequence operator+(Sequence& b);
        void add(Ket& k);
        void add(Superposition& sp);
        void add(Sequence& seq);
        std::string to_string();
};

#endif
