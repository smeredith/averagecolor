#pragma once

#include "RawBitmap.h"
#include "ColorCalculations.h"

unsigned long AverageColor_Task(
        RawBitmap::PixelColorVector::iterator begin,
        RawBitmap::PixelColorVector::iterator end,
        unsigned int chunkSize);
