#ifndef RGR_VERTEX_H
#define RGR_VERTEX_H

template <class NAME_T, class DATA_T>
class vertex {
protected:
    unsigned long index; // Индекс вершины в структуре графа или -1 (скрытое поле)
public:
    NAME_T name; // Имя вершины
    DATA_T data; // Хранимые данные

    vertex() : index(0){};
    explicit vertex(unsigned long index) : index(index){};

    [[nodiscard]] unsigned long get_index() const {
        return index;
    }
};

#endif //RGR_VERTEX_H
