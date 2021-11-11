//
// Created by myralllka on 11/11/21.
//

#ifndef STORAGE_PAIRINTOWNER_H
#define STORAGE_PAIRINTOWNER_H

#include "PairInt.h"

class PairIntOwner {
private:
    union {
        alignas(PairInt) unsigned char m_value[sizeof(PairInt)];
        PairInt *m_dyn_object;
    };
    bool m_is_dyn = false;


    PairInt *ptr() {
        return (m_is_dyn ? m_dyn_object : reinterpret_cast<PairInt *>(m_value));
    }

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

    ~PairIntOwner();

    PairIntOwner(Storage s, int a, int b);

    PairInt &value();
};


#endif //STORAGE_PAIRINTOWNER_H
