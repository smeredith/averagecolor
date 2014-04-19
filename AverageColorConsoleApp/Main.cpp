// AverageColorConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <AverageColor.h>


int _tmain(int argc, _TCHAR* argv[])
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    DWORD averageColor;
    if (FAILED(AverageColor(L"..\\TestFiles\\5000x5000_ffffff.jpg", averageColor)))
    {
        return -1;
    }

    CoUninitialize();
	return 0;
}

