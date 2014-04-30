#include "stdafx.h"
#include <numeric>
#include <ppl.h>
#include "ColorCalculations.h"
#include "AverageColor_Serial.h"
#include "AverageColor_ParallelTransform.h"

DWORD AverageColor_ParallelTransform(
        RawBitmap::PixelColorVector::iterator begin,
        RawBitmap::PixelColorVector::iterator end,
        UINT width,
        UINT height)
{
    // Want to process scanlines in parallel, so create a list of each scanline's begin
    // and end iterators.
    typedef std::tuple<RawBitmap::PixelColorVector::iterator, RawBitmap::PixelColorVector::iterator> ScanLine;
    std::vector<ScanLine> scanLines(height);

    // The sums will be stored in this output vector, with one scanline sum per element.
    std::vector<PixelColorSums> pixelColorSums(height);

    for (size_t y = 0; y < height; ++y)
    {
        RawBitmap::PixelColorVector::iterator lineBegin = begin + (width * y);
        scanLines[y] = std::make_tuple(lineBegin, lineBegin + width);
    }

    // Iterate through the scanlines in parallel.
    concurrency::parallel_transform(std::begin(scanLines), std::end(scanLines), std::begin(pixelColorSums),
        [](ScanLine& scanLine)
        {
            // Calculate the color sums for this line.
            PixelColorSums scanLineColorSum = {};
            std::for_each(std::get<0>(scanLine), std::get<1>(scanLine),
                [&scanLineColorSum](RawBitmap::PixelColor& pixelColor)
                {
                    for (size_t c = 0; c < pixelColor.size(); ++c)
                    {
                        scanLineColorSum[c] += pixelColor[c];
                    }
                });

            // Save it back into the scanline array. Note that multiple threads are
            // writing to the array, but each one is writing to a different pre-allocated
            // element, so it is thread safe.
            return scanLineColorSum;
        });

    // Sum the sum of each scanline.
    PixelColorSums totals = concurrency::parallel_reduce(std::begin(pixelColorSums), std::end(pixelColorSums), PixelColorSums(),
        [](PixelColorSums colorSum1, PixelColorSums& colorSum2)
        {
            for (size_t c = 0; c < colorSum1.size(); ++c)
            {
                colorSum1[c] += colorSum2[c];
            }
            return colorSum1;
        });

    return CalculateAverage(totals, end - begin);
}
