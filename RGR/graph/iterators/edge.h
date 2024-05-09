#ifndef EDGE_ITERATOR_H
#define EDGE_ITERATOR_H

#include "../graph.h"

template <class VERTEX_T, class EDGE_T>
class graph;

template <class VERTEX_T, class EDGE_T>
class edgeIterator {
    VERTEX_T *curVertex;
    graph<VERTEX_T, EDGE_T> *curGraph;
    EDGE_T *curEdge;
    bool graphUndefined;

public:
    explicit edgeIterator() : curGraph(0), graphUndefined(true) {}
    explicit edgeIterator(graph<VERTEX_T, EDGE_T> *graph) : curGraph(graph), graphUndefined(false) {}

    EDGE_T *operator*() {
        if (graphUndefined || *this == curGraph->edge_end()) {
            throw std::out_of_range("out of range exception");
        }

        return curEdge;
    }

    edgeIterator &operator++() {
        if (graphUndefined) return *this;
        if (*this == curGraph->edge_end()) {
            throw std::out_of_range("out of range exception");
        }

        next:
        do {
            if ((curEdge = curGraph->nextEdge(curVertex, curEdge))) {
                if (curGraph->getType() == NON_DIRECTED &&
                    curVertex == curEdge->getDest()) {
                    continue;
                }

                return *this;
            }
        } while (curEdge);

        for (unsigned long i = curVertex->getIndex() + 1; i < curGraph->getVertexCount(); ++i) {
            curVertex = curGraph->vertices[i];
            if ((curEdge = curGraph->firstEdge(curVertex))) {
                // Пропускаем повторные рёбра
                if (curGraph->getType() == NON_DIRECTED && curVertex == curEdge->getDest()) {
                    goto next;
                }

                return *this;
            }
        }

        *this = curGraph->edge_end();

        return *this;
    }

    bool operator!=(const edgeIterator& other) const {
        if (graphUndefined) return false;
        if (curVertex != other.curVertex) {
            return true;
        }

        if (curEdge != other.curEdge) {
            return true;
        }

        return false;
    }

    bool operator==(const edgeIterator& other) const {
        if (graphUndefined) return false;
        if (curVertex != other.curVertex) {
            return false;
        }

        if (curEdge != other.curEdge) {
            return false;
        }

        return true;
    }

    void setEdge(EDGE_T *new_cur_edge) {
        if (graphUndefined) return;
        curEdge = new_cur_edge;
    }

    void setVertex(VERTEX_T *new_cur_vertex) {
        if (graphUndefined) return;
        curVertex = new_cur_vertex;
    }

    bool isUndefined() {
        return graphUndefined;
    }
};

#endif //EDGE_ITERATOR_H
