#ifndef VERTEX_H
#define VERTEX_H

template<class NAME_T, class DATA_T>
class vertex
{
    protected:
        unsigned long index;
        NAME_T name;
        DATA_T data;

    public:
        explicit vertex(size_t index) : index(index)
        {
        };
        explicit vertex(size_t index, NAME_T name) : index(index), name(name)
        {
        };

        [[nodiscard]] size_t getIndex() const
        {
            return index;
        }

        void setName(NAME_T name)
        {
            this->name = name;
        }

        NAME_T getName()
        {
            return name;
        }

        void setData(DATA_T data)
        {
            this->data = data;
        }

        DATA_T get_data()
        {
            return data;
        }

        void forceIndex(size_t index)
        {
            this->index = index;
        }
};

#endif //VERTEX_H
