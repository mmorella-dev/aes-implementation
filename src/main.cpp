#include <cassert>
#include <iomanip>  // std::setw
#include <iostream>

#include "aes/aes.h"
#include "aes/galois.h"
#include "aes/rijndael.h"

using namespace aes;

auto operator<<(std::ostream &os, const std::span<byte> &sp) -> std::ostream& {
  for (const auto b : sp) {
    os << std::hex << std::setfill('0') << std::setw(2) << (int)b << " ";
  }
  return os;
}

auto test_sub_bytes() -> bool {
  std::cout << "Testing sub_bytes... ";
  // example from page 176;
  const std::array<byte, 16> init = {0xEA, 0x04, 0x65, 0x85,  //
                        0x83, 0x45, 0x5D, 0x96,  //
                        0x5C, 0x33, 0x98, 0xB0,  //
                        0xF0, 0x2D, 0xAD, 0xC5};
  const std::array<byte, 16> expected = {0x87, 0xF2, 0x4D, 0x97,  //
                            0xEC, 0x6E, 0x4C, 0x90,  //
                            0x4A, 0xC3, 0x46, 0xE7,  //
                            0x8C, 0xD8, 0x95, 0xA6};
  // Call sub_bytes
  std::array<byte, 16> result = init;
  sub_bytes(result);
  assert(expected == result);
  // Call sub_bytes inverse
  std::array<byte, 16> result2 = expected;
  sub_bytes(result2, true);
  assert(result2 == init);
  std::cout << "✅ passed.\n";
  return true;
}

auto test_shift_rows() -> bool {
  std::cout << "Testing shift_rows... ";
  // example from page 179
  const std::array<byte, 16> init = {
      0x87, 0xF2, 0x4D, 0x97,  //
      0xEC, 0x6E, 0x4C, 0x90,  //
      0x4A, 0xC3, 0x46, 0xE7,  //
      0x8C, 0xD8, 0x95, 0xA6   //
  };
  std::array<byte, 16> result = init;
  shift_rows(result);
  const std::array<byte, 16> expected = {
      0x87, 0xF2, 0x4D, 0x97,  //
      0x6E, 0x4C, 0x90, 0xEC,  //
      0x46, 0xE7, 0x4A, 0xC3,  //
      0xA6, 0x8C, 0xD8, 0x95   //
  };
  assert(result == expected);
  std::cout << "✅ passed.\n";
  return true;
}

auto test_mix_columns() -> bool {
  std::cout << "Testing mix_columns... ";
  // example from p. 181
  const std::array<byte, 16> init = {
      0x87, 0xF2, 0x4D, 0x97,  //
      0x6E, 0x4C, 0x90, 0xEC,  //
      0x46, 0xE7, 0x4A, 0xC3,  //
      0xA6, 0x8C, 0xD8, 0x95   //
  };
  std::array<byte, 16> result = init;
  mix_columns(result, false);
  const std::array<byte, 16> expected = {
      0x47, 0x40, 0xA3, 0x4C,  //
      0x37, 0xD4, 0x70, 0x9F,  //
      0x94, 0xE4, 0x3A, 0x42,  //
      0xED, 0xA5, 0xA6, 0xBC   //
  };

  assert(result == expected);
  std::array<byte, 16> result2 = expected;
  mix_columns(result2, true);
  assert(result2 == init);
  std::cout << "✅ passed.\n";
  return true;
}

auto test_key_expansion() -> bool {
  std::cout << "Testing key_expansion...";
  std::array<byte, 16> key = {0x0F, 0x15, 0x71, 0xC9, 0x47, 0xD9, 0xE8, 0x59,
                 0x0C, 0xB7, 0xAD, 0xD6, 0xAF, 0x7F, 0x67, 0x98};
  std::cerr << "Key: ";
  std::cerr << key << '\n';

  auto result = key_expansion(key);
  for (int i = 1; i < 11; i++) {
    std::cerr << "Round " << i << ": ";
    std::cerr << result[i] << '\n';
  }
  // sample data from p. 189
  std::array<byte, 16> round1 = {0xDC, 0x90, 0x37, 0xB0, 0x9B, 0x49, 0xDF, 0xE9,
                    0x97, 0xFE, 0x72, 0x3F, 0x38, 0x81, 0x15, 0xA7};
  std::array<byte, 16> round10 = {0xB4, 0x8E, 0xF3, 0x52, 0xBA, 0x98, 0x13, 0x4E,
                     0x7F, 0x4D, 0x59, 0x20, 0x86, 0x26, 0x18, 0x76};
  assert(result[1] == round1);
  assert(result[10] == round10);
  std::cout << "✅ passed.\n";
  return true;
}

auto main() -> int {
  assert(test_sub_bytes());
  assert(test_shift_rows());
  assert(test_mix_columns());
  assert(test_key_expansion());
  std::cout << "🚀 All tests passed!\n";
}