// AverageColorConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <AverageColor.h>

// Calls the provided work function and returns the number of milliseconds  
// that it takes to call that function. 
template <class Function>
__int64 time_call(Function&& f)
{
   __int64 begin = GetTickCount();
   f();
   return GetTickCount() - begin;
}

int _tmain(int argc, _TCHAR* argv[])
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    HRESULT hr;
    __int64 elapsed = time_call(
        [&hr]
        {
            DWORD averageColor;
            hr = AverageColor(L"..\\TestFiles\\5000x5000_ffffff.jpg", averageColor);
        });

    if (SUCCEEDED(hr))
    {
        std::wcout << L"Elapsed time: " << elapsed << L" ms" << std::endl;
    }
    else
    {
        std::wcout << L"Failed: " << hr << std::endl;
    }

    CoUninitialize();
    return 0;
}

