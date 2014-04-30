#pragma once

#include "RawBitmap.h"

DWORD AverageColor_ParallelForEach(
        RawBitmap::PixelColorVector::iterator begin,
        RawBitmap::PixelColorVector::iterator end,
        UINT width,
        UINT height);
