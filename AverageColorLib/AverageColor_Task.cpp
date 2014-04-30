#include "stdafx.h"
#include <ppltasks.h>
#include "ColorCalculations.h"
#include "AverageColor_Serial.h"
#include "AverageColor_Task.h"

// Divide and conquer version of SumAverages() that uses tasks.  ChunkSize represents the
// number of iterations in a single work unit. If there is more work than this, it gets
// recursively divided into two more tasks.
PixelColorSums SumAveragesUsingTasks(
        RawBitmap::PixelColorVector::iterator begin,
        RawBitmap::PixelColorVector::iterator end,
        UINT chunkSize)
{
    if ((static_cast<UINT>(end - begin) < chunkSize) || (chunkSize < 2))
    {
        return SumAverages(begin, end);
    }
    else
    {
        RawBitmap::PixelColorVector::iterator middle = begin + ((end - begin) / 2);
        concurrency::task<PixelColorSums> bottomHalfTask = concurrency::create_task(
            [begin, middle, chunkSize]
            {
                return SumAveragesUsingTasks(begin, middle, chunkSize);
            });

        concurrency::task<PixelColorSums> topHalfTask = concurrency::create_task(
            [middle, end, chunkSize]
            {
                return SumAveragesUsingTasks(middle, end, chunkSize);
            });

        return bottomHalfTask.get() + topHalfTask.get();
    }
}

DWORD AverageColor_Task(
        RawBitmap::PixelColorVector::iterator begin,
        RawBitmap::PixelColorVector::iterator end,
        UINT chunkSize)
{
    if (chunkSize == 0)
    {
        chunkSize = 10000;
    }

    return CalculateAverage(SumAveragesUsingTasks(begin, end, chunkSize), end - begin);
}
