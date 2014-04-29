#include "stdafx.h"
#include "CppUnitTest.h"
#include <RawBitmap.h>
#include <AverageColor_ParallelForEach.h>
#include "AverageColorTestSet.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestAverageColorLib
{
    TEST_CLASS(TestAverageColor_ParallelForEach)
    {
    private:
        void TestForExpected(UINT width, UINT height, RawBitmap::PixelColorVector pixels, DWORD expected)
        {
            DWORD averageColor = AverageColor_ParallelForEach(pixels.begin(), pixels.end(), width, height);
            Assert::AreEqual(expected, averageColor);
        }

    public:

        // Insert the common set of tests from the .h file.
        AVERAGECOLOR_TEST_SET
    };
}
