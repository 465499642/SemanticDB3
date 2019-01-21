#ifndef BASERULE_H
#define BASERULE_H

#include <string>
#include "KetMap.h"

class Ket;
class Superposition;
class Sequence;

class BaseRule {
    private:

    public:
        virtual int type() = 0;
        virtual std::string to_string() = 0;
        virtual ulong size() = 0;
        virtual Ket to_ket() = 0;
        virtual Superposition to_sp() = 0;
        virtual Sequence to_seq() = 0;
};

#endif
