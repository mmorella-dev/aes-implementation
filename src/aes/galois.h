/// GALOIS.H
///
/// @brief Provides common lookup tables for multiplication in
///        GF(2^8) mod (x^8 + x^4 + x^3 + x + 1)
/// @author Mae B. Morella <https://github.com/morellam-dev>

#include <algorithm>
#include <array>
#include <cstdint>

#ifndef AES_GALOIS_H_
#define AES_GALOIS_H_
namespace galois {

/// @brief Performs multiplication in the AES Galois feld
/// @param a An 8 bit number to multiply
/// @param b An 8 bit number to multiply
/// @return the result of a*b in GF(2^8) mod (x^8 + x^4 + x^3 + x + 1)
constexpr auto Multiply(uint8_t a, uint8_t b) -> uint8_t {
  // algorithm derived from <https://en.wikipedia.org/wiki/Rijndael_MixColumns>
  uint8_t p = 0;
  for (int c = 0; c < 8; c++) {
    p ^= -(b & 1) & a;
    bool high_bit = a & (1 << 7);
    a <<= 1;  // lshift by 1
    if (high_bit) {
      a ^= 0b1'1011; /* x^4 + x^3 + x + 1 */
    }
    b >>= 1;
  }
  return p;
}

/// @brief Computes the lookup table for a * n over GN(2^8)
consteval auto GenerateMultLookupTable(const uint8_t n)
    -> std::array<uint8_t, 256> {
  std::array<uint8_t, 256> arr;
  for (int i = 0; i < 256; i++) {
    arr[i] = Multiply(i, n);
  }
  return arr;
}
/// For a given index i, x2[i] is 2 * i over GN(2^8)
constexpr auto x2 = GenerateMultLookupTable(2);
/// For a given index i, x3[i] is 3 * i over GN(2^8)
constexpr auto x3 = GenerateMultLookupTable(3);
/// For a given index i, x2[i] is 9 * i over GN(2^8)
constexpr auto x9 = GenerateMultLookupTable(9);
/// For a given index i, xB[i] is 11 * i over GN(2^8)
constexpr auto xB = GenerateMultLookupTable(11);
/// For a given index i, xD[i] is 13 * i over GN(2^8)
constexpr auto xD = GenerateMultLookupTable(13);
/// For a given index i, xE[i] is 14 * i over GN(2^8)
constexpr auto xE = GenerateMultLookupTable(14);
}  // namespace galois

#endif