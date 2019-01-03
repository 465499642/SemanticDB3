#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>

#include "Ket.h"
//#include "Superposition.h"

class Superposition;

class Sequence {
    private:
        std::vector<Superposition> seq;

    public:
        Sequence() {};
        ~Sequence() {};
        Sequence(Ket& k);
        Sequence(Superposition& sp);
        Sequence add(Ket& k);
        Sequence add(Superposition& sp);
        std::string to_string();
};

#endif
