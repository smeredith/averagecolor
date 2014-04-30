#pragma once

#include <array>
#include "RawBitmap.h"

typedef std::array<ULONGLONG, sizeof(RawBitmap::PixelColor)> PixelColorSums;

PixelColorSums AddPixelColorToSums(PixelColorSums pixelColorSums, const RawBitmap::PixelColor& pixelColor);
DWORD CalculateAverage(const PixelColorSums& totals, UINT pixelCount);

inline PixelColorSums operator+(PixelColorSums lhs, const PixelColorSums& rhs)
{
    for (size_t c = 0; c < rhs.size(); ++c)
    {
        lhs[c] += rhs[c];
    }

    return lhs;
}