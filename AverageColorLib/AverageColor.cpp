#include "stdafx.h"
#include "AverageColor_ParallelTransform.h"

HRESULT AverageColor(PCWSTR filename, DWORD& averageColor)
{
    RawBitmap bitmap;
    IF_FAIL_RETURN(bitmap.InitFromFile(filename));

    // This is the fastest parallel implementation.
    averageColor = AverageColor_ParallelTransform(bitmap.begin(), bitmap.end(), bitmap.Width(), bitmap.Height());

    return S_OK;
}
