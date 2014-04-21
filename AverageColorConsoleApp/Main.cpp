// AverageColorConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <AverageColor.h>

int _tmain(int argc, _TCHAR* argv[])
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    DWORD averageColor;

    HRESULT hr = AverageColor(L"..\\TestFiles\\10000x10000_8080ff.jpg", averageColor);

    if (SUCCEEDED(hr))
    {
        std::wcout << L"Average color: " << averageColor << std::endl;
    }
    else
    {
        std::wcout << L"Failed: " << hr << std::endl;
    }

    CoUninitialize();
    return 0;
}
