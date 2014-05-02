#include "stdafx.h"
#include <numeric>
#include <ppl.h>
#include "ColorCalculations.h"
#include "AverageColor_Serial.h"

DWORD AverageColor_Serial(
    ColorIterator blueBegin, ColorIterator blueEnd,
    ColorIterator greenBegin, ColorIterator greenEnd,
    ColorIterator redBegin, ColorIterator redEnd)
{
    BYTE blueAverage = std::accumulate(blueBegin, blueEnd, 0ULL) / (blueEnd - blueBegin);
    BYTE greenAverage = std::accumulate(greenBegin, greenEnd, 0ULL) / (greenEnd - greenBegin);
    BYTE redAverage = std::accumulate(redBegin, redEnd, 0ULL) / (redEnd - redBegin);

    return (redAverage << 16) | (greenAverage << 8) | blueAverage;
}
