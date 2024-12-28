#ifndef GQ_H
#define GQ_H

#include <vector>

// Рандомизированная очередь
template <class ITEM>
class randomized_queue {
    std::vector<ITEM> s;
    unsigned long N;
public:
    explicit randomized_queue(const unsigned long max_N) : s(max_N + 1), N(0) {}

    [[nodiscard]] bool is_empty() const {
        return N == 0;
    }

    void put(ITEM item) {
        s[N++] = item;
    }

    [[nodiscard]] ITEM get() {
        unsigned long i = N * rand()/(1.0 + RAND_MAX);
        ITEM tmp = s[i];
        s[i] = s[N-1];
        s[N-1] = tmp;
        return s[--N];
    }
};



#endif //GQ_H
