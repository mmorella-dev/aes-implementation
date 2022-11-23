#include "aes.h"

#include <algorithm>
#include <bit>      // for std::bit_cast
#include <numeric>  // std::bit_xor
#include <ranges>

#include "galois.h"
#include "rijndael.h"

using namespace aes;
namespace ranges = std::ranges;

void aes::sub_bytes(Bytes16 &input, bool inverse) {
  const auto &sbox = (!inverse) ? rjindael::SBOX : rjindael::SBOX_INVERSE;
  for (uint8_t &b: input) {
    b = sbox[b];
  }
}

void aes::shift_rows(Bytes16 &input, bool inverse) {
  for (int i = 0; i < 4; i++) {
    auto row = input.begin() + 4 * i;
    auto middle = row + (!inverse ? i : 4 - i);
    std::rotate(row, middle, row + 4);
  }
}

void aes::mix_columns(Bytes16 &s, bool inverse) {
  // import lookup tables
  using namespace galois;
  for (int j = 0; j < 4; j++) {
    // get column vector
    Bytes4 a = {s[j], s[4 + j], s[8 + j], s[12 + j]};
    if (!inverse) {
      uint8_t temp = a[0] ^ a[1] ^ a[2] ^ a[3];
      s[j] = a[0] ^ temp ^ x2[a[0] ^ a[1]];
      s[j + 4] = a[1] ^ temp ^ x2[a[1] ^ a[2]];
      s[j + 8] = a[2] ^ temp ^ x2[a[2] ^ a[3]];
      s[j + 12] = a[3] ^ temp ^ x2[a[3] ^ a[0]];
    } else {
      s[j] = xE[a[0]] ^ x9[a[3]] ^ xD[a[2]] ^ xB[a[1]];
      s[j + 4] = xE[a[1]] ^ x9[a[0]] ^ xD[a[3]] ^ xB[a[2]];
      s[j + 8] = xE[a[2]] ^ x9[a[1]] ^ xD[a[0]] ^ xB[a[3]];
      s[j + 12] = xE[a[3]] ^ x9[a[2]] ^ xD[a[1]] ^ xB[a[0]];
    }
  }
}

const Bytes16 rc = {0xFF, 0x01, 0x02, 0x04, 0x08, 0x10,
                    0x20, 0x40, 0x80, 0x1B, 0x36};

Bytes176 aes::key_expansion(const Bytes16 &key) {
  std::array<Bytes4, 44> w;
  std::array<uint8_t, 176> w2;
  for (int i = 0; i < 4; i++) {
    // get row i
    w[i] = {key[4 * i], key[4 * i + 1], key[4 * i + 2], key[4 * i + 3]};
  }
  for (int i = 4; i < 44; i++) {
    Bytes4 temp = w[i - 1];
    if (i % 4 == 0) {
      // rotate left by 1
      ranges::rotate(temp, temp.begin() + 1);
      // sub word
      for (uint8_t &b : temp) {
        b = rjindael::SBOX[b];
      }
      // sub rcon
      temp[0] ^= rc[i / 4];
    }
    // w[i] = w[i-1] ^ temp;
    ranges::transform(w[i - 4], temp, w[i].begin(), std::bit_xor{});
  }
  return std::bit_cast<Bytes176>(w);
}