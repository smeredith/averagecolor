#include "stdafx.h"
#include <numeric>
#include <functional>
#include <ppl.h>
#include "EveryNIterator.h"
#include "AverageColor_ParallelInvoke.h"

DWORD AverageColor_ParallelInvokeReduce(
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
#pragma warning(disable : 4244) // Guaranteed to fit into a byte because the sum accumulated bytes.

    concurrency::parallel_invoke(
        [&blueAverage, begin, end, pixelCount]()
        {
            blueAverage = concurrency::parallel_reduce(ColorIterator(begin), ColorIterator(end), 0ULL,
                    std::accumulate<ColorIterator, ULONGLONG>,
                    std::plus<ULONGLONG>()) / pixelCount;
        },
        [&greenAverage, begin, end, pixelCount]()
        {
            greenAverage = (concurrency::parallel_reduce(ColorIterator(begin+1), ColorIterator(end-2), 0ULL,
                    std::accumulate<ColorIterator, ULONGLONG>,
                    std::plus<ULONGLONG>()) + *(end-2)) / pixelCount;
        },
        [&redAverage, begin, end, pixelCount]()
        {
            redAverage = (concurrency::parallel_reduce(ColorIterator(begin+2), ColorIterator(end-1), 0ULL,
                    std::accumulate<ColorIterator, ULONGLONG>,
                    std::plus<ULONGLONG>()) + *(end-1)) / pixelCount;
        });

#pragma warning(pop)

    return RGB(redAverage, greenAverage, blueAverage);
}
