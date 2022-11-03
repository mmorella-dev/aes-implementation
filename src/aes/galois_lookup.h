#include <array>
#include <cstdint>

namespace galois
{
    constexpr uint8_t gn_mult(uint8_t a, uint8_t b) {
        uint8_t p = 0;
        for (int c = 0; c < 8; c++) {
            if ((b & 1) != 0) {
                p ^= a;
            }
            bool hi = (a & 0x80) != 0;
            a <<= 1;
            if (hi) {
                a ^= 0x1B; /* x^8 + x^4 + x^3 + x + 1 */
            }
            b >>= 1;
        }
        return p;
    }

    constexpr std::array<uint8_t, 256> create_galois_lookup(uint8_t n) {
        std::array<uint8_t, 256> arr;
        for (int i = 0; i < 256; i++) {
            arr[i] = gn_mult(i, n);
        }
        return arr;
    }

    constexpr const std::array<uint8_t, 256> x2 = create_galois_lookup(2);
    constexpr const std::array<uint8_t, 256> x9 = create_galois_lookup(9);
    constexpr const std::array<uint8_t, 256> xB = create_galois_lookup(11);
    constexpr const std::array<uint8_t, 256> xD = create_galois_lookup(13);
    constexpr const std::array<uint8_t, 256> xE = create_galois_lookup(14);
}