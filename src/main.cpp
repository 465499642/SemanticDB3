#include <iostream>
#include <exception>
#include "KetMap.h"
#include "Ket.h"
#include "Superposition.h"
#include "Functions.h"
#include "Sequence.h"
#include "NewContext.h"
#include "Frame.h"
#include "BaseRule.h"
#include "StoredRule.h"
#include "MemoizingRule.h"
#include "ContextList.h"
#include "NumericOp.h"
#include "SimpleOp.h"
#include "OpSeq.h"
#include "PoweredOp.h"
#include "SingleOpRule.h"
#include "OpRule.h"
#include "SelfKet.h"
#include "FnOp.h"
#include "Sigmoids.h"
#include "FnMap.h"


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
    seq2.append(seq3);
    seq2.append(seq4);
    seq2.append(k3);
    seq2.append(k4);
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
    context.print_universe();


    BaseRule * rule;
    rule = context.recall("supported-ops", "Fred");
    std::cout << "supported-ops: " << rule->to_string() << std::endl;

    rule = context.recall("age", "Fred");
    std::cout << "rule: " << rule->to_string() << std::endl;

    rule = context.recall("father", "Fred");
    std::cout << "rule: " << rule->to_string() << std::endl;

    context.learn("father", "Tom", "Robert");
    context.learn("age", "Tom", "62");
    context.learn("wife", "Tom", "Mary");
    context.learn("wife", "Fred", "Liz");

    context.print_universe();


    Frame frame;
    BaseRule* brule;
    ulong op_idx1, op_idx2, op_idx3;
    Superposition tmp1("37");
    tmp1.add("39");
    brule = &tmp1;
    op_idx1 = ket_map.get_idx("op: age");
    frame.learn(op_idx1, brule);

    Superposition tmp2("Emma");
    op_idx2 = ket_map.get_idx("op: wife");
    brule = &tmp2;
    frame.learn(op_idx2, brule);

    Superposition tmp3("Eric");
    op_idx3 = ket_map.get_idx("op: father");
    brule = &tmp3;
    frame.learn(op_idx3, brule);

    // return 0;

    auto op_idx = ket_map.get_idx("op: supported-ops");

    BaseRule* sup_ops;
    sup_ops = frame.recall(op_idx);
//    return 0;

    std::cout << "frame supported-ops: " << sup_ops->to_string() << std::endl;
    std::cout << "frame supported-ops: " << frame.recall(op_idx)->to_string() << std::endl;
    std::cout << "frame supported-ops: " << frame.recall(op_idx)->size() << std::endl;

    BaseRule* brule0;
    brule0 = frame.recall(op_idx1);
    std::cout << "age: " << brule0->to_string() << " " << brule0->size() << std::endl;
    std::cout << "wife: " << frame.recall(op_idx2)->to_string() << frame.recall(op_idx2)->size() << std::endl;
    std::cout << "father: " << frame.recall(op_idx3)->to_string() << frame.recall(op_idx2)->size() << std::endl;
    frame.print();

//    return 0;


