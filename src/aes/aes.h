#ifndef AES_AES_H_
#define AES_AES_H_

#include <array> // for std::array
#include <cstdint>

namespace aes {

using Bytes4 = std::array<uint8_t, 4>;     // an array of 4 bytes
using Bytes16 = std::array<uint8_t, 16>;   // an array of 16 bytes
using Bytes176 = std::array<Bytes16, 11>;  // a 2d array of 11*16 (176) bytes

/// @brief Performs the AES SubBytes operation
/// @param input An array of 16 bytes
/// @param inverse If true, use the inverse S-Box
/// @return The result of passing each byte through a Rjindael S-box
Bytes16 sub_bytes(const Bytes16 &input, bool inverse = false);

/// @brief Performs the AES ShiftRows operation
/// @param input An array of 16 bytes
/// @param inverse If true, perform InvShiftRows
/// @return The array, shifted
Bytes16 shift_rows(const Bytes16 &input, bool inverse = false);

/// @brief Performs the AES MixColumns operation
/// @param input An array of 16 bytes
/// @param inverse If true, perform InvMixColumns
/// @return 
Bytes16 mix_columns(const Bytes16 &input, bool inverse);

/// @brief Performs the AES KeyExpansion operation
/// @param key An array of 16 bytes
/// @return An array of 11 keys for AES. 
Bytes176 key_expansion(const Bytes16 &key);
}  // namespace aes

#endif