/// RJINDAEL.H
///
/// @brief Computes the Rijndael AES S-Boxes at compile-time.
/// @author Mae B. Morella <https://github.com/morellam-dev>

#ifndef AES_RIJNDAEL_H_
#define AES_RIJNDAEL_H_

#include <array>
#include <cstdint>
#include <bit> // for std::rotl

#include "galois.h"
#include "aes.h" // for bytes_t


namespace rijndael {

using aes::byte;
using sbox_type = std::array<byte, 256>;

/// @brief Generates the rijndael S-boxes
/// @return {sbox_fwd, sbox_inverse}
consteval auto GenerateSboxes() -> std::pair<sbox_type, sbox_type> {
  // algorithm derived from <https://en.wikipedia.org/wiki/Rijndael_S-box>
  sbox_type sbox_fwd, sbox_inverse;
  uint8_t p = 1, q = 1; // loop invariant: p * q ≣ 1 in GF(2^8)
  do {
    p = galois::Multiply(p, 3);     // multiply p by 3
    q = galois::Multiply(q, 0xf6);  // divide q by 3
    // Affine transformation
    uint8_t affine =
        q ^ std::rotl(q, 1) ^ std::rotl(q, 2) ^ std::rotl(q, 3) ^ std::rotl(q, 4) ^ 0x63;
    sbox_fwd.at(p) = affine;
    sbox_inverse.at(affine) = p;
  } while (p != 1);

  /* 0 is a special case since it has no inverse */
  sbox_fwd.at(0) = 0x63;
  sbox_inverse.at(0x63) = 0;
  return {sbox_fwd, sbox_inverse};
}

constexpr auto Sbox = GenerateSboxes().first;
constexpr auto SboxInverse = GenerateSboxes().second;

/// @brief Lookup a single byte in the Rijndael Sbox.
///
/// @param b The byte to lookup
/// @param inverse If true, return the inverse substitution (default false)
/// @return The corresponding byte to b in the Sbox
inline auto SubByte(byte b, bool inverse = false) -> byte {
  if (inverse) {
    return SboxInverse.at(b);
  } else {
    return Sbox.at(b);
  }
}

}  // namespace rijndael

#endif