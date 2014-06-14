// AverageColorPerfTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>
#include <AverageColor_Serial.h>
#include <AverageColor_Task.h>
#include <AverageColor_ParallelInvoke.h>
#include <AverageColor_ParallelReduce.h>
#include <AverageColor_ParallelInvokeReduce.h>
#include <AverageColor_While.h>
#include <AverageColor_StdThread.h>
#include <AverageColor_StdThreadRecursive.h>
#include <AverageColor_StdAsync.h>
#include <AverageColor_ParallelAccumulate.h>

// Calls the provided work function and returns the number of milliseconds
// that it takes to call that function.
template <class Function>
long long time_call(Function&& f)
{
    auto start = std::chrono::steady_clock::now();

    f();

    auto diff = std::chrono::steady_clock::now() - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

    return ms.count();
}

// Functor to initialze a vector of BYTES with the repeating pattern 0,1,2,0,1,2... when
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
    std::vector<BYTE> pixels(300000000);

    // Initialize it with the pattern 0,1,2,0,1,2...
    ColorGen colorGen;
    std::generate(pixels.begin(), pixels.end(), colorGen);

    // Total times for each implementation.
    long long elapsed_While = 0;
    long long elapsed_Serial = 0;
    long long elapsed_Task = 0;
    long long elapsed_ParallelInvoke = 0;
    long long elapsed_ParallelReduce = 0;
    long long elapsed_ParallelInvokeReduce = 0;
    long long elapsed_StdThread = 0;
    long long elapsed_StdThreadRecursive = 0;
    long long elapsed_StdAsync = 0;
    long long elapsed_ParallelAccumulate = 0;

    const size_t iterations = 10;

    for (size_t i = 0; i < iterations; ++i)
    {
        DWORD averageColor;
        long long elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_While(pixels.cbegin(), pixels.cend());
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_While(): " << elapsed << L" ms" << std::endl;
        elapsed_While += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_Serial(pixels.cbegin(), pixels.cend());
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_Serial(): " << elapsed << L" ms" << std::endl;
        elapsed_Serial += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_Task(pixels.cbegin(), pixels.cend());
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_Task(): " << elapsed << L" ms" << std::endl;
        elapsed_Task += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_ParallelInvoke(pixels.cbegin(), pixels.cend());
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_ParallelInvoke(): " << elapsed << L" ms" << std::endl;
        elapsed_ParallelInvoke += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_ParallelReduce(pixels.cbegin(), pixels.cend());
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_ParallelReduce(): " << elapsed << L" ms" << std::endl;
        elapsed_ParallelReduce += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_ParallelInvokeReduce(pixels.cbegin(), pixels.cend());
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_ParallelInvokeReduce(): " << elapsed << L" ms" << std::endl;
        elapsed_ParallelInvokeReduce += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_StdThread(pixels.cbegin(), pixels.cend());
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_StdThread(): " << elapsed << L" ms" << std::endl;
        elapsed_StdThread += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_StdThreadRecursive(pixels.cbegin(), pixels.cend());
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_StdThreadRecursive(): " << elapsed << L" ms" << std::endl;
        elapsed_StdThreadRecursive += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_StdAsync(pixels.cbegin(), pixels.cend());
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_StdAsync(): " << elapsed << L" ms" << std::endl;
        elapsed_StdAsync += elapsed;

        elapsed = time_call(
            [&]
        {
            averageColor = AverageColor_ParallelAccumulate(pixels.cbegin(), pixels.cend());
        });

        std::wcout << averageColor << L" Elapsed time AverageColor_ParallelAccumulate(): " << elapsed << L" ms" << std::endl;
        elapsed_ParallelAccumulate += elapsed;


    }

    std::wcout << L"Average AverageColor_While(): " << elapsed_While / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_Serial(): " << elapsed_Serial / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_Task(): " << elapsed_Task / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_ParallelInvoke(): " << elapsed_ParallelInvoke / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_ParallelReduce(): " << elapsed_ParallelReduce / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_ParallelInvokeReduce(): " << elapsed_ParallelInvokeReduce / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_StdThread(): " << elapsed_StdThread / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_StdThreadRecursive(): " << elapsed_StdThreadRecursive / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_StdAsync(): " << elapsed_StdAsync / iterations << L" ms" << std::endl;
    std::wcout << L"Average AverageColor_ParallelAccumulate(): " << elapsed_ParallelAccumulate / iterations << L" ms" << std::endl;

    CoUninitialize();
    return 0;
}
