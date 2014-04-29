#include "stdafx.h"
#include <numeric>
#include "ColorCalculations.h"
#include "AverageColor_Serial.h"

PixelColorSums SumAverages(RawBitmap::PixelColorVector::iterator begin, RawBitmap::PixelColorVector::iterator end)
{
    PixelColorSums totals = {};
    std::for_each(begin, end,
        [&totals](RawBitmap::PixelColor pixelColor)
        {
            for (size_t c = 0; c < pixelColor.size(); ++c)
            {
                totals[c] += pixelColor[c];
            }
        });

    return totals;
}

unsigned long AverageColor_Serial(RawBitmap::PixelColorVector::iterator begin, RawBitmap::PixelColorVector::iterator end)
{
    return CalculateAverage(SumAverages(begin, end), end - begin);
}
