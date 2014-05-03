#include "stdafx.h"
#include "RawBitmap.h"
#include "AverageColor_Task.h"

HRESULT AverageColor(PCWSTR filename, DWORD& averageColor)
{
    RawBitmap bitmap;
    IF_FAIL_RETURN(bitmap.InitFromFile(filename));

    averageColor = AverageColor_Task(
        bitmap.cbegin(0), bitmap.cend(0),
        bitmap.cbegin(1), bitmap.cend(1),
        bitmap.cbegin(2), bitmap.cend(2),
        0);

    return S_OK;
}
