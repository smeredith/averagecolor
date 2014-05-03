#include "stdafx.h"
#include "RawBitmap.h"
#include "AverageColor_Serial.h"

HRESULT AverageColor(PCWSTR filename, DWORD& averageColor)
{
    RawBitmap bitmap;
    IF_FAIL_RETURN(bitmap.InitFromFile(filename));

    averageColor = AverageColor_Serial(bitmap.cbegin(), bitmap.cend());

    return S_OK;
}
