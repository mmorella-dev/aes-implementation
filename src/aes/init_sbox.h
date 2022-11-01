using std::array;
using uint8_t = uint8_t;

#define ROTL8(x, shift) ((uint8_t)((x) << (shift)) | ((x) >> (8 - (shift))))
constexpr array<uint8_t, 256> initialize_aes_sbox(bool inverse)
{
    array<uint8_t, 256> sbox = {};
    uint8_t p = 1, q = 1;

    // loop invariant: p * q == 1 in the Galois field
    do
    {
        // multiply p by 3
        p = p ^ (p << 1) ^ (p & 0x80 ? 0x1B : 0);

        // divide q by 3 (equals multiplication by 0xf6)
        q ^= q << 1;
        q ^= q << 2;
        q ^= q << 4;
        q ^= q & 0x80 ? 0x09 : 0;

        // compute the affine transformation
        uint8_t xformed = q ^ ROTL8(q, 1) ^ ROTL8(q, 2) ^ ROTL8(q, 3) ^ ROTL8(q, 4);
        if (!inverse)
            sbox[p] = xformed ^ 0x63;
        else {
            sbox[xformed ^ 0x63] = p;
        }
    } while (p != 1);

    /* 0 is a special case since it has no inverse */
    sbox[0] = 0x63;
    return sbox;
}

constexpr array<uint8_t, 256> SBOX = initialize_aes_sbox(false);
constexpr array<uint8_t, 256> SBOX_INVERSE = initialize_aes_sbox(true);