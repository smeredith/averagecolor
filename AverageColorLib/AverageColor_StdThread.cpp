#include "stdafx.h"
#include <numeric>
#include <thread>
#include "EveryNIterator.h"
#include "AverageColor_StdThread.h"

// An iterator to iterator over all bytes of one color.
typedef EveryNIterator<std::vector<BYTE>::const_iterator, 3> ColorIterator;

void Accumulate(ColorIterator begin, ColorIterator last, ULONGLONG* pResult)
{
    *pResult = std::accumulate(begin, last, static_cast<ULONGLONG>(*last));
}

DWORD AverageColor_StdThread(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end)
{
    const size_t pixelCount = (end - begin) / 3;

    ULONGLONG greenTotal;
    ULONGLONG redTotal;
    auto greenThread = std::thread(Accumulate, ColorIterator(begin+1), ColorIterator(end-2), &greenTotal);
    auto redThread = std::thread(Accumulate, ColorIterator(begin+2), ColorIterator(end-1), &redTotal);

#pragma warning(push)
#pragma warning(disable : 4244) // Guaranteed to fit into a byte because it accumulated bytes.

    BYTE blueAverage;
    BYTE greenAverage;
    BYTE redAverage;

    blueAverage = std::accumulate(ColorIterator(begin), ColorIterator(end), 0ULL) / pixelCount;

    greenThread.join();
    greenAverage = greenTotal / pixelCount;

    redThread.join();
    redAverage = redTotal / pixelCount;

#pragma warning(pop)

    return RGB(redAverage, greenAverage, blueAverage);
}
