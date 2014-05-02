// Wrap a decoded bitmap and expose iterators to access its pixels.

#pragma once

#include <vector>
#include "EveryNIterator.h"

typedef EveryNIterator<std::vector<BYTE>::const_iterator, 3> ColorIterator;

class RawBitmap
{
    public:

        HRESULT InitFromFile(PCWSTR pFilename);

        ColorIterator begin(size_t color) { return ColorIterator(m_bitmap.begin() + color); };
        ColorIterator end(size_t color) { return ColorIterator(m_bitmap.end() + color); };
        UINT Width() const { return m_width; };
        UINT Height() const { return m_height; };

    private:
        std::vector<BYTE> m_bitmap;
        UINT m_width = 0;
        UINT m_height = 0;
};
