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

    BYTE blueAverage = std::accumulate(ColorIterator(begin), ColorIterator(end), 0ULL) / pixelCount;
    BYTE greenAverage = std::accumulate(ColorIterator(begin+1), ColorIterator(end+1), 0ULL) / pixelCount;
    BYTE redAverage = std::accumulate(ColorIterator(begin+2), ColorIterator(end+2), 0ULL) / pixelCount;

#pragma warning(pop)

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
