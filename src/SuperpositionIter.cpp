#include "SuperpositionIter.h"
#include "Superposition.h"

Ket SuperpositionIter::operator* () const {
    return _p_sp->get(_pos);
}

Ket SuperpositionIter::operator[](difference_type rhs) const {
    return _p_sp->get(rhs);
}

