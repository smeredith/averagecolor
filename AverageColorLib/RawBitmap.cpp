#include "stdafx.h"
#include "RawBitmap.h"
#include <wincodec.h>

using namespace Microsoft::WRL;

HRESULT RawBitmap::InitFromFile(const wchar_t* pFilename)
{
    VERIFY_PARAM(pFilename);

    ComPtr<IWICImagingFactory> pWICFactory;
    IF_FAIL_RETURN(CoCreateInstance(
                CLSID_WICImagingFactory,
                nullptr,
                CLSCTX_INPROC_SERVER,
                IID_PPV_ARGS(&pWICFactory)
                ));

    ComPtr<IWICBitmapDecoder> pDecoder;
    IF_FAIL_RETURN(pWICFactory->CreateDecoderFromFilename(
                pFilename,
                nullptr,                         // Do not prefer a particular vendor
                GENERIC_READ,
                WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
                &pDecoder
                ));

    ComPtr<IWICBitmapFrameDecode> pFrame;
    IF_FAIL_RETURN(pDecoder->GetFrame(0, &pFrame));

    // The only pixel format info obtainable from the frame is a GUID.
    WICPixelFormatGUID pixelFormatGuid;
    IF_FAIL_RETURN(pFrame->GetPixelFormat(&pixelFormatGuid));

    // Only need for handle this format for now. Code below assumes this format.
    IF_FALSE_RETURN((pixelFormatGuid == GUID_WICPixelFormat24bppBGR), E_UNEXPECTED);

    UINT width;
    UINT height;
    IF_FAIL_RETURN(pFrame->GetSize(&width, &height));

    // Make a buffer to hold the bytes of the decoded image. This is a vector of 3-byte
    // arrays, where each byte in the array holds the RGB values for a single pixel. This
    // is so it is possible to iterate through 1 pixel at a time instead of 1 byte at a time.
    m_bitmap.resize(width * height);

    const UINT colorCount = sizeof(PixelColorVector::value_type);

    // Decode the image into the buffer. The buffer appears as a single array of BYTES to
    // this function.
    IF_FAIL_RETURN(pFrame->CopyPixels(
                0, // entire bitmap
                width * colorCount, // stride
                m_bitmap.size() * colorCount, // buffer size
                reinterpret_cast<BYTE*>(m_bitmap.data())
                ));

    return S_OK;
}
