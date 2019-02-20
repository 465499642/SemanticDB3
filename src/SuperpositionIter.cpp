#include "SuperpositionIter.h"
#include "Superposition.h"
#include "Ket.h"

SuperpositionIter::SuperpositionIter(const Superposition* p_sp, ulong idx) {
    _idx = idx;
   _p_sp = p_sp;
}

bool SuperpositionIter::operator!= (const SuperpositionIter& other) const {
    return _idx != other._idx;
}

Ket SuperpositionIter::operator* () const {
    return _p_sp->get(_idx);
}

const SuperpositionIter& SuperpositionIter::operator++ () {
    ++_idx;
    return *this;
}

SuperpositionIter& SuperpositionIter::operator- (const SuperpositionIter& other) {
    _idx -= other._idx;
    return *this;
}
