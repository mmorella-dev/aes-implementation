#ifndef AES_AES_H_
#define AES_AES_H_

#include <array>  // for std::array
#include <cstdint>

namespace aes {

using Bytes4 = std::array<uint8_t, 4>;     // an array of 4 bytes
using Bytes16 = std::array<uint8_t, 16>;   // an array of 16 bytes
using Bytes176 = std::array<Bytes16, 11>;  // a 2d array of 11*16 (176) bytes

/// @brief Performs the AES SubBytes operation
/// @param input An array of 16 bytes
/// @param inverse If true, use the inverse S-Box
void sub_bytes(Bytes16 &input, bool inverse = false);

/// @brief Performs the AES ShiftRows operation
/// @param input An array of 16 bytes
/// @param inverse If true, perform InvShiftRows
void shift_rows(Bytes16 &input, bool inverse = false);

/// @brief Performs the AES MixColumns operation
/// @param input An array of 16 bytes
/// @param inverse If true, perform InvMixColumns
void mix_columns(Bytes16 &input, bool inverse);

/// @brief Performs the AES KeyExpansion operation
/// @param key An array of 16 bytes
Bytes176 key_expansion(const Bytes16 &key);
}  // namespace aes

#endif