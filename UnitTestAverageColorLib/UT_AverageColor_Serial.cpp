#include "stdafx.h"
#include "CppUnitTest.h"
#include <RawBitmap.h>
#include <AverageColor_Serial.h>
#include "AverageColorTestSet.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestAverageColorLib
{
    TEST_CLASS(TestAverageColor_Serial)
    {
    private:
        void TestForExpected(UINT, UINT, RawBitmap::PixelColorVector pixels, DWORD expected)
        {
            DWORD averageColor = AverageColor_Serial(pixels.begin(), pixels.end());
            Assert::AreEqual(expected, averageColor);
        }

    public:

        // Insert the common set of tests from the .h file.
        AVERAGECOLOR_TEST_SET
    };
}
