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

    ULONGLONG blueAverage = blueSum / ((end - begin) / 3);
    ULONGLONG greenAverage = greenSum / ((end - begin) / 3);
    ULONGLONG redAverage = redSum / ((end - begin) / 3);

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
