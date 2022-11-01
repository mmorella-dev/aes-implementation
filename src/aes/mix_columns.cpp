#include "aes.h"

#include <algorithm>
#include <numeric>

Byte gf2n_multiply(int a, int b)
{
    const int overflow = 0x100, modulus = 0x11B; // AES GF(2^8) representation
    int sum = 0;
    while (b > 0)
    {
        if (b & 1)
            sum = sum ^ a; // if last bit of b is 1, add a to the sum
        b = b >> 1;        // divide b by 2, discarding the last bit
        a = a << 1;        // multiply a by 2
        if (a & overflow)
            a = a ^ modulus; // reduce a modulo the AES polynomial
    }
    return (Byte)sum;
}

using Bytes4 = std::array<Byte, 4>;

inline Bytes4 dot_product(const Bytes4 &v1, const Bytes4 &v2)
{
    Bytes4 product;
    std::transform(v1.cbegin(), v1.cend(), v2.cbegin(), product.begin(), gf2n_multiply);
    return product;
}

/// Gets a column from a matrix of bytes.
/// @param s A 4x4 matrix of bytes
/// @param j The index of of the column to get
/// @return The jth column
inline Bytes4 get_col(const Bytes16 &s, Byte j)
{
    return {s[j], s[4 + j], s[8 + j], s[12 + j]};
}

Bytes16 mix_columns(const Bytes16 &s, bool inverse)
{
    const Bytes4 mix_matrix[4] = {
        {2, 3, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 2, 3},
        {3, 1, 1, 2},
    };
    const Bytes4 mix_inv_matrix[4] = {
        {0xE, 0xB, 0xD, 0x9},
        {0x9, 0xE, 0xB, 0xD},
        {0xD, 0x9, 0xE, 0xB},
        {0xB, 0xD, 0x9, 0xE},
    };
    Bytes16 output;
    for (int j = 0; j < 4; j++)
    {
        Bytes4 col = get_col(s, j);
        for (int i = 0; i < 4; i++)
        {
            Bytes4 product = dot_product(
                (!inverse ? mix_matrix : mix_inv_matrix)[i], col);
            Byte ac = std::reduce(product.cbegin(), product.cend(), '\0', std::bit_xor{});
            output[i * 4 + j] = ac;
        }
    }
    return output;
}
