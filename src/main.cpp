#include <iostream>
#include <exception>
#include "KetMap.h"
#include "Ket.h"
#include "Superposition.h"
#include "Functions.h"
#include "Sequence.h"
#include "NewContext.h"
#include "Frame.h"


// for now, use main to test our components:
// later we will write test cases using googleTest
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
    seq.add(r1);
    seq.add(r2);
    seq.add(r3);

    seq.add(sp);
    seq.add(sp2);
    seq.add(sp3);

    std::cout << "seq: " << seq.to_string() << std::endl;

    Ket k1("f"), k2("r"), k3("o",2.2), k4("g", -2);
    Sequence seq2, seq3(k1), seq4(k2);
    seq2.add(seq3);
    seq2.add(seq4);
    seq2.add(k3);
    seq2.add(k4);
    std::cout << "seq2: " << seq2.to_string() << std::endl;

    Sequence seq5;
    seq5 = seq3 + seq4 + seq2;
    std::cout << "seq5: " << seq5.to_string() << std::endl;

    Ket k5("");
    Superposition sp4 = k4 + k3 + k2 + k1 + k4 + k3 + k2 + k1 + k5;
    std::cout << "sp4: " << sp4.to_string() << std::endl;

    Superposition sp5;
    std::cout << "sp5: " << sp5.to_string() << std::endl;

    auto random = ket_map.get_split_idx("random");
    for (auto idx: random) {
        std::cout << idx << " ";
    }
    std::cout << std::endl;

    ket_map.print();

    std::cout << "k5: " << k5.to_string() << " " << k5.size() << std::endl;
    std::cout << "sp4: " << sp4.to_string() << " " << sp4.size() << std::endl;
    std::cout << "seq5: " << seq5.to_string() << " " << seq5.size() << std::endl;

    NewContext context("some testing context");
    context.learn("age", "Fred", "37");
    context.learn("father", "Fred", "Tom");

    auto rule = context.recall("supported-ops", "Fred");
    std::cout << "supported-ops: " << rule.to_string() << std::endl;

    rule = context.recall("age", "Fred");
    std::cout << "rule: " << rule.to_string() << std::endl;

    rule = context.recall("father", "Fred");
    std::cout << "rule: " << rule.to_string() << std::endl;

    context.learn("father", "Tom", "Robert");
    context.learn("age", "Tom", "62");
    context.learn("wife", "Tom", "Mary");
    context.learn("wife", "Fred", "Liz");

    context.print_universe();

    Frame frame;
    ulong op_idx1, op_idx2, op_idx3;
    Superposition tmp1("37");
    op_idx1 = ket_map.get_idx("op: age");
    frame.learn(op_idx1, tmp1);

    Superposition tmp2("Emma");
    op_idx2 = ket_map.get_idx("op: wife");
    frame.learn(op_idx2, tmp2);

    Superposition tmp3("Eric");
    op_idx3 = ket_map.get_idx("op: father");
    frame.learn(op_idx3, tmp3);

    auto op_idx = ket_map.get_idx("op: supported-ops");
    auto sup_ops = frame.recall(op_idx);
    std::cout << "frame supported-ops: " << sup_ops.to_string() << std::endl;
    std::cout << "age: " << frame.recall(op_idx1).to_string() << std::endl;
    std::cout << "wife: " << frame.recall(op_idx2).to_string() << std::endl;
    std::cout << "father: " << frame.recall(op_idx3).to_string() << std::endl;
    frame.print();

//    ket_map.print();

    return 0;
}
