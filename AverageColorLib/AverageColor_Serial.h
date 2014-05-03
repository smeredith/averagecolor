#pragma once

#include "RawBitmap.h"
#include "ColorCalculations.h"

DWORD AverageColor_Serial(
    const ColorIterator& blueBegin, const ColorIterator& blueEnd,
    const ColorIterator& greenBegin, const ColorIterator& greenEnd,
    const ColorIterator& redBegin, const ColorIterator& redEnd);
