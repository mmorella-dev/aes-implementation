/// MAIN.CPP
///
/// @brief A simple test program for the aes.h header.
///        Uses test data from Stallings' "Cryptography" (2022) 8th ed.
/// @author Mae B. Morella <https://github.com/morellam-dev>

#include <cassert>
#include <iomanip>  // std::setw
#include <iostream>

#include "aes/aes.h"
#include "aes/galois.h"
#include "aes/rijndael.h"

using aes::byte;

auto operator<<(std::ostream &os, const std::span<byte> &sp) -> std::ostream & {
  for (const auto b : sp) {
    os << std::hex << std::setfill('0') << std::setw(2) << (int)b << " ";
  }
  return os;
}

auto TestSubBytes() -> bool {
  std::cout << "Testing SubBytes... ";
  // example from page 176;
  const std::array<byte, 16> init = {
      0xEA, 0x83, 0x5C, 0xF0,  //
      0x04, 0x45, 0x33, 0x2D,  //
      0x65, 0x5D, 0x98, 0xAD,  //
      0x85, 0x96, 0xB0, 0xC5   //
  };
  const std::array<byte, 16> expected = {
      0x87, 0xEC, 0x4A, 0x8C,  //
      0xF2, 0x6E, 0xC3, 0xD8,  //
      0x4D, 0x4C, 0x46, 0x95,  //
      0x97, 0x90, 0xE7, 0xA6   //
  };
  // Call SubBytes
  std::array<byte, 16> result = init;
  aes::SubBytes(result);
  assert(expected == result);
  // Call SubBytes inverse
  std::array<byte, 16> result2 = expected;
  aes::SubBytes(result2, true);
  assert(result2 == init);
  std::cout << "✅ passed.\n";
  return true;
}

auto TestShiftRows() -> bool {
  std::cout << "Testing ShiftRows... ";
  // example from page 179
  const std::array<byte, 16> init = {
      0x87, 0xEC, 0x4A, 0x8C,  //
      0xF2, 0x6E, 0xC3, 0xD8,  //
      0x4D, 0x4C, 0x46, 0x95,  //
      0x97, 0x90, 0xE7, 0xA6   //
  };

  std::array<byte, 16> result = init;
  aes::ShiftRows(result);
  const std::array<byte, 16> expected = {
      0x87, 0x6E, 0x46, 0xA6,  //
      0xF2, 0x4C, 0xE7, 0x8C,  //
      0x4D, 0x90, 0x4A, 0xD8,  //
      0x97, 0xEC, 0xC3, 0x95,  //
  };
  assert(result == expected);
  std::cout << "✅ passed.\n";
  return true;
}

auto TestMixColumns() -> bool {
  std::cout << "Testing MixColumns... ";
  // example from p. 181
  const std::array<byte, 16> init = {
      0x87, 0x6E, 0x46, 0xA6,  //
      0xF2, 0x4C, 0xE7, 0x8C,  //
      0x4D, 0x90, 0x4A, 0xD8,  //
      0x97, 0xEC, 0xC3, 0x95,  //
  };
  std::array<byte, 16> result = init;
  aes::MixColumns(result, false);
  const std::array<byte, 16> expected = {0x47, 0x37, 0x94, 0xED,  //
                                         0x40, 0xD4, 0xE4, 0xA5,  //
                                         0xA3, 0x70, 0x3A, 0xA6,  //
                                         0x4C, 0x9F, 0x42, 0xBC};
  assert(result == expected);
  std::array<byte, 16> result2 = expected;
  // MixColumns inverse
  aes::MixColumns(result2, true);
  assert(result2 == init);
  std::cout << "✅ passed.\n";
  return true;
}

auto TestKeyExpansion() -> bool {
  std::cout << "Testing KeyExpansion...";
  std::array<byte, 16> key = {0x0F, 0x15, 0x71, 0xC9, 0x47, 0xD9, 0xE8, 0x59,
                              0x0C, 0xB7, 0xAD, 0xD6, 0xAF, 0x7F, 0x67, 0x98};
  std::cerr << "Key: ";
  std::cerr << key << '\n';

  auto result = aes::KeyExpansion(key);
  for (int i = 1; i < 11; i++) {
    std::cerr << "Round " << i << ": ";
    std::cerr << result[i] << '\n';
  }
  // sample data from p. 189
  std::array<byte, 16> round1 = {0xDC, 0x90, 0x37, 0xB0, 0x9B, 0x49,
                                 0xDF, 0xE9, 0x97, 0xFE, 0x72, 0x3F,
                                 0x38, 0x81, 0x15, 0xA7};
  std::array<byte, 16> round10 = {0xB4, 0x8E, 0xF3, 0x52, 0xBA, 0x98,
                                  0x13, 0x4E, 0x7F, 0x4D, 0x59, 0x20,
                                  0x86, 0x26, 0x18, 0x76};
  assert(result[1] == round1);
  assert(result[10] == round10);
  std::cout << "✅ passed.\n";
  return true;
}

auto main() -> int {
  assert(TestSubBytes());
  assert(TestShiftRows());
  assert(TestMixColumns());
  assert(TestKeyExpansion());
  std::cout << "🚀 All tests passed!\n";
}