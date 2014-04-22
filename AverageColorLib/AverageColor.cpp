#include "stdafx.h"
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

    // A GUID is not very helpful. Need to jump through some more hoops to get actual values.
    ComPtr<IWICComponentInfo> pComponentInfo;
    IF_FAIL_RETURN(pWICFactory->CreateComponentInfo(pixelFormatGuid, &pComponentInfo));

    ComPtr<IWICPixelFormatInfo> pPixelFormatInfo;
    IF_FAIL_RETURN(pComponentInfo.As(&pPixelFormatInfo));

    UINT bitsPerPixel;  // Total number of bits for all color channels.
    IF_FAIL_RETURN(pPixelFormatInfo->GetBitsPerPixel(&bitsPerPixel));

    // The code below assumes multiples of 8.
    IF_FALSE_RETURN(((bitsPerPixel % 8) == 0), E_INVALIDARG);

    UINT colorChannels;
    IF_FAIL_RETURN(pPixelFormatInfo->GetChannelCount(&colorChannels));

    UINT bitsPerChannel = bitsPerPixel / colorChannels;

    UINT width;
    UINT height;
    IF_FAIL_RETURN(pFrame->GetSize(&width, &height));

    // Make a buffer to hold the decoded image.
    UINT pixels = width * height;
    std::vector<BYTE> buffer(pixels * colorChannels);

    // Decode the image into the buffer.
    IF_FAIL_RETURN(pFrame->CopyPixels(
                0, // entire bitmap
                width * colorChannels, // stride
                buffer.size(), 
                buffer.data()
                ));

    // Store the totals we need to calculate an average, one for each channel.
    std::vector<ULONGLONG> totals(colorChannels, 0);

    // Iterate through every color channel of every pixel and add to the total.
    for (size_t i = 0; i < buffer.size();)
    {
        for (size_t c = 0; c < colorChannels; ++c)
        {
            totals[c] += buffer[i++];
        }
    }

    averageColor = 0;

    // Calculate the averages and create a single value representing the average color.
    for (size_t i = 0; i < totals.size(); ++i)
    {
        averageColor += (totals[i] / pixels) << (8 * i);
    }

    return S_OK;
}
