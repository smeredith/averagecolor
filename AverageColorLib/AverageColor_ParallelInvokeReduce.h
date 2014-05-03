#pragma once

#include <vector>

DWORD AverageColor_ParallelInvokeReduce(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end);
