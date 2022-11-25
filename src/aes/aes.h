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
auto sub_bytes(Bytes16 &input, bool inverse = false) -> void;

/// @brief Performs the AES ShiftRows operation
/// @param input An array of 16 bytes
/// @param inverse If true, perform InvShiftRows
auto shift_rows(Bytes16 &input, bool inverse = false) -> void;

/// @brief Performs the AES MixColumns operation
/// @param input An array of 16 bytes
/// @param inverse If true, perform InvMixColumns
auto mix_columns(Bytes16 &input, bool inverse) -> void;

/// @brief Performs the AES KeyExpansion operation
/// @param key An array of 16 bytes
auto key_expansion(const Bytes16 &key) -> Bytes176;
}  // namespace aes

#endif