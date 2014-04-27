#include "stdafx.h"
#include <numeric>
#include <ppl.h>
#include "ColorCalculations.h"
#include "AverageColor_Serial.h"

unsigned long AverageColor_ParallelForEach(
        RawBitmap::PixelColorVector::iterator begin,
        RawBitmap::PixelColorVector::iterator end,
        unsigned int width,
        unsigned int height)
{
    // Want to process scanlines in parallel, so create a list of each scanline's begin
    // and end iterators. The color sums for that line will be stored in this vector as
    // well, as the third part of the tuple.
    typedef std::tuple<RawBitmap::PixelColorVector::iterator, RawBitmap::PixelColorVector::iterator, PixelColorSums> ScanLine;
    std::vector<ScanLine> scanLines(height);

    for (size_t y = 0; y < height; ++y)
    {
        RawBitmap::PixelColorVector::iterator lineBegin = begin + (width * y);
        scanLines[y] = std::make_tuple(lineBegin, lineBegin + width, PixelColorSums());
    }

    // Iterate through the scanlines in parallel.
    concurrency::parallel_for_each(scanLines.begin(), scanLines.end(),
        [](ScanLine& scanLine)
        {
            // Calculate the color sums for this line.  Save it back into the scanline
            // array. Note that multiple threads are writing to the array but each one is
            // writing to a different pre-allocated element so it is thread safe.
            std::get<2>(scanLine) = std::accumulate(
                std::get<0>(scanLine),
                std::get<1>(scanLine),
                PixelColorSums(),
                AddPixelColorToSums);
        });

    // Sum the sum of each scanline.
    PixelColorSums totals = std::accumulate(scanLines.begin(), scanLines.end(), PixelColorSums(),
        [](PixelColorSums colorSum, ScanLine& scanLine)
        {
            for (size_t c = 0; c < colorSum.size(); ++c)
            {
                colorSum[c] += std::get<2>(scanLine)[c];
            }
            return colorSum;
        });

    return CalculateAverage(totals, end - begin);
}
