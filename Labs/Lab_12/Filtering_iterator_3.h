#ifndef FILTER_ITERATOR_H
#define FILTER_ITERATOR_H

#include <iterator>
#include <functional>
using namespace std;

template <typename T, typename ValueType>
class FilterIterator {
private:
    T current;
    T end;
    function<bool(const ValueType&)> predicate; //функция-условие

    // пропуск элементов, которые не соответствуют условию
    void skipInvalid() {
        while (current != end && !predicate(*current)) {
            ++current;
        }
    }

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type        = typename iterator_traits<T>::value_type;
    using difference_type   = typename iterator_traits<T>::difference_type;
    using pointer           = typename iterator_traits<T>::pointer;
    using reference         = typename iterator_traits<T>::reference;

    // Конструктор принимает условие
    FilterIterator(T start, T last, function<bool(const ValueType&)> pred)
        : current(start), end(last), predicate(pred) {
        skipInvalid();
    }

    reference operator*() const {
        return *current;
    }

    FilterIterator& operator++() {
        if (current != end) {
            ++current;
            skipInvalid();
        }
        return *this;
    }

    bool operator!=(const FilterIterator& other) const {
        return current != other.current;
    }

    bool operator==(const FilterIterator& other) const {
        return current == other.current;
    }
};

#endif