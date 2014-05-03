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
        const ColorIterator& end,
        UINT chunkSize)
{
    if ((static_cast<UINT>(end - begin) < chunkSize) || (chunkSize < 2))
    {
        return std::accumulate(begin, end, 0ULL);
    }
    else
    {
        ColorIterator middle = begin + ((end - begin) / 2);
        concurrency::task<ULONGLONG> bottomHalfTask = concurrency::create_task(
            [begin, middle, chunkSize]
            {
                return AccumulateUsingTasks(begin, middle, chunkSize);
            });

        concurrency::task<ULONGLONG> topHalfTask = concurrency::create_task(
            [middle, end, chunkSize]
            {
                return AccumulateUsingTasks(middle, end, chunkSize);
            });

        return bottomHalfTask.get() + topHalfTask.get();
    }
}

DWORD AverageColor_Task(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end)
{
    // Chunksize is the approximate size of one chunk of work for a task, in the number of
    // pixels to process.
    UINT chunkSize = 10000;

    BYTE blueAverage = AccumulateUsingTasks(ColorIterator(begin), ColorIterator(end), chunkSize) / ((end - begin) / 3);
    BYTE greenAverage = AccumulateUsingTasks(ColorIterator(begin+1), ColorIterator(end+1), chunkSize) / ((end - begin) / 3);
    BYTE redAverage = AccumulateUsingTasks(ColorIterator(begin+2), ColorIterator(end+2), chunkSize) / ((end - begin) / 3);

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
