#ifndef EDGE_H
#define EDGE_H

#include "vertex.h"

template<class VERTEX_T, class E_WEIGHT_T, class E_DATA_T>
class edge
{
    protected:
        VERTEX_T *src;
        VERTEX_T *dest;

        E_WEIGHT_T weight;
        E_DATA_T data;

    public:
        edge(VERTEX_T *src, VERTEX_T *dest) : src(src), dest(dest), weight(0)
        {
        };
        edge(VERTEX_T *src, VERTEX_T *dest, E_WEIGHT_T weight) : src(src), dest(dest), weight(weight)
        {
        };

        [[nodiscard]] VERTEX_T *getSrc() const
        {
            return src;
        }

        [[nodiscard]] VERTEX_T *getDest() const
        {
            return dest;
        }

        [[nodiscard]] E_WEIGHT_T getWeight() const
        {
            return weight;
        }

        void setWeight(E_WEIGHT_T weight)
        {
            this->weight = weight;
        }

        [[nodiscard]] E_DATA_T getData() const
        {
            return data;
        }

        void setData(E_DATA_T new_data)
        {
            data = new_data;
        }
};

#endif //EDGE_H
