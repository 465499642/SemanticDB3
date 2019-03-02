#include <iostream>
#include <string>
#include <vector>
#include "KetMap.h"
#include "Sequence.h"
#include "FnOp.h"
#include "FnMap.h"


Sequence FnOp::Compile(ContextList& context, const Sequence& seq) const {
    std::vector<Sequence> args;
    args.push_back(seq);
    for (const auto op_rule: op_rules) {
        Sequence tmp = op_rule->Compile(context);
        args.push_back(tmp);
        std::cout << "arg: " << tmp.to_string() << std::endl;
    }
    switch (op_rules.size()) {  // is it possible to tidy up this section?
        case 1: { if (fn_map.whitelist_1.find(op_idx) != fn_map.whitelist_1.end()) {
                      auto our_fn = fn_map.whitelist_1[op_idx];
                      return our_fn(args[0], args[1]);
                  } else if (fn_map.context_whitelist_1.find(op_idx) != fn_map.context_whitelist_1.end()) {
                      auto our_fn = fn_map.context_whitelist_1[op_idx];
                      return our_fn(context, args[0], args[1]);
                  }
                  break;
                }
        case 2: { if (fn_map.whitelist_2.find(op_idx) != fn_map.whitelist_2.end()) {
                      auto our_fn = fn_map.whitelist_2[op_idx];
                      return our_fn(args[0], args[1], args[2]);
                  } else if (fn_map.context_whitelist_2.find(op_idx) != fn_map.context_whitelist_2.end()) {
                      auto our_fn = fn_map.context_whitelist_2[op_idx];
                      return our_fn(context, args[0], args[1], args[2]);
                  }
                  break;
                }
        case 3: { if (fn_map.whitelist_3.find(op_idx) != fn_map.whitelist_3.end()) {
                      auto our_fn = fn_map.whitelist_3[op_idx];
                      return our_fn(args[0], args[1], args[2], args[3]);
                  } else if (fn_map.context_whitelist_3.find(op_idx) != fn_map.context_whitelist_3.end()) {
                      auto our_fn = fn_map.context_whitelist_3[op_idx];
                      return our_fn(context, args[0], args[1], args[2], args[3]);
                  }
                  break;
                }
        case 4: { if (fn_map.whitelist_4.find(op_idx) != fn_map.whitelist_4.end()) {
                      auto our_fn = fn_map.whitelist_4[op_idx];
                      return our_fn(args[0], args[1], args[2], args[3], args[4]);
                  } else if (fn_map.context_whitelist_4.find(op_idx) != fn_map.context_whitelist_4.end()) {
                      auto our_fn = fn_map.context_whitelist_4[op_idx];
                      return our_fn(context, args[0], args[1], args[2], args[3], args[4]);
                  }
                  break;
                }
    }
    BaseRule *brule = context.fn_recall(op_idx, op_rules.size());
    std::cout << "brule: " << brule->to_string() << std::endl;
    return brule->Compile(context, args);
}

// find a way to remove this duplication!!
Sequence FnOp::Compile(ContextList& context, const Sequence& seq, const ulong label_idx) const {
    std::vector<Sequence> args;
    args.push_back(seq);
    for (const auto op_rule: op_rules) {
        Sequence tmp = op_rule->Compile(context, label_idx);
        args.push_back(tmp);
        std::cout << "arg: " << tmp.to_string() << std::endl;
    }
    switch (op_rules.size()) {  // is it possible to tidy up this section?
        case 1: { if (fn_map.whitelist_1.find(op_idx) != fn_map.whitelist_1.end()) {
                      auto our_fn = fn_map.whitelist_1[op_idx];
                      return our_fn(args[0], args[1]);
                  } else if (fn_map.context_whitelist_1.find(op_idx) != fn_map.context_whitelist_1.end()) {
                      auto our_fn = fn_map.context_whitelist_1[op_idx];
                      return our_fn(context, args[0], args[1]);
                  }
                  break;
                }
        case 2: { if (fn_map.whitelist_2.find(op_idx) != fn_map.whitelist_2.end()) {
                      auto our_fn = fn_map.whitelist_2[op_idx];
                      return our_fn(args[0], args[1], args[2]);
                  } else if (fn_map.context_whitelist_2.find(op_idx) != fn_map.context_whitelist_2.end()) {
                      auto our_fn = fn_map.context_whitelist_2[op_idx];
                      return our_fn(context, args[0], args[1], args[2]);
                  }
                  break;
                }
        case 3: { if (fn_map.whitelist_3.find(op_idx) != fn_map.whitelist_3.end()) {
                      auto our_fn = fn_map.whitelist_3[op_idx];
                      return our_fn(args[0], args[1], args[2], args[3]);
                  } else if (fn_map.context_whitelist_3.find(op_idx) != fn_map.context_whitelist_3.end()) {
                      auto our_fn = fn_map.context_whitelist_3[op_idx];
                      return our_fn(context, args[0], args[1], args[2], args[3]);
                  }
                  break;
                }
        case 4: { if (fn_map.whitelist_4.find(op_idx) != fn_map.whitelist_4.end()) {
                      auto our_fn = fn_map.whitelist_4[op_idx];
                      return our_fn(args[0], args[1], args[2], args[3], args[4]);
                  } else if (fn_map.context_whitelist_4.find(op_idx) != fn_map.context_whitelist_4.end()) {
                      auto our_fn = fn_map.context_whitelist_4[op_idx];
                      return our_fn(context, args[0], args[1], args[2], args[3], args[4]);
                  }
                  break;
                }
    }
    BaseRule *brule = context.fn_recall(op_idx, op_rules.size());
    std::cout << "brule: " << brule->to_string() << std::endl;
    return brule->Compile(context, args);
}

