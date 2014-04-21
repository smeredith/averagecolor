#include "stdafx.h"
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ppl.h>
#include <wincodec.h>

using namespace Microsoft::WRL;

HRESULT AverageColor(PCWSTR filename, DWORD& averageColor)
{
    VERIFY_PARAM(filename);

    ComPtr<IWICImagingFactory> pWICFactory;
    IF_FAIL_RETURN(CoCreateInstance(
                CLSID_WICImagingFactory,
                nullptr,
                CLSCTX_INPROC_SERVER,
                IID_PPV_ARGS(&pWICFactory)
                ));

    ComPtr<IWICBitmapDecoder> pDecoder;
    IF_FAIL_RETURN(pWICFactory->CreateDecoderFromFilename(
                filename,
                nullptr,                         // Do not prefer a particular vendor
                GENERIC_READ,
                WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
                &pDecoder
                ));

    ComPtr<IWICBitmapFrameDecode> pFrame;
    IF_FAIL_RETURN(pDecoder->GetFrame(0, &pFrame));

    // The only pixel format info we can get from the frame is a GUID.
    WICPixelFormatGUID pixelFormatGuid;
    IF_FAIL_RETURN(pFrame->GetPixelFormat(&pixelFormatGuid));

    // Only need for handle this format for now. Code below assumes this format.
    IF_FALSE_RETURN((pixelFormatGuid == GUID_WICPixelFormat24bppBGR), E_UNEXPECTED);

    const UINT colorCount = 3;
    const UINT bitsPerChannel = 8;

    UINT width;
    UINT height;
    IF_FAIL_RETURN(pFrame->GetSize(&width, &height));

    // Make a buffer to hold the bytes of the decoded image. This is a vector of 3-byte
    // arrays, where each byte in the array holds the RGB values for a single pixel. This
    // is so we can iterate through 1 pixel at a time instead of 1 byte at a time.
    typedef std::array<BYTE, colorCount> PixelColors;
    typedef std::vector<PixelColors> PixelColorVector;
    const UINT pixelCount = width * height;
    PixelColorVector buffer(pixelCount);

    // Decode the image into the buffer. The buffer appears as a single array of BYTES to
    // this function.
    IF_FAIL_RETURN(pFrame->CopyPixels(
                0, // entire bitmap
                width * colorCount, // stride
                pixelCount * colorCount, // buffer size
                reinterpret_cast<BYTE*>(buffer.data())
                ));

    // PixelColorSum is a type to hold three different sums: one for each color.
    typedef std::array<ULONGLONG, colorCount> PixelColorSum;
    const PixelColorSum colorSumZero = {0,0,0};

    // Want to process scanlines in parallel, so create a list of each scanline's begin
    // and end iterators. The color sum for that line will be stored in this vector as
    // well, as the third part of the tuple.
    typedef std::tuple<PixelColorVector::iterator, PixelColorVector::iterator, PixelColorSum> ScanLine;
    std::vector<ScanLine> scanLines(height);

    for (size_t l = 0; l < height; ++l)
    {
        PixelColorVector::iterator begin = buffer.begin() + (width * l);
        scanLines[l] = std::make_tuple(begin, begin + width, colorSumZero);
    }

    // Iterate through the scan lines in parallel.
    concurrency::parallel_for_each(scanLines.begin(), scanLines.end(),
        [](ScanLine& scanLine)
        {
            // Calculate the color sums for this line.
            PixelColorSum scanLineColorSum = { 0, 0, 0 };
            std::for_each(std::get<0>(scanLine), std::get<1>(scanLine),
                [&scanLineColorSum](PixelColors& pixelColors)
                {
                    for (size_t c = 0; c < pixelColors.size(); ++c)
                    {
                        scanLineColorSum[c] += pixelColors[c];
                    }
                });

            // Save it back into the scanline array. Note that multiple threads are
            // writing to the array, but each one is writing to a different pre-allocated
            // element, so it is thread safe.
            std::get<2>(scanLine) = scanLineColorSum;
        });

    // Sum the sums of each scanline to get the grand total.
    PixelColorSum grandTotal = std::accumulate(scanLines.begin(), scanLines.end(), colorSumZero,
        [](PixelColorSum colorSum, ScanLine& scanLine)
        {
            for (size_t c = 0; c < colorSum.size(); ++c)
            {
                colorSum[c] += std::get<2>(scanLine)[c];
            }
            return colorSum;
        });

    averageColor = 0;

    // Calculate the averages and create a single value representing the average color.
    for (size_t i = 0; i < colorCount; ++i)
    {
        averageColor += (0xff & (grandTotal[i] / pixelCount)) << (bitsPerChannel * i);
    }

    return S_OK;
}
