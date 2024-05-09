#ifndef COMMON_H
#define COMMON_H

typedef enum {
    DIRECTED,
    NON_DIRECTED
} graphTypeE;

typedef enum {
    L,
    M
} graphFormE;

template <class EDGE_T>
class form;

template <class EDGE_T>
std::ostream& operator<< (std::ostream &os, form<EDGE_T> &plist) {
    plist.print(os);
    return os;
}

template <class EDGE_T>
class form{
    protected:
    graphTypeE type;
    graphFormE curForm;

    unsigned long edgeCount; // Число ребер

    virtual void print(std::ostream &os) = 0;

    form(graphTypeE type, graphFormE form, unsigned long num_of_edges) :
        type(type), curForm(form), edgeCount(num_of_edges) {};
    public:
    virtual ~form() = default;

    // Число ребер в графе
    [[nodiscard]] unsigned long getEdgeCount() const {
        return edgeCount;
    }

    [[nodiscard]] graphTypeE getType() const {
        return type;
    }

    [[nodiscard]] graphFormE getForm() const {
        return curForm;
    }

    virtual EDGE_T *getEdge(unsigned long v1_index, unsigned long v2_index) = 0;

    virtual bool popEdge(unsigned long v1_index, unsigned long v2_index) = 0;

    virtual unsigned long pushVertex() = 0;

    virtual bool popVertex(unsigned long vertex_index) = 0;

    virtual bool pushEdge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) = 0;

    virtual EDGE_T *firstEdge(unsigned long vertex_index) = 0;

    virtual EDGE_T *nextEdge(unsigned long vertex_index, EDGE_T *edge) = 0;

    friend std::ostream& operator<< <>(std::ostream &os, form<EDGE_T> &plist);
};

#endif //COMMON_H