// find a way to remove this duplication!!
Sequence FnOp::Compile(ContextList& context, const Sequence& seq, const std::vector<Sequence>& input_args) const {
    std::vector<Sequence> args;
    args.push_back(seq);
    for (const auto op_rule: op_rules) {
        Sequence tmp = op_rule->Compile(context, input_args);
        args.push_back(tmp);
        std::cout << "arg: " << tmp.to_string() << std::endl;
    }
    switch (op_rules.size()) {  // is it possible to tidy up this section?
        case 1: { if (fn_map.whitelist_1.find(op_idx) != fn_map.whitelist_1.end()) {
                      auto our_fn = fn_map.whitelist_1[op_idx];
                      return our_fn(args[0], args[1]);
                  } else if (fn_map.context_whitelist_1.find(op_idx) != fn_map.context_whitelist_1.end()) {
                      auto our_fn = fn_map.context_whitelist_1[op_idx];
                      return our_fn(context, args[0], args[1]);
                  }
                  break;
                }
        case 2: { if (fn_map.whitelist_2.find(op_idx) != fn_map.whitelist_2.end()) {
                      auto our_fn = fn_map.whitelist_2[op_idx];
                      return our_fn(args[0], args[1], args[2]);
                  } else if (fn_map.context_whitelist_2.find(op_idx) != fn_map.context_whitelist_2.end()) {
                      auto our_fn = fn_map.context_whitelist_2[op_idx];
                      return our_fn(context, args[0], args[1], args[2]);
                  }
                  break;
                }
        case 3: { if (fn_map.whitelist_3.find(op_idx) != fn_map.whitelist_3.end()) {
                      auto our_fn = fn_map.whitelist_3[op_idx];
                      return our_fn(args[0], args[1], args[2], args[3]);
                  } else if (fn_map.context_whitelist_3.find(op_idx) != fn_map.context_whitelist_3.end()) {
                      auto our_fn = fn_map.context_whitelist_3[op_idx];
                      return our_fn(context, args[0], args[1], args[2], args[3]);
                  }
                  break;
                }
        case 4: { if (fn_map.whitelist_4.find(op_idx) != fn_map.whitelist_4.end()) {
                      auto our_fn = fn_map.whitelist_4[op_idx];
                      return our_fn(args[0], args[1], args[2], args[3], args[4]);
                  } else if (fn_map.context_whitelist_4.find(op_idx) != fn_map.context_whitelist_4.end()) {
                      auto our_fn = fn_map.context_whitelist_4[op_idx];
                      return our_fn(context, args[0], args[1], args[2], args[3], args[4]);
                  }
                  break;
                }
    }
    BaseRule *brule = context.fn_recall(op_idx, op_rules.size());
    std::cout << "brule: " << brule->to_string() << std::endl;
    return brule->Compile(context, args);
}


const std::string FnOp::to_string() const {
    std::string s = ket_map.get_str(op_idx) + "(";
    bool first_pass = true;
    for (const auto op_rule: op_rules) {
        if (first_pass) {
            s += op_rule->to_string();
            first_pass = false;
        } else {
            s += "," + op_rule->to_string();
        }
    }
    s += ")";
    return s;
}
