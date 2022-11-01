#include "aes.h"

#include <array>

using Word = std::array<Byte, 4>;

Bytes176 key_expansion(const Bytes16 &key)
{
    std::array<Word, 44> output;
    // for (int i{}; i < 4; i++)
    // {
    //     // get row i
    //     output[i] =
    //         {key[4 * i], key[4 * i + 1], key[4 * i + 2], key[4 * i + 3]};
    // }
    // Word &temp = output[3];
    // for (int i = 4; i < 44; i++)
    // {
    //     temp = output[i - 1];
    //     if (i % 4 == 0) {
    //         temp = SubWord ( RotWord (temp)) ^ Rcon[i/4];
    //         w[i] = w[i-4] ^ temp;
    //     }
    // }
}
