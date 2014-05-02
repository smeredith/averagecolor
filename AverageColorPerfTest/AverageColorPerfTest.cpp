// AverageColorPerfTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <RawBitmap.h>
#include <AverageColor_Serial.h>
#include <AverageColor_Task.h>

// Calls the provided work function and returns the number of milliseconds  
// that it takes to call that function. 
template <class Function>
__int64 time_call(Function&& f)
{
    __int64 begin = GetTickCount64();
    f();
    return GetTickCount64() - begin;
}

int _tmain(int argc, _TCHAR* argv[])
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    RawBitmap bitmap;
    HRESULT hr = bitmap.InitFromFile(L"..\\TestFiles\\10000x10000_8080ff.jpg");

    if (FAILED(hr))
    {
        std::wcout << L"Failed: " << hr << std::endl;
        return -1;
    }

    DWORD averageColor;
    __int64 elapsed_Serial = 0;
    __int64 elapsed_ParallelFor = 0;
    __int64 elapsed_Task = 0;
    __int64 elapsed_ParallelTransform = 0;

    size_t iterations = 10;

    for (size_t i = 0; i < iterations; ++i)
    {
        __int64 elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_Serial(
                bitmap.begin(0), bitmap.end(0),
                bitmap.begin(1), bitmap.end(1),
                bitmap.begin(2), bitmap.end(2));
        });

        std::wcout << L"Elapsed time AverageColor_Serial(): " << elapsed << L" ms" << std::endl;
        elapsed_Serial += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_Task(
                bitmap.begin(0), bitmap.end(0),
                bitmap.begin(1), bitmap.end(1),
                bitmap.begin(2), bitmap.end(2),
                0);
        });

        std::wcout << L"Elapsed time AverageColor_Task(): " << elapsed << L" ms" << std::endl;
        elapsed_Task += elapsed;

    }

    std::wcout << L"Average AverageColor_Serial(): " << elapsed_Serial / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_Task(): " << elapsed_Task/ iterations << L" ms" << std::endl;

    CoUninitialize();
    return 0;
}

