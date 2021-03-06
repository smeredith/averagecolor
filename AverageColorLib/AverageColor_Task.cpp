#include "stdafx.h"
#include <numeric>
#include <ppltasks.h>
#include "EveryNIterator.h"
#include "AverageColor_Task.h"

// An iterator to iterator over all bytes of one color.
typedef EveryNIterator<std::vector<BYTE>::const_iterator, 3> ColorIterator;

// Divide and conquer version of SumAverages() that uses tasks.  ChunkSize represents the
// number of iterations in a single work unit. If there is more work than this, it gets
// recursively divided into two more tasks.
ULONGLONG AccumulateUsingTasks(
        const ColorIterator& begin,
        const ColorIterator& end)
{
    // Chunksize is the approximate size of one chunk of work for a task, in the number of
    // pixels to process.
    const size_t chunkSize = 200000;

    if ((end - begin) < chunkSize)
    {
        return std::accumulate(begin, end, 0ULL);
    }
    else
    {
        ColorIterator middle = begin + ((end - begin) / 2);
        concurrency::task<ULONGLONG> bottomHalfTask = concurrency::create_task(
            [begin, middle]
            {
                return AccumulateUsingTasks(begin, middle);
            });

        ULONGLONG topHalfSum = AccumulateUsingTasks(middle, end);
        return topHalfSum + bottomHalfTask.get();
    }
}

DWORD AverageColor_Task(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end)
{
    concurrency::task<ULONGLONG> blueSum = concurrency::create_task(
        [begin, end]()
        {
            return AccumulateUsingTasks(ColorIterator(begin), ColorIterator(end));
        });

    concurrency::task<ULONGLONG> greenSum = concurrency::create_task(
        [begin, end]()
        {
            return AccumulateUsingTasks(ColorIterator(begin+1), ColorIterator(end-2)) + *(end-2);
        });

    ULONGLONG redSum = AccumulateUsingTasks(ColorIterator(begin+2), ColorIterator(end-1)) + *(end-1);

    const size_t pixelCount = (end - begin) / 3;

#pragma warning(push)
#pragma warning(disable : 4244) // Guaranteed to fit into a byte because the sum accumulated bytes.

    const BYTE blueAverage = blueSum.get() / pixelCount;
    const BYTE greenAverage = greenSum.get() / pixelCount;
    const BYTE redAverage = redSum / pixelCount;

#pragma warning(pop)

    return RGB(redAverage, greenAverage, blueAverage);
}
