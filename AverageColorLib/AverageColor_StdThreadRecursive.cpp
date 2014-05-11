#include "stdafx.h"
#include <numeric>
#include <thread>
#include "EveryNIterator.h"
#include "AverageColor_StdThreadRecursive.h"

// An iterator to iterator over all bytes of one color.
typedef EveryNIterator<std::vector<BYTE>::const_iterator, 3> ColorIterator;

// Divide and conquer version of SumAverages() that uses threads.  ChunkSize represents the
// number of iterations in a single work unit. If there is more work than this, it gets
// recursively divided into two more threads.
void AccumulateUsingThreads(
        const ColorIterator& begin,
        const ColorIterator& end,
        ULONGLONG* pSum)
{
    // Chunksize is the approximate size of one chunk of work for a thread, in the number of
    // pixels to process.
    const size_t chunkSize = 1000000;

    if ((end - begin) < chunkSize)
    {
        *pSum = std::accumulate(begin, end, 0ULL);
    }
    else
    {
        ColorIterator middle = begin + ((end - begin) / 2);
        ULONGLONG bottomHalfSum;
        std::thread bottomHalfThread = std::thread(AccumulateUsingThreads, begin, middle, &bottomHalfSum);

        ULONGLONG topHalfSum;
        AccumulateUsingThreads(middle, end, &topHalfSum);
        bottomHalfThread.join();

        *pSum = bottomHalfSum + topHalfSum;
    }
}

DWORD AverageColor_StdThreadRecursive(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end)
{
    ULONGLONG blueSum;
    auto blueThread = std::thread(AccumulateUsingThreads, ColorIterator(begin), ColorIterator(end), &blueSum);

    ULONGLONG greenSum;
    auto greenThread = std::thread(AccumulateUsingThreads, ColorIterator(begin+1), ColorIterator(end-2), &greenSum);
    greenSum += *(end-2);

    ULONGLONG redSum;
    AccumulateUsingThreads(ColorIterator(begin+2), ColorIterator(end-1), &redSum);
    redSum += *(end-1);

    const size_t pixelCount = (end - begin) / 3;

    blueThread.join();
    greenThread.join();

#pragma warning(push)
#pragma warning(disable : 4244) // Guaranteed to fit into a byte because the sum accumulated bytes.

    const BYTE blueAverage = blueSum / pixelCount;
    const BYTE redAverage = redSum / pixelCount;
    const BYTE greenAverage = greenSum / pixelCount;

#pragma warning(pop)

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
