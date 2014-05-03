#pragma once

#include "RawBitmap.h"

DWORD AverageColor_ParallelInvokeReduce(
    const ColorIterator& blueBegin, const ColorIterator& blueEnd,
    const ColorIterator& greenBegin, const ColorIterator& greenEnd,
    const ColorIterator& redBegin, const ColorIterator& redEnd);
