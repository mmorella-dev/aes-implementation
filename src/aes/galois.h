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
consteval uint8_t gn_mult(uint8_t a, uint8_t b) {
  uint8_t p = 0;
  for (int c = 0; c < 8; c++) {
    if ((b & 1) != 0) {
      p ^= a;
    }
    bool hi = a & 0b1000'0000;
    a <<= 1;  // lshift by 1
    if (hi) {
      a ^= 0b0001'1011; /* x^4 + x^3 + x + 1 */
    }
    b >>= 1;
  }
  return p;
}

/// @brief
consteval std::array<uint8_t, 256> generate_galois_lookup(const uint8_t n) {
  std::array<uint8_t, 256> arr;
  for (int i = 0; i < 256; i++) {
    arr[i] = gn_mult(i, n);
  }
  return arr;
}
/// For a given index i, x2[i] is 2 * i over GN(2^8)
constexpr auto x2 = generate_galois_lookup(2);
/// For a given index i, x3[i] is 3 * i over GN(2^8)
constexpr auto x3 = generate_galois_lookup(3);
/// For a given index i, x2[i] is 9 * i over GN(2^8)
constexpr auto x9 = generate_galois_lookup(9);
/// For a given index i, xB[i] is 11 * i over GN(2^8)
constexpr auto xB = generate_galois_lookup(11);
/// For a given index i, xD[i] is 13 * i over GN(2^8)
constexpr auto xD = generate_galois_lookup(13);
/// For a given index i, xE[i] is 14 * i over GN(2^8)
constexpr auto xE = generate_galois_lookup(14);
}  // namespace galois

#endif