#include "stdafx.h"
#include "AverageColor_Serial.h"

unsigned long AverageColor_Serial(RawBitmap::PixelColorVector::iterator begin, RawBitmap::PixelColorVector::iterator end)
{
    // Store the totals we need to calculate an average, one for each channel.
    std::array<ULONGLONG, sizeof(RawBitmap::PixelColorVector::iterator::value_type)> totals = {};

    // Iterate through every color channel of every pixel and add to the total.
    std::for_each(begin, end,
        [&totals](RawBitmap::PixelColorVector::iterator::value_type pixelColors)
        {
            for (size_t c = 0; c < pixelColors.size(); ++c)
            {
                totals[c] += pixelColors[c];
            }
        });

    unsigned long averageColor = 0;

    // Calculate the averages and create a single value representing the average color.
    for (size_t i = 0; i < totals.size(); ++i)
    {
        averageColor += (0xff & (totals[i] / (end - begin))) << (8 * i);
    }

    return averageColor;
}
