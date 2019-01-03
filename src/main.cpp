#include <iostream>
#include <exception>
#include "KetMap.h"
#include "Ket.h"
#include "Superposition.h"
#include "Functions.h"
#include "Sequence.h"

int main() {
    ulong i,j,k,l;

    // KetMap ket_map;
    i = ket_map.get_idx("first");
    j = ket_map.get_idx("second");
    k = ket_map.get_idx("third");
    l = ket_map.get_idx("second");

    std::cout << "i: " << i << std::endl;
    std::cout << "j: " << j << std::endl;
    std::cout << "k: " << k << std::endl;
    std::cout << "l: " << l << std::endl;

    std::cout << "str[i]: " << ket_map.get_str(i) << std::endl;
    std::cout << "str[j]: " << ket_map.get_str(j) << std::endl;
    std::cout << "str[k]: " << ket_map.get_str(k) << std::endl;
    std::cout << "str[l]: " << ket_map.get_str(l) << std::endl;


    auto svec = split("first: second: third: fourth", ": ");
    for (const auto s: svec) {
        std::cout << s << " ";
    }
    std::cout << std::endl;

    auto v = ket_map.get_split_idx("first: second: third");
    for (const auto i: v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;


    auto v1 = ket_map.get_idx("one: two: three: four: five");
    auto v2 = ket_map.get_split_idx("six: seven: eight: nine");

    auto r1 = Ket();
    auto r2 = Ket("Fred");
    auto r3 = Ket("person: Sam", 3.7);

    ket_map.print();

    std::cout << "r1: " << r1.to_string() << std::endl;
    std::cout << "r2: " << r2.to_string() << std::endl;
    std::cout << "r3: " << r3.to_string() << std::endl;

    std::cout << "r1.label_idx(): " << r1.label_idx() << std::endl;
    std::cout << "r2.label_idx(): " << r2.label_idx() << std::endl;
    std::cout << "r3.label_idx(): " << r3.label_idx() << std::endl;


    auto s1 = r1.label_split_idx();
    auto s2 = r2.label_split_idx();
    auto s3 = r3.label_split_idx();

    std::cout << "r1.label_split_idx(): " << std::endl;
    for (const auto i: s1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "r2.label_split_idx(): " << std::endl;
    for (const auto i: s2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "r3.label_split_idx(): " << std::endl;
    for (const auto i: s3) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    Superposition sp("dog: charlie", 3.14);
    std::cout << "sp: " << sp.to_string() << std::endl;

    sp.add(r2);
    sp.add(r3);
    sp.add(r2);
    std::cout << "sp: " << sp.to_string() << std::endl;

    Superposition sp2("constant: pi", 3.141592);
    sp2.add(sp);
    sp2.add(sp);
    std::cout << "sp2: " << sp2.to_string() << std::endl;

    Ket r4("four", 4), r5("five", 5.0), r6("six", 6.666);
    Superposition sp3;
    sp3 = r4 + r5 + r6;
    // sp3 = sp3 + r4 + r5 + r6;
    std::cout << "sp3: " << sp3.to_string() << std::endl;


    ket_map.print();

    auto svec1 = split("house: cat: dog: mouse", ": ");
    auto str = join(svec1, "; ");
    std::cout << "str: " << str << std::endl;

    Sequence seq;
    // Ket k1("fish soup", 37.2);
    // seq.add(k1);
    seq.add(sp);
    seq.add(sp2);

//    seq.add(r2);
//    seq.add(r3);
/*
    seq.add(sp);
    seq.add(sp2);
    seq.add(sp3);
*/
//    std::cout << "seq: " << seq.to_string() << std::endl;

    return 0;
}
