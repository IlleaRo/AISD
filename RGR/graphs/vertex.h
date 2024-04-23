#ifndef RGR_VERTEX_H
#define RGR_VERTEX_H

template <class NAME_T, class DATA_T>
class vertex {
protected:
    unsigned long index; // Индекс вершины в структуре графа или -1 (скрытое поле)

    NAME_T name; // Имя вершины
    DATA_T data; // Хранимые данные
public:
    vertex() : index(-1){};
    explicit vertex(unsigned long index) : index(index){};
    explicit vertex(NAME_T name) : index(-1), name(name){};

    [[nodiscard]] unsigned long get_index() const {
        return index;
    }

    void set_name(NAME_T new_name) {
        name = new_name;
    }

    NAME_T &get_name() {
        return name;
    }

    void set_data(DATA_T new_data) {
        data = new_data;
    }

    DATA_T &get_data() {
        return data;
    }
};

#endif //RGR_VERTEX_H
