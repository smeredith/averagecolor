#pragma once

#include "RawBitmap.h"
#include "ColorCalculations.h"

DWORD AverageColor_Serial(
    ColorIterator blueBegin, ColorIterator blueEnd,
    ColorIterator greenBegin, ColorIterator greenEnd,
    ColorIterator redBegin, ColorIterator redEnd);
