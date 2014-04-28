#include "stdafx.h"
#include "AverageColor_Serial.h"
#include "AverageColor_ParallelForEach.h"

HRESULT AverageColor(const wchar_t* filename, unsigned long& averageColor)
{
    RawBitmap bitmap;
    IF_FAIL_RETURN(bitmap.InitFromFile(filename));

    //averageColor = AverageColor_ParallelForEach(bitmap.begin(), bitmap.end(), bitmap.Width(), bitmap.Height());
    averageColor = AverageColor_Serial(bitmap.begin(), bitmap.end());

    return S_OK;
}
