// Wrap a decoded bitmap and expose iterators to access its pixels.

#pragma once

#include <array>
#include <vector>

class RawBitmap
{
    public:
        // A raw bitmap is a vector of 3 bytes, one for each of red, green, and blue.
        typedef std::vector<std::array<unsigned char, 3>> PixelColorVector;

        HRESULT InitFromFile(const wchar_t* pFilename);

        PixelColorVector::iterator begin() { return m_bitmap.begin(); };
        PixelColorVector::iterator end() { return m_bitmap.end(); };

    private:
        PixelColorVector m_bitmap;
};
