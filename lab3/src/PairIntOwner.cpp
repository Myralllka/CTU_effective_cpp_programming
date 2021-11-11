// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

//
// Created by myralllka on 11/11/21.
//

#include "PairIntOwner.h"
#include <new> // I have no idea how to do it without including new,

PairIntOwner::PairIntOwner() = default;

PairIntOwner::PairIntOwner(PairIntOwner::Storage s, int a, int b) : m_is_dyn(s != INCLUDED) {

    if (s == INCLUDED) {
        // as far as I can not move this object, can not copy part of the memory..
        // placement new is the only one possible solution that I can see...
        // but to use it I must include <new> and violate the lab work rules =(
        // Also I can not overload the `new` operator for the PairInt class (it can be like)
        //  void* operator new(unsigned long s, void *memory) {
        //        return memory;
        //    }
        // and then here `new(&m_value) PairInt(a, b);`
        // I tried, it worked... resource (https://www.embedded.com/calling-constructors-with-placement-new/)

        new(m_value) PairInt(a, b);


    } else if (s == DYNAMIC) {
        m_dyn_object = new PairInt(a, b);
    }
}

PairIntOwner::~PairIntOwner() { ptr()->~PairInt(); }

PairInt &PairIntOwner::value() {
    return *ptr();
}
