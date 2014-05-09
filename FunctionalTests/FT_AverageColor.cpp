#include "stdafx.h"
#include "CppUnitTest.h"
#include <AverageColor.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FunctionalTests
{
    TEST_CLASS(UnitTestAverageColor)
    {
        private:
            void TestFile(PCWSTR filename, DWORD expected)
            {
                DWORD averageColor = 0;
                HRESULT hr = AverageColor(filename, averageColor);

                Assert::AreEqual(S_OK, hr);
                Assert::AreEqual(expected, averageColor);
            }

        public:

            TEST_METHOD(FT_AveragaeColor_NullFilenameShouldFail)
            {
                DWORD averageColor = 0;

                HRESULT hr = AverageColor(nullptr, averageColor);
                Assert::AreEqual(E_INVALIDARG, hr);
            }

            TEST_METHOD(FT_AveragaeColor_FileNotFoundShouldFail)
            {
                DWORD averageColor = 0;

                HRESULT hr = AverageColor(L"not_a_file.jpg", averageColor);
                Assert::IsTrue(FAILED(hr));
            }

            TEST_METHOD(FT_AveragaeColor_256ColorUnsupportedFormatShouldFail)
            {
                DWORD averageColor = 0;

                HRESULT hr = AverageColor(L"..\\TestFiles\\256color.bmp", averageColor);
                Assert::IsTrue(FAILED(hr));
            }

            TEST_METHOD(FT_AveragaeColor_16ColorUnsupportedFormatShouldFail)
            {
                DWORD averageColor = 0;

                HRESULT hr = AverageColor(L"..\\TestFiles\\16color.bmp", averageColor);
                Assert::IsTrue(FAILED(hr));
            }

            TEST_METHOD(FT_AveragaeColor_1x1_000000)
            {
                TestFile(L"..\\TestFiles\\1x1_000000.bmp", 0);
            }

            TEST_METHOD(FT_AveragaeColor_1x1_0000ff)
            {
                TestFile(L"..\\TestFiles\\1x1_0000ff.bmp", 0xff);
            }

            TEST_METHOD(FT_AveragaeColor_1x1_00ff00)
            {
                TestFile(L"..\\TestFiles\\1x1_00ff00.bmp", 0xff00);
            }

            TEST_METHOD(FT_AveragaeColor_1x1_ff0000)
            {
                TestFile(L"..\\TestFiles\\1x1_ff0000.bmp", 0xff0000);
            }

            TEST_METHOD(FT_AveragaeColor_1x1_ffffff)
            {
                TestFile(L"..\\TestFiles\\1x1_ffffff.bmp", 0xffffff);
            }

            TEST_METHOD(FT_AveragaeColor_1x255_020202)
            {
                TestFile(L"..\\TestFiles\\1x255_020202.bmp", 0x020202);
            }

            TEST_METHOD(FT_AveragaeColor_2x2_000000)
            {
                TestFile(L"..\\TestFiles\\2x2_000000.bmp", 0);
            }

            TEST_METHOD(FT_AveragaeColor_2x2_00003f)
            {
                TestFile(L"..\\TestFiles\\2x2_00003f.bmp", 0x3f);
            }

            TEST_METHOD(FT_AveragaeColor_2x2_3f3f3f)
            {
                TestFile(L"..\\TestFiles\\2x2_3f3f3f.bmp", 0x3f3f3f);
            }

            TEST_METHOD(FT_AveragaeColor_2x2_7f0000)
            {
                TestFile(L"..\\TestFiles\\2x2_7f0000.bmp", 0x7f0000);
            }

            TEST_METHOD(FT_AveragaeColor_2x2_ff0000)
            {
                TestFile(L"..\\TestFiles\\2x2_ff0000.bmp", 0xff0000);
            }

            TEST_METHOD(FT_AveragaeColor_2x2_ffffff)
            {
                TestFile(L"..\\TestFiles\\2x2_ffffff.bmp", 0xffffff);
            }

            TEST_METHOD(FT_AveragaeColor_16x16_000400)
            {
                TestFile(L"..\\TestFiles\\16x16_000400.bmp", 0x400);
            }

            TEST_METHOD(FT_AveragaeColor_255x1_010101)
            {
                TestFile(L"..\\TestFiles\\255x1_010101.bmp", 0x010101);
            }

            TEST_METHOD(FT_AveragaeColor_255x1_030102)
            {
                TestFile(L"..\\TestFiles\\255x1_030102.bmp", 0x030102);
            }

            TEST_METHOD(FT_AveragaeColor_255x1_030303)
            {
                TestFile(L"..\\TestFiles\\255x1_030303.bmp", 0x030303);
            }

            TEST_METHOD(FT_AveragaeColor_64x1_020202)
            {
                TestFile(L"..\\TestFiles\\64x1_020202.bmp", 0x020202);
            }

            TEST_METHOD(FT_AveragaeColor_5000x5000_ffffff)
            {
                TestFile(L"..\\TestFiles\\5000x5000_ffffff.jpg", 0xffffff);
            }

            TEST_METHOD(FT_AveragaeColor_25000x1000_ff8041)
            {
                TestFile(L"..\\TestFiles\\25000x1000_ff8041.jpg", 0xff8041);
            }

            TEST_METHOD(FT_AveragaeColor_real_5e93b6)
            {
                TestFile(L"..\\TestFiles\\real_5e93b6.jpg", 0x5e93b6);
            }
    };
}
