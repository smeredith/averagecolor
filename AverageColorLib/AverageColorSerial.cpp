#include "stdafx.h"
#include <array>
#include <vector>
#include <algorithm>
#include <numeric>
#include <ppl.h>
#include <wincodec.h>

using namespace Microsoft::WRL;

HRESULT AverageColorSerial(PCWSTR filename, DWORD& averageColor, ULONGLONG* pElapsedTime)
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

    const UINT colorChannels = 3;
    const UINT bitsPerChannel = 8;

    UINT width;
    UINT height;
    IF_FAIL_RETURN(pFrame->GetSize(&width, &height));

    // Make a buffer to hold the decoded image.
    UINT pixelCount = width * height;
    std::vector<BYTE> buffer(pixelCount * colorChannels);

    // Decode the image into the buffer.
    IF_FAIL_RETURN(pFrame->CopyPixels(
                0, // entire bitmap
                width * colorChannels, // stride
                buffer.size(), 
                buffer.data()
                ));

    ULONGLONG beginTime = GetTickCount64();

    // Store the totals we need to calculate an average, one for each channel.
    std::array<ULONGLONG, colorChannels> totals = {0};

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
        averageColor += (0xff & (totals[i] / pixelCount)) << (8 * i);
    }

    if (pElapsedTime)
    {
        *pElapsedTime = GetTickCount64() - beginTime;
    }

    return S_OK;
}
