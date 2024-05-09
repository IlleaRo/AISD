#ifndef VERTEXEDGE_ITERATOR_H
#define VERTEXEDGE_ITERATOR_H

template<class VERTEX_T, class EDGE_T>
class graph;

template<class VERTEX_T, class EDGE_T>
class vertexEdgeIter
{
    VERTEX_T *curVertex;
    graph<VERTEX_T, EDGE_T> *curGraph;
    EDGE_T *curEdge;
    bool graphUndefined;

    public:
        vertexEdgeIter() : curVertex(nullptr), curGraph(nullptr), curEdge(nullptr), graphUndefined(true)
        {
        }

        vertexEdgeIter(graph<VERTEX_T, EDGE_T> *graph, VERTEX_T *vertex)
        {
            this->curVertex = vertex;
            this->curEdge = graph->firstEdge(vertex);
            this->curGraph = graph;
            graphUndefined = false;
        }

        vertexEdgeIter(vertexEdgeIter const &other)
        {
            curVertex = other.curVertex;
            curGraph = other.curGraph;
            curEdge = other.curEdge;
            graphUndefined = false;
        }

        EDGE_T *operator*()
        {
            if (graphUndefined || *this == curGraph->edge_v_end(curVertex))
            {
                throw std::out_of_range("out of range exception");
            }

            return curEdge;
        }

        vertexEdgeIter &operator++()
        {
            if (graphUndefined || *this == curGraph->edge_v_end(curVertex))
            {
                throw std::out_of_range("out of range exception");
            }

            curEdge = curGraph->nextEdge(curVertex, curEdge);
            return *this;
        }

        bool operator!=(const vertexEdgeIter &other) const
        {
            if (curVertex != other.curVertex)
            {
                return true;
            }

            if (curEdge != other.curEdge)
            {
                return true;
            }

            return false;
        }

        bool operator==(const vertexEdgeIter &other) const
        {
            if (curVertex != other.curVertex)
            {
                return false;
            }

            if (curEdge != other.curEdge)
            {
                return false;
            }

            return true;
        }

        void setEdge(EDGE_T *new_cur_edge)
        {
            curEdge = new_cur_edge;
        }

        bool isUndefined()
        {
            return graphUndefined;
        }
};

#endif //VERTEXEDGE_ITERATOR_H
