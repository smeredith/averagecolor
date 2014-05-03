// AverageColorPerfTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <RawBitmap.h>
#include <AverageColor_Serial.h>
#include <AverageColor_Task.h>
#include <AverageColor_ParallelInvoke.h>
#include <AverageColor_ParallelReduce.h>
#include <AverageColor_ParallelInvokeReduce.h>

// Calls the provided work function and returns the number of milliseconds
// that it takes to call that function.
template <class Function>
__int64 time_call(Function&& f)
{
    __int64 begin = GetTickCount64();
    f();
    return GetTickCount64() - begin;
}

// Fuctor to initialze a vector of BYTES with the repeating pattern 0,1,2,0,1,2... when
// passed to std::generate().
class ColorGen
{
    public:
        BYTE operator()() { return m_total++ % 3; }

    private:
        UINT m_total = 0;
};


int _tmain(int argc, _TCHAR* argv[])
{
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    // Make a big bitmap.
    std::vector<BYTE> bitmap(300000000);

    // Initialize it with the pattern 0,1,2,0,1,2...
    ColorGen colorGen;
    std::generate(bitmap.begin(), bitmap.end(), colorGen);

    // Total times for each implementation.
    __int64 elapsed_Serial = 0;
    __int64 elapsed_Task = 0;
    __int64 elapsed_ParallelInvoke = 0;
    __int64 elapsed_ParallelReduce = 0;
    __int64 elapsed_ParallelInvokeReduce = 0;

    const size_t iterations = 10;

    for (size_t i = 0; i < iterations; ++i)
    {
        DWORD averageColor;
        __int64 elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_Serial(
                ColorIterator(bitmap.cbegin()), ColorIterator(bitmap.cend()),
                ColorIterator(bitmap.cbegin()+1), ColorIterator(bitmap.cend()+1),
                ColorIterator(bitmap.cbegin()+2), ColorIterator(bitmap.cend()+2));
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_Serial(): " << elapsed << L" ms" << std::endl;
        elapsed_Serial += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_Task(
                ColorIterator(bitmap.cbegin()), ColorIterator(bitmap.cend()),
                ColorIterator(bitmap.cbegin()+1), ColorIterator(bitmap.cend()+1),
                ColorIterator(bitmap.cbegin()+2), ColorIterator(bitmap.cend()+2),
                0);
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_Task(): " << elapsed << L" ms" << std::endl;
        elapsed_Task += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_ParallelInvoke(
                ColorIterator(bitmap.cbegin()), ColorIterator(bitmap.cend()),
                ColorIterator(bitmap.cbegin()+1), ColorIterator(bitmap.cend()+1),
                ColorIterator(bitmap.cbegin()+2), ColorIterator(bitmap.cend()+2));
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_ParallelInvoke(): " << elapsed << L" ms" << std::endl;
        elapsed_ParallelInvoke += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_ParallelReduce(
                ColorIterator(bitmap.cbegin()), ColorIterator(bitmap.cend()),
                ColorIterator(bitmap.cbegin()+1), ColorIterator(bitmap.cend()+1),
                ColorIterator(bitmap.cbegin()+2), ColorIterator(bitmap.cend()+2));
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_ParallelReduce(): " << elapsed << L" ms" << std::endl;
        elapsed_ParallelReduce += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_ParallelInvokeReduce(
                ColorIterator(bitmap.cbegin()), ColorIterator(bitmap.cend()),
                ColorIterator(bitmap.cbegin()+1), ColorIterator(bitmap.cend()+1),
                ColorIterator(bitmap.cbegin()+2), ColorIterator(bitmap.cend()+2));
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_ParallelInvokeReduce(): " << elapsed << L" ms" << std::endl;
        elapsed_ParallelInvokeReduce += elapsed;
    }

    std::wcout << L"Average AverageColor_Serial(): " << elapsed_Serial / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_Task(): " << elapsed_Task / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_ParallelInvoke(): " << elapsed_ParallelInvoke / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_ParallelReduce(): " << elapsed_ParallelReduce / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_ParallelInvokeReduce(): " << elapsed_ParallelInvokeReduce / iterations << L" ms" << std::endl;

    CoUninitialize();
    return 0;
}
