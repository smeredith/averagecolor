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

    BYTE blueAverage;
    BYTE greenAverage;
    BYTE redAverage;

    blueAverage = concurrency::parallel_reduce(ColorIterator(begin), ColorIterator(end), 0ULL,
            std::accumulate<ColorIterator, ULONGLONG>,
            [](ULONGLONG a, ULONGLONG b){return a+b;}) / ((end - begin) / 3);
    greenAverage = concurrency::parallel_reduce(ColorIterator(begin+1), ColorIterator(end+1), 0ULL,
            std::accumulate<ColorIterator, ULONGLONG>,
            [](ULONGLONG a, ULONGLONG b){return a+b;}) / ((end - begin) / 3);
    redAverage = concurrency::parallel_reduce(ColorIterator(begin+2), ColorIterator(end+2), 0ULL,
            std::accumulate<ColorIterator, ULONGLONG>,
            [](ULONGLONG a, ULONGLONG b){return a+b;}) / ((end - begin) / 3);


    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
