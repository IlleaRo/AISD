#ifndef RGR_EDGE_H
#define RGR_EDGE_H

template <class VERTEX_T, class E_WEIGHT_T, class E_DATA_T>
class edge {
protected:
    VERTEX_T *v1; // Дескриптор вершины, из которой исходит ребро.
    VERTEX_T *v2; // Дескриптор вершины, в которую входит ребро.

    E_WEIGHT_T weight; // Вес ребра
    E_DATA_T data; // Данные, связанные с ребром

public:
    edge() : v1(nullptr), v2(nullptr), weight(0) {};
    edge(VERTEX_T *v1, VERTEX_T *v2) : v1(v1), v2(v2), weight(0) {};
    edge(VERTEX_T *v1, VERTEX_T *v2, E_WEIGHT_T weight) : v1(v1), v2(v2), weight(weight) {};

    [[nodiscard]] VERTEX_T *get_v1() const {
        return v1;
    }

    [[nodiscard]] VERTEX_T *get_v2() const {
        return v2;
    }

    [[nodiscard]] E_WEIGHT_T get_weight() const {
        return weight;
    }

    void set_weight(E_WEIGHT_T new_weight) {
        weight = new_weight;
    }

    [[nodiscard]] E_DATA_T get_data() const {
        return data;
    }

    void set_data(E_DATA_T new_data) {
        data = new_data;
    }
};

#endif //RGR_EDGE_H
