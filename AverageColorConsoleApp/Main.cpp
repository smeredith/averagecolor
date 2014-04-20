// AverageColorConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <AverageColor.h>

int _tmain(int argc, _TCHAR* argv[])
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    DWORD averageColor;
    ULONGLONG elapsedTime;
    HRESULT hr = AverageColorSerial(L"..\\TestFiles\\10000x10000_8080ff.jpg", averageColor, &elapsedTime);

    if (SUCCEEDED(hr))
    {
        // 450 ms
        std::wcout << L"Elapsed time serial: " << elapsedTime << L" ms" << std::endl;
    }
    else
    {
        std::wcout << L"Failed: " << hr << std::endl;
    }

    hr = AverageColor(L"..\\TestFiles\\10000x10000_8080ff.jpg", averageColor, &elapsedTime);

    if (SUCCEEDED(hr))
    {
        // 125 ms
        std::wcout << L"Elapsed time parallel: " << elapsedTime << L" ms" << std::endl;
    }
    else
    {
        std::wcout << L"Failed: " << hr << std::endl;
    }

    CoUninitialize();
    return 0;
}

