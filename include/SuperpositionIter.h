#ifndef SUPERPOSITIONITER_H
#define SUPERPOSITIONITER_H

#include "KetMap.h"

class Superposition;
class Ket;

class SuperpositionIter{
    private:
        ulong _idx;
        const Superposition *_p_sp;

    public:
        SuperpositionIter(const Superposition* p_sp, ulong idx);
        bool operator!= (const SuperpositionIter& other) const;
        Ket operator* () const;
        const SuperpositionIter& operator++ ();

        SuperpositionIter& operator- (const SuperpositionIter& other);
};

#endif
