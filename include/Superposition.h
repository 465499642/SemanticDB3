#ifndef SUPERPOSITION_H
#define SUPERPOSITION_H

#define SUPERPOSITION 1

#include <unordered_map>
#include <string>
#include <functional>

#include "KetMap.h"
#include "BaseRule.h"
#include "Ket.h"
#include "SuperpositionIter.h"


class Superposition : public BaseRule {
    private:
        std::unordered_map<ulong, double> sp;
        std::vector<ulong> sort_order;

    public:
        Superposition() {};
        ~Superposition() {};
        Superposition(const ulong idx);
        Superposition(const std::string& s);
        Superposition(const std::string&s, const double v);
        Superposition(const ulong idx, const double v);
        Superposition(Ket k);
        Superposition(const Superposition &sp);

        Superposition operator+(Ket& b);
        const int type() const { return SUPERPOSITION; };
        const ulong size() const;
        // void add(const Ket& a); // bugs out for now

        BaseRule* b_add(BaseRule* brule);
        BaseRule* b_append(BaseRule* brule);

        void add(const ulong idx);
        void add(const ulong idx, const double v);
        void add(const std::string& s);
        void add(Ket& a);
        void add(const Superposition& a);
        void multiply(const double d);
        const std::string to_string() const;

        Ket to_ket() const;
        Superposition to_sp() const;
        Sequence to_seq() const;

        // SuperpositionIter:
        Ket get(ulong idx) const;
        SuperpositionIter begin () const;
        SuperpositionIter end () const;

        void merge(const Superposition& sp2);
        void merge(const Superposition& sp2, const std::string& s);

        Sequence Compile(ContextList& context) const;
        Sequence Compile(ContextList& context, const ulong label_idx) const;
        Sequence Compile(ContextList& context, const std::vector<Sequence>& args) const;

        double find_min_coeff() const;
        double find_max_coeff() const;
        double find_value(const ulong idx) const;
        double find_value(const Ket &k) const;

        Superposition drop() const;
        Superposition drop_below(const double t) const;
        Superposition drop_above(const double t) const;

        Ket do_you_know() const;
        Ket how_many() const;
        Ket measure_currency() const;
        Superposition pick(const ulong n) const;
        Ket pick_elt() const;
        Ket weighted_pick_elt() const;

        Superposition reverse() const;
        Superposition normalize() const;
        Superposition normalize(const double t) const;
        Superposition rescale() const;
        Superposition rescale(const double t) const;
        Superposition shuffle() const;
        Superposition coeff_sort() const;
        Superposition ket_sort() const;
        Superposition select_range(const ulong a, const ulong b) const;
        Superposition top(const ulong a) const;

        Superposition apply_sigmoid(std::function<double(double)> sigmoid) const;
        Superposition apply_sigmoid(std::function<double(double,double)> sigmoid, const double t) const;
        Superposition apply_sigmoid(std::function<double(double,double,double)> sigmoid, const double t1, const double t2) const;
};

#endif
