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

    BYTE blueAverage = std::accumulate(ColorIterator(begin), ColorIterator(end), 0ULL) / ((end - begin) / 3);
    BYTE greenAverage = std::accumulate(ColorIterator(begin+1), ColorIterator(end+1), 0ULL) / ((end - begin) / 3);
    BYTE redAverage = std::accumulate(ColorIterator(begin+2), ColorIterator(end+2), 0ULL) / ((end - begin) / 3);

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
