// Wrap a decoded bitmap and expose iterators to access its pixels.

#pragma once

#include <array>
#include <vector>

class RawBitmap
{
    public:
        // A raw bitmap is a vector of pixels, where each pixel is a 3-byte color array
        // one for each of red, green, and blue.
        typedef std::array<BYTE, 3> PixelColor;
        typedef std::vector<PixelColor> PixelColorVector;

        HRESULT InitFromFile(PCWSTR pFilename);

        PixelColorVector::iterator begin() { return m_bitmap.begin(); };
        PixelColorVector::iterator end() { return m_bitmap.end(); };
        UINT Width() { return m_width; };
        UINT Height() { return m_height; };

    private:
        PixelColorVector m_bitmap;
        UINT m_width = 0;
        UINT m_height = 0;
};
