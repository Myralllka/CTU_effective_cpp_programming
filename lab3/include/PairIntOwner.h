//
// Created by myralllka on 11/11/21.
//

#ifndef STORAGE_PAIRINTOWNER_H
#define STORAGE_PAIRINTOWNER_H

#include <PairInt.h>

class PairIntOwner {

public:
    enum Storage {
        INCLUDED [[maybe_unused]],
        DYNAMIC [[maybe_unused]]
    };

    PairIntOwner();

    PairIntOwner(const PairIntOwner &) = delete;

    PairIntOwner(PairIntOwner &&) = delete;

    PairIntOwner operator=(const PairIntOwner &) = delete;

    PairIntOwner operator=(PairIntOwner &&) = delete;

    PairIntOwner(Storage s, int a, int b);

    ~PairIntOwner();

    PairInt &value();
};


#endif //STORAGE_PAIRINTOWNER_H
