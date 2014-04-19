#include "stdafx.h"
#include <array>
#include <vector>
#include <algorithm>
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

    // Make a buffer to hold the decoded image.
    typedef std::array<BYTE, colorCount> PixelColors;
    UINT pixelCount = width * height;
    std::vector<PixelColors> buffer(pixelCount);

    // Decode the image into the buffer.
    IF_FAIL_RETURN(pFrame->CopyPixels(
                0, // entire bitmap
                width * colorCount, // stride
                pixelCount * colorCount, // buffer size
                reinterpret_cast<BYTE*>(buffer.data())
                ));

    // Store the totals we need to calculate an average, one for each channel.
    std::array<ULONGLONG, colorCount> totals = {0};

    // To make parallel, create a vector of color values for each pixel, and a vector of those for each scan line, and a vector or scan lines.
    // Then the outer loop is scan lines, and the inner loop is accumulating pixel colors.
    // Iterate through every color channel of every pixel and add to the total.
    std::for_each(buffer.begin(), buffer.end(), [&totals, colorCount](PixelColors& colors)
            {
                for (size_t c = 0; c < colorCount; ++c)
                {
                    totals[c] += colors[c];
                }
            });

    averageColor = 0;

    // Calculate the averages and create a single value representing the average color.
    for (size_t i = 0; i < totals.size(); ++i)
    {
        averageColor += (totals[i] / pixelCount) << (8 * i);
    }

    return S_OK;
}
