#include "stdafx.h"
#include <numeric>
#include <ppl.h>
#include "AverageColor_ParallelInvoke.h"

DWORD AverageColor_ParallelInvoke(
    ColorIterator blueBegin, ColorIterator blueEnd,
    ColorIterator greenBegin, ColorIterator greenEnd,
    ColorIterator redBegin, ColorIterator redEnd)
{
    BYTE blueAverage;
    BYTE greenAverage;
    BYTE redAverage;

    concurrency::parallel_invoke(
        [&blueAverage, &blueBegin, &blueEnd](){blueAverage = std::accumulate(blueBegin, blueEnd, 0ULL) / (blueEnd - blueBegin);},
        [&greenAverage, &greenBegin, &greenEnd](){greenAverage = std::accumulate(greenBegin, greenEnd, 0ULL) / (greenEnd - greenBegin);},
        [&redAverage, &redBegin, &redEnd](){redAverage = std::accumulate(redBegin, redEnd, 0ULL) / (redEnd - redBegin);});

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
