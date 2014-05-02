#include "stdafx.h"
#include "RawBitmap.h"
#include "AverageColor_Task.h"

HRESULT AverageColor(PCWSTR filename, DWORD& averageColor)
{
    RawBitmap bitmap;
    IF_FAIL_RETURN(bitmap.InitFromFile(filename));

    averageColor = AverageColor_Task(
        bitmap.begin(0), bitmap.end(0),
        bitmap.begin(1), bitmap.end(1),
        bitmap.begin(2), bitmap.end(2),
        0);

    return S_OK;
}
