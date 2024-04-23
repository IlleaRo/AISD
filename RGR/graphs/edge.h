#ifndef RGR_EDGE_H
#define RGR_EDGE_H

#include "vertex.h"

template <class VERTEX_T, class E_WEIGHT_T, class E_DATA_T>
class edge {
public:
    VERTEX_T *v1; // Дескриптор вершины, из которой исходит ребро.
    VERTEX_T *v2; // Дескриптор вершины, в которую входит ребро.

    E_WEIGHT_T weight; // Вес ребра
    E_DATA_T data; // Данные, связанные с ребром
};

#endif //RGR_EDGE_H
