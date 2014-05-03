// Wrap a decoded bitmap and expose iterators to access its pixels.

#pragma once

#include <vector>

class RawBitmap
{
    public:

        HRESULT InitFromFile(PCWSTR pFilename);

        std::vector<BYTE>::const_iterator cbegin() { return m_bitmap.cbegin(); };
        std::vector<BYTE>::const_iterator cend() { return m_bitmap.cend(); };
        UINT Width() const { return m_width; };
        UINT Height() const { return m_height; };

    private:
        std::vector<BYTE> m_bitmap;
        UINT m_width = 0;
        UINT m_height = 0;
};
