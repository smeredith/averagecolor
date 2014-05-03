#pragma once

#include <iterator>

// Iterate over an array of T as if only every nth element exists.
template <typename T, int n>
class EveryNIterator : public std::iterator<std::random_access_iterator_tag, T>
{
    public:
        explicit EveryNIterator(const T& iterator)
        : m_realIterator(iterator)
        {
        }

        typename std::iterator_traits<T>::value_type operator*() const
        {
           return *m_realIterator;
        }

        EveryNIterator& operator++()
        {
            m_realIterator += n;
            return *this;
        }

        EveryNIterator operator++(int)
        {
            EveryNIterator tmp(*this);
            m_realIterator += n;
            return tmp;
        }

        EveryNIterator& operator--()
        {
            m_realIterator -= n;
            return *this;
        }

        typename std::iterator_traits<T>::difference_type operator-(const EveryNIterator& other) const
        {
            return (m_realIterator - other.m_realIterator) / n;
        }

        EveryNIterator operator+ (size_t rhs) const
        {
            return EveryNIterator<T, n>(m_realIterator + (rhs * n));
        }

        bool operator!=(const EveryNIterator& other) const
        {
            return m_realIterator != other.m_realIterator;
        }

        bool operator>=(const EveryNIterator& other) const
        {
            return m_realIterator >= other.m_realIterator;
        }

    private:

        T m_realIterator;
};
