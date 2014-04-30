#include "stdafx.h"
#include "CppUnitTest.h"
#include <CppUnitTestAssert.h>
#include <ColorCalculations.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<> static std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<PixelColorSums>(const PixelColorSums& t)
{ 
    std::wstringstream _s;	
    _s << t[0] << L' ' << t[1] << L' ' << t[2]; return _s.str();
}

namespace UnitTestAverageColorLib
{
    TEST_CLASS(UnitTestColorCalculations)
    {
        public:

            TEST_METHOD(PixelColorSums_OperatorPlus_rhs_zero)
            {
                PixelColorSums expected = {1,2,3};
                PixelColorSums rhs = {};
                PixelColorSums lhs = {1,2,3};
                PixelColorSums result = rhs + lhs;

                Assert::AreEqual(expected, result);
            }

            TEST_METHOD(PixelColorSums_OperatorPlus_lhs_zero)
            {
                PixelColorSums expected = { 1, 2, 3 };
                PixelColorSums lhs = {};
                PixelColorSums rhs = { 1, 2, 3 };
                PixelColorSums result = rhs + lhs;

                Assert::AreEqual(expected, result);
            }

            TEST_METHOD(PixelColorSums_OperatorPlus_both_zero)
            {
                PixelColorSums expected = {};
                PixelColorSums lhs = {};
                PixelColorSums rhs = {};
                PixelColorSums result = rhs + lhs;

                Assert::AreEqual(expected, result);
            }

            TEST_METHOD(PixelColorSums_OperatorPlus_both_nonzero)
            {
                PixelColorSums expected = {2,5,9};
                PixelColorSums lhs = {1,2,3};
                PixelColorSums rhs = {1,3,6};
                PixelColorSums result = rhs + lhs;

                Assert::AreEqual(expected, result);
            }

    };
}
