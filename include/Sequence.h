#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include <string>

#include "BaseRule.h"

#define SEQUENCE 2

class Ket;
class Superposition;

class Sequence : public BaseRule {
    private:
        std::vector<Superposition> seq;

    public:
        Sequence() {};
        ~Sequence() {};
        Sequence(const std::string& s);
        Sequence(Ket& k);
        Sequence(Superposition& sp);
        Sequence(const Sequence& seq);
        Sequence operator+(Sequence& b);
        int type() { return SEQUENCE; };
        const ulong size();

        BaseRule* b_add(BaseRule* brule);
        BaseRule* b_append(BaseRule* brule);

        void add(Ket& k);
        void add(const Superposition& sp);
        void add(const Sequence& seq);

        void multiply(const double d);

        void append(Ket& k);
        void append(const Superposition& sp);
        void append(const Sequence& seq);

        std::string to_string();

        // define an iterator for our sequence class:
        Superposition get(ulong idx) const;
        typedef typename std::vector<Superposition>::iterator iterator;
        typedef typename std::vector<Superposition>::const_iterator const_iterator;

        iterator begin() {return seq.begin();}
        const_iterator begin() const {return seq.begin();}
        const_iterator cbegin() const {return seq.cbegin();}
        iterator end() {return seq.end();}
        const_iterator end() const {return seq.end();}
        const_iterator cend() const {return seq.cend();}

        Ket to_ket();
        Superposition to_sp();
        Sequence to_seq();

        void merge(const Sequence& seq2);
        void merge(const Sequence& seq2, const std::string& s);
};

#endif
