#ifndef MULTI_ITERATOR_H
#define MULTI_ITERATOR_H

#include <iterator>

template <typename T>
class MultiIterator {
private:
    T current;      // текущая позиция
    T end1;         // конец первого контейнера
    T begin2;       // начало второго контейнера
    T end2;         // конец второго контейнера
    bool inFirst;   //флаг

    // логика переключения
    void checkSwitch() {
        if (inFirst && current == end1) {
            current = begin2;
            inFirst = false;
        }
    }

public:
    using iterator_category = forward_iterator_tag;
    using value_type        = typename iterator_traits<T>::value_type;
    using difference_type   = typename iterator_traits<T>::difference_type;
    using pointer           = typename iterator_traits<T>::pointer;
    using reference         = typename iterator_traits<T>::reference;

    // Конструктор
    MultiIterator(T b1, T e1, T b2, T e2, bool startInFirst = true)
        : current(startInFirst ? b1 : e2), 
          end1(e1), begin2(b2), end2(e2), 
          inFirst(startInFirst) 
    {
        if (inFirst) checkSwitch();
    }

    reference operator*() const {
        return *current;
    }

    MultiIterator& operator++() {
        if (inFirst || current != end2) {
            ++current;
            checkSwitch();
        }
        return *this;
    }

    bool operator!=(const MultiIterator& other) const {
        return current != other.current || inFirst != other.inFirst;
    }

    bool operator==(const MultiIterator& other) const {
        return !(*this != other);
    }
};

#endif