#ifndef RGR_VERTEX_H
#define RGR_VERTEX_H

template <class NAME_T, class DATA_T>
class vertex {
protected:
    unsigned long index; // Индекс вершины в структуре графа или -1 (скрытое поле)
public:
    NAME_T name; // Имя вершины?
    DATA_T data; // Хранимые данные
};

#endif //RGR_VERTEX_H
