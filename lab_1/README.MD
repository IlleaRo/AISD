# Практическая работа "Коллекция данных - список"
## Вариант 7
Структура данных - кольцевая, двухсвязная, на базе адресных указателей

## Заметки
1. Итераторы (прямой и обратный) являются разными классами - не надо ничего наследовать
2. end() можно использовать вместо rend(). Сказала, что с нашей структурой можно работать и так. end() должен возвращать iterator указывающий на узел NULL, указатель на лист остается.
3. НЕ надо добавлять другие конструкторы для листа: нужны только без параметров и копирования
4. НЕ надо добавлять другие конструкторы для узлов.
5. Итераторы перескакивают с конца на начало списка для обычного и с начала на конец для обратного.
6. Необходимо использовать throw в "опасных" местах.