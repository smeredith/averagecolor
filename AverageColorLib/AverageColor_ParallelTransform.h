#pragma once

#include "RawBitmap.h"

DWORD AverageColor_ParallelTransform(
        RawBitmap::PixelColorVector::iterator begin,
        RawBitmap::PixelColorVector::iterator end,
        UINT width,
        UINT height);
