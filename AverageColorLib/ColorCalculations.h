#pragma once

#include <array>
#include "RawBitmap.h"

typedef std::array<ULONGLONG, 3> PixelColorSums;

DWORD CalculateAverage(const PixelColorSums& totals, UINT pixelCount);
