#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include <iterator>
using namespace std;

template <typename T>
class MyReverseIterator {
private:
    T current;
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type        = typename iterator_traits<T>::value_type;
    using difference_type   = typename iterator_traits<T>::difference_type;
    using pointer           = typename iterator_traits<T>::pointer;
    using reference         = typename iterator_traits<T>::reference;

    // конструктор
    explicit MyReverseIterator(T it) : current(it) {}

    // оператор разыменования
    reference operator*() const {
        T temp = current;
        return *(--temp);
    }

    // ++it
    MyReverseIterator& operator++() {
        --current;
        return *this;
    }

    //it++
    MyReverseIterator operator++(int) {
        MyReverseIterator temp = *this;
        --current;
        return temp;
    }

    // Оператор сравнения 
    bool operator!=(const MyReverseIterator& other) const {
        return current != other.current;
    }

    bool operator==(const MyReverseIterator& other) const {
        return current == other.current;
    }
};

#endif