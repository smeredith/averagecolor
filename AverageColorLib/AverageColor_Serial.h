#pragma once

#include "RawBitmap.h"
#include "ColorCalculations.h"

PixelColorSums SumAverages(RawBitmap::PixelColorVector::iterator begin, RawBitmap::PixelColorVector::iterator end);
DWORD AverageColor_Serial(RawBitmap::PixelColorVector::iterator begin, RawBitmap::PixelColorVector::iterator end);
