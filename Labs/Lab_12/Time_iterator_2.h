#ifndef INTERVAL_ITERATOR_H
#define INTERVAL_ITERATOR_H

#include <iterator>
using namespace std;

template <typename T, typename ValueType>
class IntervalIterator {
private:
    T current;       //текущая позиция
    T end;           // конец контейнера 
    ValueType minV;  // начало интервала
    ValueType maxV;  // конец интервала

    // Вспомогательная функция: пропустить элементы, не входящие в интервал
    void skipInvalid() {
        while (current != end && (*current < minV || *current > maxV)) {
            ++current;
        }
    }

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = typename iterator_traits<T>::value_type;
    using difference_type   = typename iterator_traits<T>::difference_type;
    using pointer           = typename iterator_traits<T>::pointer;
    using reference         = typename iterator_traits<T>::reference;

    // Конструктор
    IntervalIterator(T start, T last, ValueType minVal, ValueType maxVal)
        : current(start), end(last), minV(minVal), maxV(maxVal) {
        skipInvalid(); 
    }

    reference operator*() const {
        return *current;
    }

    //++it
    IntervalIterator& operator++() {
        if (current != end) {
            ++current;
            skipInvalid();
        }
        return *this;
    }
    
    //!=
    bool operator!=(const IntervalIterator& other) const {
        return current != other.current;
    }

    //==
    bool operator==(const IntervalIterator& other) const {
        return current == other.current;
    }
};

#endif