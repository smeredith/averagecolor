#pragma once

#include "RawBitmap.h"
#include "ColorCalculations.h"

// Chunksize is the approximate size of one chunk of work for a task, in the number of
// pixels to process. If 0, the number is set to a reasonable value.
DWORD AverageColor_Task(
    ColorIterator blueBegin, ColorIterator blueEnd,
    ColorIterator greenBegin, ColorIterator greenEnd,
    ColorIterator redBegin, ColorIterator redEnd,
    UINT chunkSize);
