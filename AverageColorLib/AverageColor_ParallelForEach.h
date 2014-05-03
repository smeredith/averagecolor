#pragma once

DWORD AverageColor_ParallelForEach(
    const std::vector<BYTE>::const_iterator& begin,
    const std::vector<BYTE>::const_iterator& end,
    UINT width,
    UINT height);
