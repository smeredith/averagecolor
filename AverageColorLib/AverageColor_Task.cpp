#include "stdafx.h"
#include <numeric>
#include <ppltasks.h>
#include "AverageColor_Task.h"

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
    const ColorIterator& blueBegin, const ColorIterator& blueEnd,
    const ColorIterator& greenBegin, const ColorIterator& greenEnd,
    const ColorIterator& redBegin, const ColorIterator& redEnd,
    UINT chunkSize)
{
    if (chunkSize == 0)
    {
        chunkSize = 5000;
    }

    BYTE blueAverage = AccumulateUsingTasks(blueBegin, blueEnd, chunkSize) / (blueEnd - blueBegin);
    BYTE greenAverage = AccumulateUsingTasks(greenBegin, greenEnd, chunkSize) / (greenEnd - greenBegin);
    BYTE redAverage = AccumulateUsingTasks(redBegin, redEnd, chunkSize) / (redEnd - redBegin);

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
