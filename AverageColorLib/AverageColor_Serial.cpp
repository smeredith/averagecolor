#include "stdafx.h"
#include <numeric>
#include "ColorCalculations.h"
#include "AverageColor_Serial.h"

unsigned long AverageColor_Serial(RawBitmap::PixelColorVector::iterator begin, RawBitmap::PixelColorVector::iterator end)
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

    return CalculateAverage(totals, end - begin);
}
