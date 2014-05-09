#include "stdafx.h"
#include <numeric>
#include <ppl.h>
#include "EveryNIterator.h"
#include "AverageColor_ParallelInvoke.h"

DWORD AverageColor_ParallelReduce(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end)
{
    // An iterator to iterator over all bytes of one color.
    typedef EveryNIterator<std::vector<BYTE>::const_iterator, 3> ColorIterator;

    const size_t pixelCount = (end - begin) / 3;

#pragma warning(push)
#pragma warning(disable : 4244) // Guaranteed to fit into a byte because the sum accumulated bytes.

    const BYTE blueAverage = concurrency::parallel_reduce(
            ColorIterator(begin),
            ColorIterator(end),
            0ULL,
            std::accumulate<ColorIterator, ULONGLONG>,
            std::plus<ULONGLONG>()) / pixelCount;

    // Read one BYTE less than we should so we don't set the ColorIterator past the end of
    // the real iterator, then add in the last one.
    const BYTE greenAverage = (concurrency::parallel_reduce(
            ColorIterator(begin+1),
            ColorIterator(end-2),
            0ULL,
            std::accumulate<ColorIterator, ULONGLONG>,
            std::plus<ULONGLONG>()) + *(end-2)) / pixelCount;

    const BYTE redAverage = (concurrency::parallel_reduce(
            ColorIterator(begin+2),
            ColorIterator(end-1),
            0ULL,
            std::accumulate<ColorIterator, ULONGLONG>,
            std::plus<ULONGLONG>()) + *(end-1)) / pixelCount;

#pragma warning(pop)

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
