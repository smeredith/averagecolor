#include "stdafx.h"
#include "CppUnitTest.h"
#include <AverageColor_ParallelInvokeReduce.h>
#include "AverageColorTestSet.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestAverageColorLib
{
    TEST_CLASS(TestAverageColor_ParallelInvokeReduce)
    {
    private:
        void TestForExpected(UINT, UINT, std::vector<BYTE> pixels, DWORD expected)
        {
            DWORD averageColor = AverageColor_ParallelInvokeReduce(pixels.cbegin(), pixels.cend());

            Assert::AreEqual(expected, averageColor);
        }

    public:

        // Insert the common set of tests from the .h file.
        AVERAGECOLOR_TEST_SET
    };
}
