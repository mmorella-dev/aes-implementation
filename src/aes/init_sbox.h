#include <array>
#include <cstdint>

#include "galois.h"

constexpr inline uint8_t rotl8(uint8_t x, uint8_t shift)
{
    return ((uint8_t)((x) << (shift)) | ((x) >> (8 - (shift))));
}

consteval std::array<uint8_t, 256> generate_sbox(bool inverse)
{
    std::array<uint8_t, 256> sbox;
    uint8_t p = 1, q = 1;
    // loop invariant: p * q == 1 in the Galois field
    do
    {
        p = galois::x3[p]; // multiply p by 3
        q = galois::gn_mult(q, 0xf6); // divide q by 3
        // Affine transformation
        uint8_t affine = q ^ rotl8(q, 1) ^ rotl8(q, 2) ^ rotl8(q, 3) ^ rotl8(q, 4) ^ 0x63;
        if (!inverse)
            sbox[p] = affine;
        else
            sbox[affine] = p;
    } while (p != 1);

    /* 0 is a special case since it has no inverse */
    sbox[0] = 0x63;
    return sbox;
}

constexpr auto SBOX = generate_sbox(false);
constexpr auto SBOX_INVERSE = generate_sbox(true);