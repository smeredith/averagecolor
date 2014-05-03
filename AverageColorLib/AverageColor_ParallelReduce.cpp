#include "stdafx.h"
#include <numeric>
#include <ppl.h>
#include "AverageColor_ParallelInvoke.h"

DWORD AverageColor_ParallelReduce(
    const ColorIterator& blueBegin, const ColorIterator& blueEnd,
    const ColorIterator& greenBegin, const ColorIterator& greenEnd,
    const ColorIterator& redBegin, const ColorIterator& redEnd)
{
    BYTE blueAverage;
    BYTE greenAverage;
    BYTE redAverage;

    blueAverage = concurrency::parallel_reduce(blueBegin, blueEnd, 0ULL,
            std::accumulate<ColorIterator, ULONGLONG>,
            [](ULONGLONG a, ULONGLONG b){return a+b;}) / (blueEnd - blueBegin);
    redAverage = concurrency::parallel_reduce(redBegin, redEnd, 0ULL,
            std::accumulate<ColorIterator, ULONGLONG>,
            [](ULONGLONG a, ULONGLONG b){return a+b;}) / (redEnd - redBegin);
    greenAverage = concurrency::parallel_reduce(greenBegin, greenEnd, 0ULL,
            std::accumulate<ColorIterator, ULONGLONG>,
            [](ULONGLONG a, ULONGLONG b){return a+b;}) / (greenEnd - greenBegin);


    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
