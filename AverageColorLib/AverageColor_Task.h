#pragma once

#include "RawBitmap.h"
#include "ColorCalculations.h"

// Chunksize is the approximate size of one chunk of work for a task, in the number of
// pixels to process. If 0, the number is set to a reasonable value.
unsigned long AverageColor_Task(
        RawBitmap::PixelColorVector::iterator begin,
        RawBitmap::PixelColorVector::iterator end,
        unsigned int chunkSize);
