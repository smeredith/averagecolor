// Wrap a decoded bitmap and expose iterators to access its pixels.

#pragma once

#include <array>
#include <vector>

class RawBitmap
{
    public:
        // A raw bitmap is a vector of pixels, where each pixel is a 3-byte color array
        // one for each of red, green, and blue.
        typedef std::array<unsigned char, 3> PixelColor;
        typedef std::vector<PixelColor> PixelColorVector;

        HRESULT InitFromFile(const wchar_t* pFilename);

        PixelColorVector::iterator begin() { return m_bitmap.begin(); };
        PixelColorVector::iterator end() { return m_bitmap.end(); };
        unsigned int Width() { return m_width; };
        unsigned int Height() { return m_height; };

    private:
        PixelColorVector m_bitmap;
        unsigned int m_width = 0;
        unsigned int m_height = 0;
};
