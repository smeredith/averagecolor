#include "stdafx.h"
#include <numeric>
#include "EveryNIterator.h"
#include "AverageColor_Serial.h"

DWORD AverageColor_Serial(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end)
{
    // An iterator to iterator over all bytes of one color.
    typedef EveryNIterator<std::vector<BYTE>::const_iterator, 3> ColorIterator;

    const size_t pixelCount = (end - begin) / 3;

#pragma warning(push)
#pragma warning(disable : 4244) // Guaranteed to fit into a byte because the sum accumulated bytes.

    const BYTE blueAverage = std::accumulate(ColorIterator(begin), ColorIterator(end), 0ULL) / pixelCount;

    // Read one BYTE less than we should so we don't set the ColorIterator past the end of
    // the real iterator, but add in the last one by initializing accumulate() with it.
    const BYTE greenAverage = std::accumulate(ColorIterator(begin+1), ColorIterator(end-2), static_cast<ULONGLONG>(*(end-2))) / pixelCount;
    const BYTE redAverage = std::accumulate(ColorIterator(begin+2), ColorIterator(end-1), static_cast<ULONGLONG>(*(end-1))) / pixelCount;

#pragma warning(pop)

    return RGB(redAverage, greenAverage, blueAverage);
}
