#include "stdafx.h"
#include "RawBitmap.h"
#include "AverageColor_ParallelInvokeReduce.h"

HRESULT AverageColor(PCWSTR filename, DWORD& averageColor)
{
    RawBitmap bitmap;
    IF_FAIL_RETURN(bitmap.InitFromFile(filename));

    averageColor = AverageColor_ParallelInvokeReduce(bitmap.cbegin(), bitmap.cend());

    return S_OK;
}
