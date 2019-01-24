#ifndef BASECOMPOUNDSEQ_H
#define BASECOMPOUNDSEQ_H

#include <string>

class Sequence;
class ContextList;

class BaseCompoundSeq {
    private:
    public:
        virtual Sequence Compile(ContextList& context) = 0;
        virtual std::string to_string() = 0;
};

#endif
