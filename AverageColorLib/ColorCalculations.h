#pragma once

#include <array>
#include "RawBitmap.h"

typedef std::array<unsigned long long, sizeof(RawBitmap::PixelColor)> PixelColorSums;

PixelColorSums AddPixelColorToSums(PixelColorSums pixelColorSums, const RawBitmap::PixelColor& pixelColor);
unsigned long CalculateAverage(const PixelColorSums& totals, unsigned int pixelCount);

inline PixelColorSums operator+(PixelColorSums lhs, const PixelColorSums& rhs)
{
    for (size_t c = 0; c < rhs.size(); ++c)
    {
        lhs[c] += rhs[c];
    }

    return lhs;
}
