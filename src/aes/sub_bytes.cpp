#include "aes.h"
#include "rijndael.h"

#include <algorithm>

namespace aes
{
    Bytes16 sub_bytes(const Bytes16 &input, bool inverse)
    {
        Bytes16 result;
        std::transform(input.begin(), input.end(), result.begin(), [=](uint8_t b)
                       {
        if (!inverse)
            return rjindael::SBOX[b];
        else
            return SBOX_INVERSE[b]; });
        return result;
    }
}