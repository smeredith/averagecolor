#include "stdafx.h"
#include <numeric>
#include "ColorCalculations.h"
#include "AverageColor_Serial.h"

unsigned long AverageColor_Serial(RawBitmap::PixelColorVector::iterator begin, RawBitmap::PixelColorVector::iterator end)
{
    return CalculateAverage(std::accumulate(begin, end, PixelColorSums(), AddPixelColorToSums), end - begin);
}
