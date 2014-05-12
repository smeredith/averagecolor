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

    const size_t pixelCount = (end - begin) / 3;

#pragma warning(push)
#pragma warning(disable : 4244) // Guaranteed to fit into a byte because it accumulated bytes.

    concurrency::parallel_invoke(
        [&blueAverage, begin, end, pixelCount](){blueAverage = std::accumulate(ColorIterator(begin), ColorIterator(end), 0ULL) / pixelCount;},
        [&greenAverage, begin, end, pixelCount](){greenAverage = std::accumulate(ColorIterator(begin+1), ColorIterator(end-2), static_cast<ULONGLONG>(*(end-2))) / pixelCount;},
        [&redAverage, begin, end, pixelCount](){redAverage = std::accumulate(ColorIterator(begin+2), ColorIterator(end-1), static_cast<ULONGLONG>(*(end-1))) / pixelCount;});

#pragma warning(pop)

    return RGB(redAverage, greenAverage, blueAverage);
}
