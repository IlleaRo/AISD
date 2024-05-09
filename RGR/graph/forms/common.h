#ifndef COMMON_H
#define COMMON_H

typedef enum {
    DIRECTED,
    NON_DIRECTED
} graph_type_e;

typedef enum {
    L,
    M
} graph_form_e;

template <class EDGE_T>
class form_of_graphs;

template <class EDGE_T>
std::ostream& operator<< (std::ostream &os, form_of_graphs<EDGE_T> &plist) {
    plist.print_graph(os);
    return os;
}

template <class EDGE_T>
class form_of_graphs{
    protected:
    graph_type_e type;
    graph_form_e form;

    unsigned long num_of_edges; // Число ребер

    virtual void print_graph(std::ostream &os) = 0;

    form_of_graphs(graph_type_e type, graph_form_e form, unsigned long num_of_edges) :
        type(type), form(form), num_of_edges(num_of_edges) {};
    public:
    virtual ~form_of_graphs() = default;

    // Число ребер в графе
    [[nodiscard]] unsigned long get_num_of_edges() const {
        return num_of_edges;
    }

    [[nodiscard]] graph_type_e get_type() const {
        return type;
    }

    [[nodiscard]] graph_form_e get_form() const {
        return form;
    }

    virtual EDGE_T *get_edge(unsigned long v1_index, unsigned long v2_index) = 0;

    virtual bool remove_edge(unsigned long v1_index, unsigned long v2_index) = 0;

    virtual unsigned long insert_vertex() = 0;

    virtual bool remove_vertex(unsigned long vertex_index) = 0;

    virtual bool insert_edge(unsigned long v_index_1, unsigned long v_index_2, EDGE_T *edge) = 0;

    virtual EDGE_T *get_first_edge(unsigned long vertex_index) = 0;

    virtual EDGE_T *get_next_edge(unsigned long vertex_index, EDGE_T *edge) = 0;

    friend std::ostream& operator<< <>(std::ostream &os, form_of_graphs<EDGE_T> &plist);
};

#endif //COMMON_H
