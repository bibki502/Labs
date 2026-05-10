#ifndef TRANSFORM_ITERATOR_H
#define TRANSFORM_ITERATOR_H

#include <iterator>
#include <functional>
using namespace std;

template <typename T, typename InputType, typename OutputType>
class TransformIterator {
private:
    T current;
    function<OutputType(const InputType&)> transformer; // функция преобразования

public:
    // категория итератора и типы
    using iterator_category = forward_iterator_tag;
    using value_type        = OutputType;
    using difference_type   = typename iterator_traits<T>::difference_type;
    using pointer           = OutputType*;
    using reference         = OutputType; 

    // Конструктор
    TransformIterator(T it, std::function<OutputType(const InputType&)> func)
        : current(it), transformer(func) {}

    // * при разыменовании применяем функцию
    OutputType operator*() const {
        return transformer(*current);
    }

    // ++it
    TransformIterator& operator++() {
        ++current;
        return *this;
    }

    bool operator!=(const TransformIterator& other) const {
        return current != other.current;
    }

    bool operator==(const TransformIterator& other) const {
        return current == other.current;
    }
};

#endif