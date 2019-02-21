#include "SuperpositionIter.h"
#include "Superposition.h"
#include "Ket.h"

SuperpositionIter::SuperpositionIter(const Superposition* p_sp, ulong pos) {
    _pos = pos;
   _p_sp = p_sp;
}

SuperpositionIter& SuperpositionIter::operator+=(difference_type rhs) {
    _pos += rhs;
    return *this;
}

SuperpositionIter& SuperpositionIter::operator-=(difference_type rhs) {
    _pos -= rhs;
    return *this;
}

Ket SuperpositionIter::operator* () const {
    return _p_sp->get(_pos);
}

Ket SuperpositionIter::operator[](difference_type rhs) const {
    return _p_sp->get(rhs);  // is this correct?
}

SuperpositionIter& SuperpositionIter::operator++() {
    ++_pos;
    return *this;
}

SuperpositionIter& SuperpositionIter::operator--() {
    --_pos;
    return *this;
}

SuperpositionIter SuperpositionIter::operator++(int) {
    SuperpositionIter tmp(_p_sp, _pos);
    ++_pos;
    return tmp;
}

SuperpositionIter SuperpositionIter::operator--(int) {
    SuperpositionIter tmp(_p_sp, _pos);
    --_pos;
    return tmp;
}

SuperpositionIter::difference_type SuperpositionIter::operator-(const SuperpositionIter& rhs) const {
    return _pos - rhs._pos;
}

SuperpositionIter SuperpositionIter::operator+(difference_type rhs) const {
    return SuperpositionIter(_p_sp, _pos + rhs);
}

SuperpositionIter SuperpositionIter::operator-(difference_type rhs) const {
    return SuperpositionIter(_p_sp, _pos - rhs);
}

SuperpositionIter operator+(SuperpositionIter::difference_type lhs, const SuperpositionIter& rhs) {
    return SuperpositionIter(_p_sp, lhs + rhs._pos);
}

SuperpositionIter SuperpositionIter::operator-(difference_type lhs, const SuperpositionIter& rhs) {
    return SuperpositionIter(_p_sp, lhs - rhs._pos);
}

bool SuperpositionIter::operator== (const SuperpositionIter& rhs) const {
    return _pos == rhs._pos;
}

bool SuperpositionIter::operator!= (const SuperpositionIter& rhs) const {
    return _pos != rhs._pos;
}

bool SuperpositionIter::operator> (const SuperpositionIter& rhs) const {
    return _pos > rhs._pos;
}

bool SuperpositionIter::operator< (const SuperpositionIter& rhs) const {
    return _pos < rhs._pos;
}

bool SuperpositionIter::operator>= (const SuperpositionIter& rhs) const {
    return _pos >= rhs._pos;
}

bool SuperpositionIter::operator<= (const SuperpositionIter& rhs) const {
    return _pos <= rhs._pos;
}



/*
bool SuperpositionIter::operator!= (const SuperpositionIter& other) const {
    return _pos != other._pos;
}


const SuperpositionIter& SuperpositionIter::operator++ () {
    ++_pos;
    return *this;
}

SuperpositionIter& SuperpositionIter::operator- (const SuperpositionIter& other) {
    _pos -= other._pos;
    return *this;
}
*/
