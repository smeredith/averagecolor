#include "stdafx.h"
#include <numeric>
#include <ppl.h>
#include "EveryNIterator.h"
#include "AverageColor_ParallelInvoke.h"

DWORD AverageColor_ParallelInvoke(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end)
{
    // An iterator to iterator over all bytes of one color.
    typedef EveryNIterator<std::vector<BYTE>::const_iterator, 3> ColorIterator;

    BYTE blueAverage;
    BYTE greenAverage;
    BYTE redAverage;

#pragma warning(push)
#pragma warning(disable : 4244) // Guaranteed to fit into a byte because it accumulated bytes.

    concurrency::parallel_invoke(
        [&blueAverage, begin, end](){blueAverage = std::accumulate(ColorIterator(begin), ColorIterator(end), 0ULL) / ((end - begin) / 3);},
        [&greenAverage, begin, end](){greenAverage = std::accumulate(ColorIterator(begin+1), ColorIterator(end+1), 0ULL) / ((end - begin) / 3);},
        [&redAverage, begin, end](){redAverage = std::accumulate(ColorIterator(begin+2), ColorIterator(end+2), 0ULL) / ((end - begin) / 3);});

#pragma warning(pop)

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
