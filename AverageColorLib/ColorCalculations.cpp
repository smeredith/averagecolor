#include "stdafx.h"
#include "ColorCalculations.h"

// Return the average color represented as a PixelColorSums packed into a single unsigned long.
unsigned long CalculateAverage(const PixelColorSums& totals, unsigned int pixelCount)
{
    unsigned long averageColor = 0;

    // Calculate the averages and create a single value representing the average color.
    for (size_t i = 0; i < totals.size(); ++i)
    {
        averageColor += (0xff & (totals[i] / pixelCount)) << (8 * i);
    }

    return averageColor;
}

