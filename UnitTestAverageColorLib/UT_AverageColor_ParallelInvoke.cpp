#include "stdafx.h"
#include "CppUnitTest.h"
#include <RawBitmap.h>
#include <AverageColor_ParallelInvoke.h>
#include "AverageColorTestSet.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestAverageColorLib
{
    TEST_CLASS(TestAverageColor_ParallelInvoke)
    {
    private:
        void TestForExpected(UINT, UINT, std::vector<BYTE> pixels, DWORD expected)
        {
            DWORD averageColor = AverageColor_ParallelInvoke(
                ColorIterator(pixels.cbegin()), ColorIterator(pixels.cend()),
                ColorIterator(pixels.cbegin() + 1), ColorIterator(pixels.cend() + 1),
                ColorIterator(pixels.cbegin() + 2), ColorIterator(pixels.cend() + 2));

            Assert::AreEqual(expected, averageColor);
        }

    public:

        // Insert the common set of tests from the .h file.
        AVERAGECOLOR_TEST_SET
    };
}
