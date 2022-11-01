#include "aes.h"
#include "init_sbox.h"

#include <algorithm>

namespace aes
{
    Bytes16 sub_bytes(const Bytes16 &input, bool inverse)
    {
        Bytes16 result;
        std::transform(input.begin(), input.end(), result.begin(), [=](Byte b)
                       {
        if (!inverse)
            return SBOX[b];
        else
            return SBOX_INVERSE[b]; });
        return result;
    }
}