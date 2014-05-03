#pragma once

#include <iterator>

// Iterate over an array of It as if only every nth element exists.
// Initialize from a normal iterator.
template <typename It, int n>
class EveryNIterator : public std::iterator<std::random_access_iterator_tag, It>
{
    public:
        explicit EveryNIterator(const It& iterator)
        : m_realIterator(iterator)
        {
        }

        EveryNIterator(It&& iterator)
        : m_realIterator(std::move(iterator))
        {
        }

        EveryNIterator(EveryNIterator&& other)
        : m_realIterator(std::move(other.m_realIterator))
        {
        }

        EveryNIterator& operator=(It&& rhs)
        {
            m_realIterator = std::move(rhs.m_realIterator);
        }

        typename std::iterator_traits<It>::value_type operator*() const
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

        typename std::iterator_traits<It>::difference_type operator-(const EveryNIterator& other) const
        {
            return (m_realIterator - other.m_realIterator) / n;
        }

        EveryNIterator operator+ (size_t rhs) const
        {
            return EveryNIterator<It, n>(m_realIterator + (rhs * n));
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

        It m_realIterator;
};