//    ket_map.print();

    std::cout << "ket type: " << k1.type() << std::endl;
    std::cout << "sp type: " << sp2.type() << std::endl;
    std::cout << "seq type: " << seq2.type() << std::endl;

    BaseRule * base_rule;
    base_rule = &k1;
    std::cout << "base_rule->to_string " << base_rule->to_string() << std::endl;

    base_rule = &sp2;
    std::cout << "base_rule->to_string " << base_rule->to_string() << std::endl;

    base_rule = &seq2;
    std::cout << "base_rule->to_string " << base_rule->to_string() << std::endl;

    StoredRule stored_rule("|_self>");
    std::cout << "stored_rule: " << stored_rule.type() << " " << stored_rule.size() << " " << stored_rule.to_string() << std::endl;

    context.learn("foo", "*", &stored_rule);

    MemoizingRule mem_rule("3 |_self>");
    context.learn("bah", "*", &mem_rule);

    context.print_universe();


    Ket k6("a: b: c: d: e");
    ulong k6_idx = k6.label_idx();
    ulong k6_head_idx = ket_map.get_head_idx(k6_idx);
    ulong k6_value_idx = ket_map.get_value_idx(k6_idx);
    Ket k7(k6_head_idx), k8(k6_value_idx);
    std::cout << "k7: " << k7.to_string() << std::endl;
    std::cout << "k8: " << k8.to_string() << std::endl;


    // test extract_* operators:
    Ket k9("animal: dog: Charlie", 7.72);
    std::cout << "k9: " << k9.to_string() << std::endl;
    std::cout << "k9: extract_head: " << extract_head(k9).to_string() << std::endl;
    std::cout << "k9: extract_tail: " << extract_tail(k9).to_string() << std::endl;
    std::cout << "k9: extract_category: " << extract_category(k9).to_string() << std::endl;
    std::cout << "k9: extract_value: " << extract_value(k9).to_string() << std::endl;


    // test label descent:
    context.learn("op0", "*", "op0 applied to *");
    context.learn("op1", "animal: *", "op1 applied to animal");
    context.learn("op2", "animal: mammal: *", "op2 applied to animal: mammal");
    context.learn("op3", "animal: mammal: cat: *", "op3 applied to animal: mammal: cat");
    context.learn("op4", "animal: mammal: cat: Trudy", "op4 applied to animal: mammal: cat: Trudy");
    context.print_universe();

    std::cout << "op4: " << context.recall("op4", "animal: mammal: cat: Trudy")->to_string() << std::endl;
    std::cout << "op3: " << context.recall("op3", "animal: mammal: cat: Trudy")->to_string() << std::endl;
    std::cout << "op2: " << context.recall("op2", "animal: mammal: cat: Trudy")->to_string() << std::endl;
    std::cout << "op1: " << context.recall("op1", "animal: mammal: cat: Trudy")->to_string() << std::endl;
    std::cout << "op0: " << context.recall("op0", "animal: mammal: cat: Trudy")->to_string() << std::endl;
    std::cout << "op: " << context.recall("op", "animal: mammal: cat: Trudy")->to_string() << std::endl;

    ket_map.print();

    // test Compile:
    ContextList context_list("testing compile");
    context_list.learn("foo", "f", "foo: f");
    context_list.learn("foo", "r", "foo: r");
    context_list.learn("foo", "o", "foo: o");
    context_list.learn("foo", "g", "foo: g");
    context_list.learn("bah", "foo: f", "bah: foo: f");
    context_list.learn("bah", "foo: r", "bah: foo: r");
    context_list.learn("bah", "foo: o", "bah: foo: o");
    context_list.learn("bah", "foo: g", "bah: foo: g");
    NumericOp n_op(3.1);
    SimpleOp s_op("foo"), s_op2("bah");
    std::cout << "simple op: " << s_op.Compile(context_list, seq5).to_string() << std::endl;
    std::cout << "numeric op: " << n_op.Compile(context_list, seq5).to_string() << std::endl;

    // test seq.to_ket() and seq.to_sp():
    Ket kx("x",7), ky("y", 3.2), kz("z",-3.14);
    Sequence test_seq;
    test_seq.add(kx);
    test_seq.add(ky);
    test_seq.add(kz);
    test_seq.append(ky);
    test_seq.add(kz);
    test_seq.append(kx);
    std::cout << "test_seq: " << test_seq.to_string() << std::endl;
    std::cout << "test_seq.to_ket(): " << test_seq.to_ket().to_string() << std::endl;
    std::cout << "test_seq.to_sp(): " << test_seq.to_sp().to_string() << std::endl;

    // test OpSeq;
    OpSeq op_seq;
    op_seq.append(&s_op2);
    op_seq.append(&n_op);
    op_seq.append(&s_op);
    std::cout << "op_seq: " << op_seq.to_string() << std::endl;
    std::cout << "compiled op_seq: " << op_seq.Compile(context_list, seq5).to_string() << std::endl;

    // test PoweredOp;
    PoweredOp p_op(&n_op, 2);
    std::cout << "p_op: " << p_op.to_string() << std::endl;
    std::cout << "compiled p_op: " << p_op.Compile(context_list, seq5).to_string() << std::endl;

    // test sp for-each:
    Superposition sp20;
    sp20.add(kx);
    sp20.add(ky);
    sp20.add(kz);
    for (auto k: sp20) {
        std::cout << k.to_string() << std::endl;
    }

    // test SimpleOp Compile:
    Ket ka("a"), kb("b",2.2), kc("c");
    SimpleOp s_op3("foo");
    context_list.learn("foo", "a", "foo: a");
    context_list.learn("foo", "b", "foo: b");
    context_list.learn("foo", "x", "foo: x");
    Sequence seq_abx;
    seq_abx.add(ka);
    seq_abx.add(kb);
    seq_abx.append(kx);
    std::cout << "seq_abx: " << seq_abx.to_string() << std::endl;
    std::cout << "s_op3: " << s_op3.to_string() << std::endl;
    std::cout << "compiled seq_abx: " << s_op3.Compile(context_list, seq_abx).to_string() << std::endl;

    // test Sequence add(seq):
    Sequence seq_abc, seq_xyz, seq_abcxyz;
    seq_abc.add(ka);
    seq_abc.append(kb);
    seq_abc.add(kc);
    seq_xyz.add(kx);
    seq_xyz.add(ky);
    seq_xyz.append(kz);
    seq_abcxyz.add(seq_abc);
    seq_abcxyz.add(seq_xyz);
    std::cout << "seq_abc: " << seq_abc.to_string() << std::endl;
    std::cout << "seq_xyz: " << seq_xyz.to_string() << std::endl;
    std::cout << "seq_abcxyz: " << seq_abcxyz.to_string() << std::endl;

    // test Sequence add(kempty):
    Ket kempty;
    Sequence seq_empty;
    seq_empty.append(kempty);
    seq_empty.append(kempty);
    seq_empty.append(kempty);
    seq_empty.append(ka);
    seq_empty.append(kb);
    std::cout << "seq_empty: " << seq_empty.to_string() << std::endl;

    // test merge:
    Ket kmerge1 = kc;
    kmerge1.merge(kx);
    Ket kmerge2 = kc;
    kmerge2.merge(kx, " ");
    std::cout << "kmerge1: " << kmerge1.to_string() << std::endl;
    std::cout << "kmerge2: " << kmerge2.to_string() << std::endl;

    Superposition spm1, spm2;
    spm1.add(ka);
    spm1.add(kb);
    spm2.add(kx);
    spm2.add(ky);
    Superposition spmerge1 = spm1;
    spmerge1.merge(spm2);
    Superposition spmerge2 = spm1;
    spmerge2.merge(spm2, " ");
    std::cout << "spm1: " << spm1.to_string() << std::endl;
    std::cout << "spm2: " << spm2.to_string() << std::endl;
    std::cout << "spmerge1: " << spmerge1.to_string() << std::endl;
    std::cout << "spmerge2: " << spmerge2.to_string() << std::endl;

    Sequence seqm1, seqm2;
    seqm1.add(ka);
    seqm1.add(kb);
    seqm1.append(kx);
    seqm1.add(ky);
    Sequence seqmerge1 = seqm1;
    seqmerge1.merge(seqm1);
    Sequence seqmerge2 = seqm1;
    seqmerge2.merge(seqm1, " ");
    std::cout << "seqm1: " << seqm1.to_string() << std::endl;
    std::cout << "seqmerge1: " << seqmerge1.to_string() << std::endl;
    std::cout << "seqmerge2: " << seqmerge2.to_string() << std::endl;

    // test SingleOpRule:
    SimpleOp s_op_1("op1"), s_op_2("op2");
    NumericOp n_3(3);
    PoweredOp p_op_1(&n_3, 4);
    OpSeq op_seq_1;
    op_seq_1.append(&s_op_2);
    op_seq_1.append(&p_op_1);
    op_seq_1.append(&s_op_1);
    SingleOpRule op_rule(&op_seq_1, &kx);
    context_list.learn("op1", "x", "op1: x");
    context_list.learn("op2", "op1: x", "op2: op1: x");
    std::cout << "op_seq_1: " << op_seq_1.to_string() << std::endl;
    std::cout << "op_rule: " << op_rule.to_string() << std::endl;
    std::cout << "compiled op_rule: " << op_rule.Compile(context_list).to_string() << std::endl;
    std::cout << "testing existance of op_rule: " << op_rule.to_string() << std::endl;


    // test OpRule:
    SingleOpRule op_rule2(&op_seq_1, &ky);
    OpRule full_op_rule;
    full_op_rule.push(op_rule);
    full_op_rule.push(op_rule2);
    context_list.learn("op1", "y", "op1: y");
    context_list.learn("op2", "op1: y", "op2: op1: y");
    std::cout << "op_rule: " << op_rule.to_string() << std::endl;
    std::cout << "op_rule2: " << op_rule2.to_string() << std::endl;
    std::cout << "full_op_rule: " << full_op_rule.to_string() << std::endl;
    std::cout << "compiled full_op_rule: " << full_op_rule.Compile(context_list).to_string() << std::endl;

