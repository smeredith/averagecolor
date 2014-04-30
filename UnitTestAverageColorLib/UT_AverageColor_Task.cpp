#include "stdafx.h"
#include "CppUnitTest.h"
#include <RawBitmap.h>
#include <AverageColor_Task.h>
#include "AverageColorTestSet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestAverageColorLib
{
    TEST_CLASS(TestAverageColor_Task)
    {
    private:
        void TestForExpected(UINT width, UINT height, RawBitmap::PixelColorVector pixels, DWORD expected)
        {
            // Test the three interesting chunk sizes. If you pass 0, the function picks a
            // chunk size for you. 1 and 2 are also where bugs could exist.
            for (size_t chunkSize = 0; chunkSize < 3; ++chunkSize)
            {
                DWORD averageColor = AverageColor_Task(pixels.begin(), pixels.end(), chunkSize);
                Assert::AreEqual(expected, averageColor);
            }
        }

    public:

        // Insert the common set of tests from the .h file.
        AVERAGECOLOR_TEST_SET
    };
}
