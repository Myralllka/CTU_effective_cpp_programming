#ifndef PAIRINT_H
#define PAIRINT_H

class PairInt {
    int a_, b_;

    static long constructed_;
    static long alive_;
    static long destructed_;

public:
    PairInt(int a, int b) : a_(a), b_(b) {
        constructed_++;
        alive_++;
    }

    ~PairInt() {
        destructed_++;
        alive_--;
    }

    PairInt(const PairInt &) = delete;

    PairInt(PairInt &&) = delete;

    PairInt &operator=(const PairInt &) = delete;

    PairInt &operator=(PairInt &&) = delete;

    int &a() { return a_; }

    int &b() { return b_; }

    static long constructed() { return constructed_; }

    static long alive() { return alive_; }

    static long destructed() { return destructed_; }
};

#endif