//    OpSeq op_seq_2(SMINUS);
    OpSeq op_seq_2(SSEQ);
//    OpSeq op_seq_2(SMERGE2);
    op_seq_2.append(&s_op_2);
    op_seq_2.append(&p_op_1);
    op_seq_2.append(&s_op_1);
    SingleOpRule op_rule3(&op_seq_2, &ky);
    OpRule full_op_rule2;
    full_op_rule2.push(op_rule);
    full_op_rule2.push(op_rule3);
    std::cout << "op_rule: " << op_rule.to_string() << std::endl;
    std::cout << "op_rule3: " << op_rule3.to_string() << std::endl;
    std::cout << "full_op_rule2: " << full_op_rule2.to_string() << std::endl;
    std::cout << "compiled full_op_rule2: " << full_op_rule2.Compile(context_list).to_string() << std::endl;

    // test SelfKet:
    SelfKet s_ket;
    SelfKet s_ket2(5, 3.142);
    std::cout << "s_ket: " << s_ket.to_string() << std::endl;
    std::cout << "s_ket2: " << s_ket2.to_string() << std::endl;
    std::cout << "compiled s_ket: " << s_ket.Compile(context_list, 2).to_string() << std::endl;

    // test context.fn_learn() and context.fn_recall():
    ulong fn_idx = ket_map.get_idx("foo");
    SelfKet s_ket3(3, 7.25);
    context_list.set("testing fn_learn");
    context_list.fn_learn(fn_idx, 3, &s_ket3);
    context_list.print_universe();

    // test FnOp:
    FnOp fn_op(fn_idx);
    Ket sam("Sam", 3);
    fn_op.push(&full_op_rule);
    fn_op.push(&full_op_rule2);
    std::cout << "fn_op: " << fn_op.to_string() << std::endl;

    // test arithmetic:
    Sequence arith_0, arith_1("3"), arith_2("+"), arith_3("5");
    Sequence arith_result = arithmetic(context_list, arith_0, arith_1, arith_2, arith_3);
    std::cout << "arith_result: " << arith_result.to_string() << std::endl;

    Sequence arith_4("3.14159265"), arith_5("+"), arith_6("5.2");
    Sequence arith_result2 = arithmetic(context_list, arith_0, arith_4, arith_5, arith_6);
    std::cout << "arith_result2: " << arith_result2.to_string() << std::endl;

    // test simm:
    Superposition sp_1, sp_2, sp_3;
    sp_1.add("a");
    sp_2.add("a");
    sp_2.add("b");
    sp_2.add("c");
    std::cout << "simm(sp2, sp2): " << simm(sp_2, sp_2) << std::endl;
    std::cout << "simm(sp1, sp2): " << simm(sp_1, sp_2) << std::endl;

    std::cout << "scaled_simm(sp2, sp2): " << scaled_simm(sp_2, sp_2) << std::endl;
    std::cout << "scaled_simm(sp1, sp2): " << scaled_simm(sp_1, sp_2) << std::endl;

    // test push_float():
    Ket pk0("",7), pk1("a: b", 3.2), pk2(" ",5), pk3("x: y");
    std::cout << "push_float 7|> " << push_float(pk0).to_string() << std::endl;
    std::cout << "push_float 3.2|a: b> " << push_float(pk1).to_string() << std::endl;
    std::cout << "push_float 5| > " << push_float(pk2).to_string() << std::endl;
    std::cout << "push_float |x: y> " << push_float(pk3).to_string() << std::endl;

    // test pop_float():
    Ket pk4("3.14159"), pk5("a: b: c: 5.1", 3), pk6("a: b: c");
    std::cout << "pop_float |3.14159> " << pop_float(pk4).to_string() << std::endl;
    std::cout << "pop_float 3|a: b: c: 5.1> " << pop_float(pk5).to_string() << std::endl;
    std::cout << "pop_float |a: b: c> " << pop_float(pk6).to_string() << std::endl;

    // test Superposition::find_min_coeff() and find_max_coeff():
    Superposition spm;
    Ket sk1("a"), sk2("b", 3), sk3("c",5);
    spm.add(sk1);
    spm.add(sk2);
    spm.add(sk3);
    spm.add(sk2);
    std::cout << "|a> + 3|b> + 5|c> + 3|b>: " << spm.to_string() << std::endl;
    std::cout << "min_coeff: " << spm.find_min_coeff() << std::endl;
    std::cout << "max_coeff: " << spm.find_max_coeff() << std::endl;

    // test Superposition::find_value(ket):
    std::cout << "a: " << spm.find_value(sk1) << std::endl;
    std::cout << "b: " << spm.find_value(sk2) << std::endl;
    std::cout << "c: " << spm.find_value(sk3) << std::endl;

    // test normed_frequency_class:
    // double normed_frequency_class(const Ket &k, const Superposition &sp)

    Ket nfc_k1("a"), nfc_k2("b"), nfc_k3("c"), nfc_k4("d");
    Superposition nfc_sp1;
    nfc_sp1 = nfc_k1 + nfc_k2 + nfc_k3;
    Superposition nfc_sp2 = nfc_sp1;
    nfc_sp2.multiply(7.2);

    std::cout << "nfc_sp1: " << nfc_sp1.to_string() << std::endl;
    std::cout << "nfc_sp2: " << nfc_sp2.to_string() << std::endl;

    std::cout << "nfc b: " << normed_frequency_class(nfc_k2, nfc_sp1) << std::endl;
    std::cout << "nfc c: " << normed_frequency_class(nfc_k3, nfc_sp2) << std::endl;
    std::cout << "nfc d: " << normed_frequency_class(nfc_k4, nfc_sp1) << std::endl;

    // test Superposition::drop(), drop_below(), drop_above():
    Ket dk1("a"), dk2("b",-2.2), dk3("c",0), dk4("d",3);
    Superposition dsp1 = dk1 + dk2 + dk3 + dk4;
    std::cout << "dsp1: " << dsp1.to_string() << std::endl;
    std::cout << "dsp1.drop(): " << dsp1.drop().to_string() << std::endl;
    std::cout << "dsp1.drop_below(2): " << dsp1.drop_below(2).to_string() << std::endl;
    std::cout << "dsp1.drop_above(0): " << dsp1.drop_above(0).to_string() << std::endl;

    // test Superposition::how_many():
    Superposition hsp_empty;
    std::cout << "dsp1.how_many(): " << dsp1.how_many().to_string() << std::endl;
    std::cout << "hsp_empty.how_many(): " << hsp_empty.how_many().to_string() << std::endl;

    // test Superposition::do_you_know():
    std::cout << "dsp1.do_you_know(): " << dsp1.do_you_know().to_string() << std::endl;
    std::cout << "hsp_empty.do_you_know(): " << hsp_empty.do_you_know().to_string() << std::endl;

    // test Superposition::pick_elt():
    for (int i = 0; i < 10; i++) {
        std::cout << "dsp1.pick_elt(): " << dsp1.pick_elt().to_string() << std::endl;
    }

    // test Superposition::weighted_pick_elt():
    for (int i = 0; i < 10; i++) {
        std::cout << "dsp1.weighted_pick_elt(): " << dsp1.weighted_pick_elt().to_string() << std::endl;
    }

    // test Superposition::reverse():
    std::cout << "dsp1.reverse(): " << dsp1.reverse().to_string() << std::endl;

   // test Superposition::normalize():
    Ket nk1("a"), nk2("b"), nk3("c"), nk4("d"), nk5("e");
    Superposition nsp1 = nk1 + nk2 + nk3 + nk4 + nk5;
    Superposition nsp2 = nk1 + nk1 + nk2;
    std::cout << "dsp1.normalize(): " << dsp1.normalize().to_string() << std::endl;
    std::cout << "nsp1.normalize(): " << nsp1.normalize().to_string() << std::endl;
    std::cout << "nsp2.normalize(): " << nsp2.normalize().to_string() << std::endl;

    std::cout << "dsp1.normalize(100): " << dsp1.normalize(100).to_string() << std::endl;
    std::cout << "nsp1.normalize(100): " << nsp1.normalize(100).to_string() << std::endl;
    std::cout << "nsp2.normalize(100): " << nsp2.normalize(100).to_string() << std::endl;

   // test Superposition::rescale():
    std::cout << "dsp1.rescale(): " << dsp1.rescale().to_string() << std::endl;
    std::cout << "nsp1.rescale(): " << nsp1.rescale().to_string() << std::endl;
    std::cout << "nsp2.rescale(): " << nsp2.rescale().to_string() << std::endl;

    std::cout << "dsp1.rescale(100): " << dsp1.rescale(100).to_string() << std::endl;
    std::cout << "nsp1.rescale(100): " << nsp1.rescale(100).to_string() << std::endl;
    std::cout << "nsp2.rescale(100): " << nsp2.rescale(100).to_string() << std::endl;

    // test Superposition::shuffle():
    std::cout << "nsp1.shuffle(): " << nsp1.shuffle().to_string() << std::endl;

    // test Superposition::coeff_sort():
    std::cout << "dsp1.coeff_sort(): " << dsp1.coeff_sort().to_string() << std::endl;

    // test Superposition::ket_sort():
    std::cout << "dsp1.coeff_sort().ket_sort(): " << dsp1.coeff_sort().ket_sort().to_string() << std::endl;

    // test Superposition::measure_currency():
    std::cout << "dsp1.measure_currency(): " << dsp1.measure_currency().to_string() << std::endl;
    std::cout << "nsp1.measure_currency(): " << nsp1.measure_currency().to_string() << std::endl;

    // test split():
    Ket split_k("a b c d e f", 3);
    std::cout << "split 3|a b c d e f>: " << split(split_k).to_string() << std::endl;

    // test Superposition::select_range(a, b):
    std::cout << "select[2,4] split 3|a b c d e f>: " << split(split_k).select_range(2,4).to_string() << std::endl;
    std::cout << "select[2,10] split 3|a b c d e f>: " << split(split_k).select_range(2,10).to_string() << std::endl;

    // test rank():
    std::cout << "rank split |a b c d e f>: " << rank(split(split_k)).to_string() << std::endl;

    // test top(k):
    std::cout << "top[3] rank split |a b c d e f>: " << rank(split(split_k)).top(3).to_string() << std::endl;

    // test Superposition::pick(n):
    std::cout << "pick[3] rank split |a b c d e f>: " << rank(split(split_k)).pick(3).to_string() << std::endl;

    // test Superposition::apply_sigmoid(sigmoid):
    std::cout << "dsp1: " << dsp1.to_string() << std::endl;
    std::cout << "clean (|a> - 2.2|b> + 0|c> + 3|d>): " << dsp1.apply_sigmoid(clean).to_string() << std::endl;
    std::cout << "threshold-filter[3] rank split |a b c d e f>: " << rank(split(split_k)).apply_sigmoid(threshold_filter, 3).to_string() << std::endl;
    std::cout << "sigmoid_in_range[3,5] rank split |a b c d e f>: " << rank(split(split_k)).apply_sigmoid(sigmoid_in_range, 3, 5).to_string() << std::endl;

    // test range(|1>, |15>):
    // Sequence range(Sequence &input_seq, Sequence &start, Sequence &stop)
    Sequence input_seq, start("1"), stop("15");
    std::cout << "range(|1>, |15>): " << range(input_seq, start, stop).to_string() << std::endl;

    Sequence start2("number: 1"), stop2("price: 5"), stop3("number: 5");
    std::cout << "range(|number: 1>, |price: 5>): " << range(input_seq, start2, stop2).to_string() << std::endl;
    std::cout << "range(|number: 1>, |number: 5>): " << range(input_seq, start2, stop3).to_string() << std::endl;

    Sequence step("3");
    std::cout << "range(|1>, |15>, |3>): " << range(input_seq, start, stop, step).to_string() << std::endl;

    Sequence step2("0");
    std::cout << "range(|1>, |15>, |0>): " << range(input_seq, start, stop, step2).to_string() << std::endl;

    Sequence step3("1", -1);
    std::cout << "range(|15>, |1>, -|1>): " << range(input_seq, stop, start, step3).to_string() << std::endl;

    Sequence stop4("5"), step4("0.5");
    std::cout << "range(|1>, |5>, |0.5>): " << range(input_seq, start, stop4, step4).to_string() << std::endl;

    // test Sequence::sreverse():
    Sequence srev;
    Ket krev1("a"), krev2("b", 3.14), krev3("c", -2), krev4("d");
    srev.append(krev1);
    srev.append(krev2);
    srev.append(krev3);
    srev.append(krev4);
    std::cout << "srev: " << srev.to_string() << std::endl;
    std::cout << "sreverse srev: " << srev.sreverse().to_string() << std::endl;

    // test sp2seq and seq2sp:
    std::cout << "seq2sp srev: " << seq2sp(srev).to_string() << std::endl;
    std::cout << "sp2seq range(|1>, |5>): " << sp2seq(range(input_seq, start, stop4).to_sp()).to_string() << std::endl;

    // test bar-chart[50]:
    Ket kbc("a b c d e f");
    std::cout << "bar-chart[12] rank split |a b c d e f>:\n" << bar_chart(rank(split(kbc)), 12).to_string() << std::endl;
    std::cout << "bar-chart[12] shuffle rank split |a b c d e f>:\n" << bar_chart(rank(split(kbc)).shuffle(), 12).to_string() << std::endl;

    Ket kbc2("Fred Sam Robert");
    std::cout << "bar-chart[6] rank split |Fred Sam Robert>:\n" << bar_chart(rank(split(kbc2)), 6).to_string() << std::endl;

    // test Sequence::apply_sigmoid():
    std::cout << "srev: " << srev.to_string() << std::endl;
    std::cout << "clean (|a> . 3.140000|b> . - 2.000000|c> . |d>): " << srev.apply_sigmoid(clean).to_string() << std::endl;
    std::cout << "threshold_filter[2] (|a> . 3.140000|b> . - 2.000000|c> . |d>): " << srev.apply_sigmoid(threshold_filter, 2).to_string() << std::endl;
    std::cout << "sigmoid_in_range[0,2] (|a> . 3.140000|b> . - 2.000000|c> . |d>): " << srev.apply_sigmoid(sigmoid_in_range, 0, 2).to_string() << std::endl;

    // test FnMap.whitelist_3:
    ulong arithmetic_idx = ket_map.get_idx("arithmetic");
    fn_map.context_whitelist_3.emplace(arithmetic_idx, &arithmetic);
    // fn_map.context_whitelist_3[arithmetic_idx] = &arithmetic;
    auto our_fn = fn_map.context_whitelist_3[arithmetic_idx];
    Sequence plus("+");
    std::cout << "our_fn(context, |>, |1>, |+>, |5>): " << our_fn(context_list, input_seq, start, plus, stop4).to_string() << std::endl;

    ulong range_idx = ket_map.get_idx("range");
    fn_map.whitelist_2.emplace(range_idx, &range2);
    // fn_map.whitelist_2[range_idx] = &range2;
    fn_map.whitelist_3[range_idx] = &range3;
    auto our_fn2 = fn_map.whitelist_2[range_idx];
    std::cout << "our_fn2(|>, |1>, |5>): " << our_fn2(input_seq, start, stop4).to_string() << std::endl;

    auto our_fn3 = fn_map.whitelist_3[range_idx];
    std::cout << "our_fn3(|>, |1>, |5>, |0.5>): " << our_fn3(input_seq, start, stop4, step4).to_string() << std::endl;

    fn_map.print();


    // test empty KetMap:
    KetMap ket_map2;
    ket_map2.print();
    ket_map2.get_idx("range");
    ket_map2.print();

    return 0;
}
