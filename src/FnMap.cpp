#include <iostream>
#include "KetMap.h"
#include "FnMap.h"
#include "Functions.h"
#include "Sigmoids.h"
#include "Sequence.h"

KetMap ket_map;
FnMap fn_map;

FnMap::FnMap() {
    ulong idx;

    idx = ket_map.get_idx("shuffle");
    fn_map.built_in.emplace(idx, &Sequence::shuffle);

    idx = ket_map.get_idx("sreverse");
    fn_map.built_in.emplace(idx, &Sequence::sreverse);

    idx = ket_map.get_idx("sdrop");
    fn_map.built_in.emplace(idx, &Sequence::sdrop);


    idx = ket_map.get_idx("clean");
    fn_map.sigmoids.emplace(idx, &clean);

    idx = ket_map.get_idx("split");
    fn_map.ket_fn.emplace(idx, &seq_split);

    idx = ket_map.get_idx("print");
    fn_map.ket_fn.emplace(idx, &print_ket);

    idx = ket_map.get_idx("sp2seq");
    fn_map.sp_fn.emplace(idx, &sp2seq);

    idx = ket_map.get_idx("rank");
    fn_map.sp_fn.emplace(idx, &seq_rank);

    // learn some functions:
    idx = ket_map.get_idx("range");
    fn_map.whitelist_2.emplace(idx, &range2);
    fn_map.whitelist_3.emplace(idx, &range3);

    idx = ket_map.get_idx("intersection");
    fn_map.whitelist_2.emplace(idx, &seq_intersection);

    idx = ket_map.get_idx("arithmetic");
    fn_map.context_whitelist_3.emplace(idx, &arithmetic); // later remove context dependence of arithmetic.

    idx = ket_map.get_idx("simm");
    fn_map.whitelist_2.emplace(idx, &ket_simm);

    idx = ket_map.get_idx("scaled-simm");
    fn_map.whitelist_2.emplace(idx, &ket_scaled_simm);

}


void FnMap::print() const {
    std::cout << "built_in:" << std::endl;
    for (auto it : built_in) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }

    std::cout << "sigmoids:" << std::endl;
    for (auto it : sigmoids) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }

    std::cout << "ket_fn:" << std::endl;
    for (auto it : ket_fn) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }

    std::cout << "sp_fn:" << std::endl;
    for (auto it : sp_fn) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }


    std::cout << "whitelist_1:" << std::endl;
    for (auto it : whitelist_1) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "whitelist_2:" << std::endl;
    for (auto it : whitelist_2) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "whitelist_3:" << std::endl;
    for (auto it : whitelist_3) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "whitelist_4:" << std::endl;
    for (auto it : whitelist_4) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }

    std::cout << "context_whitelist_1:" << std::endl;
    for (auto it : context_whitelist_1) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "context_whitelist_2:" << std::endl;
    for (auto it : context_whitelist_2) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "context_whitelist_3:" << std::endl;
    for (auto it : context_whitelist_3) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
    std::cout << "context_whitelist_4:" << std::endl;
    for (auto it : context_whitelist_4) {
        std::cout << "    " << ket_map.get_str(it.first) << std::endl;
    }
}

