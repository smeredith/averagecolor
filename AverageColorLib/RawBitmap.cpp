#include "stdafx.h"
#include <wincodec.h>
#include "RawBitmap.h"

using namespace Microsoft::WRL;

HRESULT RawBitmap::InitFromFile(PCWSTR pFilename)
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

    IF_FAIL_RETURN(pFrame->GetSize(&m_width, &m_height));

    const UINT colorCount = 3;

    // Make a buffer to hold the bytes of the decoded image.
    try
    {
        m_bitmap.resize(m_width * m_height * colorCount);
    }
    catch(std::bad_alloc&)
    {
        return E_OUTOFMEMORY;
    }

    // Decode the image into the buffer.
    IF_FAIL_RETURN(pFrame->CopyPixels(
                0, // entire bitmap
                m_width * colorCount, // stride
                m_bitmap.size() * colorCount, // buffer size
                m_bitmap.data()
                ));

    return S_OK;
}
