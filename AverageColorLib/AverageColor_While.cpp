#include "stdafx.h"
#include <numeric>
#include "AverageColor_While.h"

DWORD AverageColor_While(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end)
{
    ULONGLONG blueSum = 0;
    ULONGLONG greenSum = 0;
    ULONGLONG redSum = 0;

    auto iter = begin;
    while (iter != end)
    {
        blueSum += *iter++;
        greenSum += *iter++;
        redSum += *iter++;
    }

#pragma warning(push)
#pragma warning(disable : 4244) // Guaranteed to fit into a byte because the sum accumulated bytes.

    BYTE blueAverage = blueSum / ((end - begin) / 3);
    BYTE greenAverage = greenSum / ((end - begin) / 3);
    BYTE redAverage = redSum / ((end - begin) / 3);

#pragma warning(pop)

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
