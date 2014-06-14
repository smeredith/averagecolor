#include "stdafx.h"
#include "CppUnitTest.h"
#include <array>
#include <vector>
#include <algorithm>
#include <Parallel_Accumulate.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestAverageColorLib
{
    TEST_CLASS(TestParallelAccumulate)
    {

    public:
        TEST_METHOD(ParallelAccumulate_LengthGreaterThanNumberOfThreads_ShouldAccumulate)
        {
            size_t numThreads = std::thread::hardware_concurrency();
            std::vector<UINT> input(numThreads + 1);

            std::iota(input.begin(), input.end(), 0);

            UINT expected = std::accumulate(input.begin(), input.end(), 1U);
            UINT actual = parallel_accumulate(input.begin(), input.end(), 1U, std::plus<UINT>());
        }

        TEST_METHOD(ParallelAccumulate_LengthEqualToNumberOfThreads_ShouldAccumulate)
        {
            size_t numThreads = std::thread::hardware_concurrency();
            std::vector<UINT> input(numThreads);

            std::iota(input.begin(), input.end(), 0);

            UINT expected = std::accumulate(input.begin(), input.end(), 1U);
            UINT actual = parallel_accumulate(input.begin(), input.end(), 1U, std::plus<UINT>());
        }

        TEST_METHOD(ParallelAccumulate_LengthLessThanNumberOfThreads_ShouldAccumulate)
        {
            size_t numThreads = std::thread::hardware_concurrency();
            std::vector<UINT> input(numThreads-1);

            std::iota(input.begin(), input.end(), 0);

            UINT expected = std::accumulate(input.begin(), input.end(), 1U);
            UINT actual = parallel_accumulate(input.begin(), input.end(), 1U, std::plus<UINT>());
        }

        TEST_METHOD(ParallelAccumulate_LargeArray_ShouldAccumulate)
        {
            std::array<int, 90000> input;

            std::iota(input.begin(), input.end(), 0);

            UINT expected = std::accumulate(input.begin(), input.end(), 1);
            UINT actual = parallel_accumulate(input.begin(), input.end(), 1);
        }
    };
}
