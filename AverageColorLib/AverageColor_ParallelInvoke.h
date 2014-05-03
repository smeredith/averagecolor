#pragma once

#include "RawBitmap.h"

DWORD AverageColor_ParallelInvoke(
    ColorIterator blueBegin, ColorIterator blueEnd,
    ColorIterator greenBegin, ColorIterator greenEnd,
    ColorIterator redBegin, ColorIterator redEnd);
