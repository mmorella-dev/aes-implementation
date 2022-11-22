#include "aes.h"
#include "rijndael.h"

#include <algorithm>
#include <array>
#include <bit>
#include <numeric>
#include <cstdint>

namespace aes
{
    using Bytes4 = std::array<uint8_t, 4>;

    Bytes16 rc = {0xFF, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

    Bytes176 key_expansion(const Bytes16 &key)
    {
        std::array<Bytes4, 44> w;
        for (int i = 0; i < 4; i++)
        {
            // get row i
            w[i] = {key[4 * i], key[4 * i + 1], key[4 * i + 2], key[4 * i + 3]};
        }
        Bytes4 temp;
        for (int i = 4; i < 44; i++)
        {
            temp = w[i - 1];
            if (i % 4 == 0)
            {
                // rotate left by 1
                std::rotate(temp.begin(), temp.begin() + 1, temp.end());
                // sub word
                std::transform(temp.cbegin(), temp.cend(), temp.begin(), [](uint8_t b)
                               { return SBOX[b]; });
                // sub rcon
                temp[0] ^= rc[i / 4];
            }
            // w[i] = w[i-1];
            std::transform(w[i-4].cbegin(), w[i - 4].cend(), temp.cbegin(), w[i].begin(), std::bit_xor{});
        }
        return std::bit_cast<Bytes176>(w);
    }
}