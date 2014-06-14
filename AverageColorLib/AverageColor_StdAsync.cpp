#include "stdafx.h"
#include <numeric>
#include <future>
#include "EveryNIterator.h"
#include "AverageColor_StdThread.h"

// An iterator to iterator over all bytes of one color.
typedef EveryNIterator<std::vector<BYTE>::const_iterator, 3> ColorIterator;

DWORD AverageColor_StdAsync(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end)
{
    const size_t pixelCount = (end - begin) / 3;

    // Run the first calculation on the current thread when .get() is called.
    std::future<ULONGLONG> blueTotal = std::async(std::launch::deferred,
         std::accumulate<ColorIterator, ULONGLONG>, ColorIterator(begin), ColorIterator(end), 0ULL);

    // Run the next two on seperate threads.
    std::future<ULONGLONG> greenTotal = std::async(std::launch::async,
        std::accumulate<ColorIterator, ULONGLONG>, ColorIterator(begin + 1), ColorIterator(end - 2), static_cast<ULONGLONG>(*(end - 2)));
    std::future<ULONGLONG> redTotal = std::async(std::launch::async,
        std::accumulate<ColorIterator, ULONGLONG>, ColorIterator(begin + 2), ColorIterator(end - 1), static_cast<ULONGLONG>(*(end - 1)));

#pragma warning(push)
#pragma warning(disable : 4244) // Guaranteed to fit into a byte because it accumulated bytes.

    const BYTE blueAverage = blueTotal.get() / pixelCount;
    const BYTE greenAverage = greenTotal.get()  / pixelCount;
    const BYTE redAverage = redTotal.get() / pixelCount;

#pragma warning(pop)

    return RGB(redAverage, greenAverage, blueAverage);
}
