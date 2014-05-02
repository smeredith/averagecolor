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
        void TestForExpected(UINT, UINT, std::vector<BYTE> pixels, DWORD expected)
        {
            DWORD averageColor = AverageColor_Task(
                ColorIterator(pixels.begin()), ColorIterator(pixels.end()),
                ColorIterator(pixels.begin() + 1), ColorIterator(pixels.end() + 1),
                ColorIterator(pixels.begin() + 2), ColorIterator(pixels.end() + 2),
                0);

            Assert::AreEqual(expected, averageColor);
        }

    public:

        // Insert the common set of tests from the .h file.
        AVERAGECOLOR_TEST_SET
    };
}
