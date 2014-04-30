#pragma once

#include "RawBitmap.h"

unsigned long AverageColor_ParallelTransform(
        RawBitmap::PixelColorVector::iterator begin,
        RawBitmap::PixelColorVector::iterator end,
        unsigned int width,
        unsigned int height);
