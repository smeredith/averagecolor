#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include <EveryNIterator.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestAverageColorLib
{
    TEST_CLASS(TestEveryNIterator)
    {

    public:
        TEST_METHOD(EveryNIterator_UINT_PreInc_ShouldFindNthElement)
        {
            std::vector<UINT> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<UINT>::iterator, 1> iter1(input.begin());
            for (UINT i = 0; i < input.size() - 1; ++i)
            {
                Assert::AreEqual(i+1, *(++iter1));
            }

            EveryNIterator<std::vector<UINT>::const_iterator, 2> iter2(input.begin());
            for (UINT i = 0; i < input.size() / 2; ++i)
            {
                Assert::AreEqual(i * 2, *iter2);
                ++iter2;
            }

            EveryNIterator<std::vector<UINT>::const_iterator, 3> iter3(input.begin());
            for (UINT i = 0; i < input.size() / 3; ++i)
            {
                Assert::AreEqual(i * 3, *iter3);
                ++iter3;
            }
        }

        TEST_METHOD(EveryNIterator_BYTE_PostInc_ShouldFindNthElement)
        {
            std::vector<BYTE> input = { 0, 1, 2, 3, 4, 5 };

            EveryNIterator<std::vector<BYTE>::iterator, 1> iter1(input.begin());
            for (BYTE i = 0; i < input.size(); ++i)
            {
                Assert::AreEqual(i, *iter1++);
            }

            EveryNIterator<std::vector<BYTE>::const_iterator, 2> iter2(input.begin());
            for (BYTE i = 0; i < input.size() / 2; ++i)
            {
                Assert::AreEqual(static_cast<BYTE>(i * 2), *iter2++);
            }

            EveryNIterator<std::vector<BYTE>::const_iterator, 3> iter3(input.begin());
            for (BYTE i = 0; i < input.size() / 3; ++i)
            {
                Assert::AreEqual(static_cast<BYTE>(i * 3), *iter3++);
            }
        }

        TEST_METHOD(EveryNIterator_Int_PreDec_ShouldFindNthElement)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> iter2(input.end());
            --iter2;
            Assert::AreEqual(4, *iter2);
        }

        TEST_METHOD(EveryNIterator_SubtractionOfDifferentIters_ShouldBeDifference)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> beginIter(input.begin());
            EveryNIterator<std::vector<int>::const_iterator, 2> endIter(input.end());
            Assert::AreEqual(0, beginIter - beginIter);
        }

        TEST_METHOD(EveryNIterator_SubtractionOfSameIters_ShouldBeZero)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> beginIter(input.begin());
            EveryNIterator<std::vector<int>::const_iterator, 2> endIter(input.end());
            Assert::AreEqual(0, beginIter - beginIter);
        }

        TEST_METHOD(EveryNIterator_AdditionOfPositive_ShouldBeCorrect)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> beginIter(input.begin());
            Assert::AreEqual(4, *(beginIter + 2));
        }

        TEST_METHOD(EveryNIterator_AdditionOfZero_ShouldBeSame)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> beginIter(input.begin());
            Assert::AreEqual(0, *(beginIter + 0));
        }

        TEST_METHOD(EveryNIterator_AdditionOfNegative_ShouldBeCorrent)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> endIter(input.end());
            Assert::AreEqual(4, *(endIter + -1));
        }

        TEST_METHOD(EveryNIterator_NotEqual_ShouldBeTrueForDifferentIterators)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> beginIter(input.begin());
            EveryNIterator<std::vector<int>::const_iterator, 2> endIter(input.end());
            Assert::IsTrue(beginIter != endIter);
        }

        TEST_METHOD(EveryNIterator_NotEqual_ShouldBeFalseForSameIterators)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> iter1(input.begin());
            EveryNIterator<std::vector<int>::const_iterator, 2> iter2(input.begin());
            Assert::IsFalse(iter1 != iter2);
        }

        TEST_METHOD(EveryNIterator_GreaterThanOrEqual_ShouldBeTrueForEqual)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> iter1(input.begin());
            EveryNIterator<std::vector<int>::const_iterator, 2> iter2(input.begin());
            Assert::IsTrue(iter1 >= iter2);
        }

        TEST_METHOD(EveryNIterator_GreaterThanOrEqual_ShouldBeTrueForGreaterThan)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> iter1(input.begin());
            EveryNIterator<std::vector<int>::const_iterator, 2> iter2(input.end());
            Assert::IsTrue(iter2 >= iter1);
        }

        TEST_METHOD(EveryNIterator_GreaterThanOrEqual_ShouldBeFalseForLessThan)
        {
            std::vector<int> input = {0,1,2,3,4,5};

            EveryNIterator<std::vector<int>::const_iterator, 2> iter1(input.begin());
            EveryNIterator<std::vector<int>::const_iterator, 2> iter2(input.end());
            Assert::IsFalse(iter1 >= iter2);
        }
    };
}
