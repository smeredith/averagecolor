#pragma once

#include <numeric>
#include <future>
#include <vector>

// This is similar to concurrency::parallel_reduce().
template <typename Iterator, typename T, typename BinaryOperation>
T parallel_accumulate(Iterator first, Iterator last, T init, BinaryOperation binOp)
{
    size_t inputLength = last - first;
    size_t numThreads = std::thread::hardware_concurrency();
    size_t blockSize = inputLength / numThreads;

    // If too few items to benefit from parallel execution, use standard std::accumulate().
    if (blockSize < 1000)
    {
        return std::accumulate(first, last, init, binOp);
    }

    std::vector<std::future<T>> futures(numThreads - 1);

    Iterator blockFirst = first;
    for (size_t i = 0; i < numThreads - 1; ++i)
    {
        Iterator blockLast = blockFirst + blockSize;
        futures[i] = std::async(std::accumulate<Iterator, T, BinaryOperation>, blockFirst, blockLast, 0, binOp);
        blockFirst = blockLast;
    }

    // Use init so that it is part of the total. This last operation is performed on the current thread.
    // Since it uses last, it uses the remainer for when inputLength is not evenly divisible by numThreads.
    T total = std::accumulate(blockFirst, last, init, binOp);

    for (auto& f : futures)
    {
        total += f.get();
    }

    return total;
}

template <typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
    return parallel_accumulate(first, last, init, std::plus<T>());
}

