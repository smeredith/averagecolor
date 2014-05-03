#pragma once

#include "RawBitmap.h"
#include "ColorCalculations.h"

// Chunksize is the approximate size of one chunk of work for a task, in the number of
// pixels to process. If 0, the number is set to a reasonable value.
DWORD AverageColor_Task(
    const ColorIterator& blueBegin, const ColorIterator& blueEnd,
    const ColorIterator& greenBegin, const ColorIterator& greenEnd,
    const ColorIterator& redBegin, const ColorIterator& redEnd,
    UINT chunkSize);
